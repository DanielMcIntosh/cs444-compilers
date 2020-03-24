#include "codegen.h"
#include "ast/allASTHeaders.h"

#include <variant>
#include <algorithm>

using namespace std;

// all calculation results should be left in eax
// ctx->lastExprLValue will be true if the value in eax is a pointer to the
// value (LValue), in which case an instruction mov eax, [eax] should be added

namespace AST {

void ConditionalStatement::codeGenerate(CodeGen::SContext *ctx) {
	// TODO Daniel
	ctx->text.add("; BEGIN - ConditionalStatement");


	ctx->text.add("; END - ConditionalStatement");
}

void ReturnStatement::codeGenerate(CodeGen::SContext *ctx) {
	// TODO Daniel
	ctx->text.add("; BEGIN - ReturnStatement");
	ctx->text.add("; END - ReturnStatement");
}

void BinaryExpression::codeGenerate(CodeGen::SContext *ctx) {
	// TODO Daniel
	ctx->text.add("; BEGIN - BinaryExpression");
	ctx->lastExprLValue = false;
	ctx->text.add("; END - BinaryExpression");
}

void UnaryExpression::codeGenerate(CodeGen::SContext *ctx) {
	// TODO Daniel
	ctx->text.add("; BEGIN - UnaryExpression");
	ctx->lastExprLValue = false;
	ctx->text.add("; END - UnaryExpression");
}

}  // namespace AST

namespace CodeGen {

void SText::addExternSymbol(const vector <string> &symbol) {
	for (const auto &sym : symbol) {
		strdecl512(text, "extern %s", sym.c_str());
		add(text);
	}
}

void SText::declGlobalAndBegin(const string &name) {
	strdecl512(text, "global %s", name.c_str());
	add(text);
	snprintf(text, ARRAY_SIZE(text), "%s:", name.c_str());
	add(text);

	declaredGlobals.insert(name);
}

string SText::toString() {
	for (const auto& constant : constants) {
		visit(visitor{
			[&] (const string& str) {
				strdecl512(text , "%s: dd '%s'", constant.name.c_str(), str.c_str());
				add(text);
				snprintf(text, ARRAY_SIZE(text), "%sLen equ $ - %s - 1",
								 constant.name.c_str(), constant.name.c_str());
				add(text);
			},
			[&] (int num) {
				strdecl512(text , "%s: dd %d", constant.name.c_str(), num);
				add(text);
			}
			}, constant.constant);
	}

	string res;

	for (const auto &externLabel : externalLabels) {
		if (!declaredGlobals.count(externLabel))
			res.append("extern " + externLabel + "\n");
	}

	res.append("section .text\n");

	for (const auto &line : lines) {
		res.append(line);
		res.append("\n");
	}

	return res;
}

void SText::addConstant(const string &name, const string &constant) {
	constants.push_back(SConstant{name, constant});
}

void SText::addConstant(const string &name, unsigned int constant) {
	constants.push_back(SConstant{name, constant});
}

void SText::add(const string &str) {
	lines.push_back(str);
}

void SText::addf(const char *fmt, ...) {
	char buffer[TWO_TO_EIGHT];
	va_list arg;
	va_start(arg, fmt);
	vsnprintf(buffer, TWO_TO_EIGHT, fmt, arg);
	va_end(arg);

	add(string(buffer));
}

void SText::call(const char *fmt, ...) {
	char buffer[TWO_TO_EIGHT];
	va_list arg;
	va_start(arg, fmt);
	vsnprintf(buffer, TWO_TO_EIGHT, fmt, arg);
	va_end(arg);

	addExternSymbol(buffer);
	add("call " + string(buffer));
}

void SText::addExternSymbol(const std::string &str) {
	externalLabels.insert(str);
}

string getProcedureName(const AST::MemberDeclaration *theMember) {
	using namespace AST;
	const string *id = nullptr;
	const vector<std::unique_ptr<AST::VariableDeclaration>> *parameters = nullptr;

	// procedure name (label) does not need to take into account of "this"
	int paramBeginIndex = -1;

	if (theMember->nodeType == AST::NodeType::MethodDeclaration) {
		auto item = (const MethodDeclaration*)theMember;
		id = &item->identifier;
		parameters= &item->parameters;
		if (item->hasModifier(Modifier::Variant::Static)) {
			paramBeginIndex = 0;
		} else {
			paramBeginIndex = 1;
		}
	} else if (theMember->nodeType == NodeType::ConstructorDeclaration) {
		auto item = (const ConstructorDeclaration*)theMember;
		id = &item->identifier;
		parameters= &item->parameters;
		paramBeginIndex = 1;
	} else {
		ASSERT(false);
	}

	string labelName = theMember->_enclosingClass->fqn + "." + *id;
	if (theMember->hasModifier(Modifier::Variant::Native)) {
		labelName = "NATIVE" + labelName;
		return labelName;
	}

	labelName += "_";

	for (size_t i = paramBeginIndex; i < parameters->size(); ++i) {
		const auto &param = parameters->at(i);

		string paramName;
		AST::Type * paramType = param->type.get();
		paramName = paramType->toCode();
		if (paramType->nodeType == NodeType::NameType) {
			paramName = ((NameType*)paramType)->declaration->fqn;
		}
		if (paramType->isArray) {
			paramName += "ARR";
		}

		labelName += paramName + "_";
	}
	labelName.pop_back();
	return labelName;
}

MethodInfo::MethodInfo(int index, AST::MethodDeclaration *decl): tableIndex(index),
                                                                 declaration(decl) {

}

const vector<string> &getPrimitiveTypes() {
	static vector<string> gPrimTypes = {"_Boolean", "_Byte", "_Short", "_Int", "_Char"};
	return gPrimTypes;
}

void codeGenEmitTypeInfo(SContext *ctx, AST::TypeDeclaration *type, int typeIndex,
                         const unordered_map<string, AST::TypeDeclaration*> &typeMap) {

	// class (typeinfo) table
	strdecl512(typeInfoName, "%s_typeinfo", type->fqn.c_str());

	ctx->text.add("section .text"); // read only
	ctx->text.addf("align 2");
	ctx->text.declGlobalAndBegin(typeInfoName);
	ctx->text.addf("dd %d ; %s", typeIndex, type->fqn.c_str());
	ctx->text.addf("; Method selector");

	int mCtr = 0;
	// method selector
	for (auto &methodInfo : ctx->methodTable) {
		string label = getProcedureName(methodInfo->declaration);
		// TODO Wei Heng: also set function pointers for methods that this method
		// is overriding or implementing
		// (e.g. in String.s, java.lang.Object.toString should be filled with
		// java.lang.String.toString)

		bool isConcrete = false;
		for (const auto &ourMethod : type->methodContainSet) {
			if (ourMethod->equals(methodInfo->declaration) &&
			    ourMethod->body) {
				isConcrete = true;
				break;
			}
		}

		if (isConcrete) {
			ctx->text.addExternSymbol(label);
			ctx->text.addf("dd %s; %d %s", label.c_str(), mCtr, label.c_str());
		} else {
			ctx->text.addf("dd 0; %d %s", mCtr, label.c_str());
		}

		++mCtr;
	}

	ctx->text.addf(" ; Subtype table");

	// calculate subtype testing table
	int typeCounter = 0;
	for (auto &[otherTypeName, otherType] : typeMap) {
		if (std::find(type->hyperSet.begin(), type->hyperSet.end(), otherType) !=
		    type->hyperSet.end()) {
			ctx->text.addf("dd 1 ; %d %s", typeCounter, otherType->fqn.c_str());
		} else {
			ctx->text.addf("dd 0 ; %d %s", typeCounter, otherType->fqn.c_str());
		}
		++typeCounter;
	}

	auto primTypes = getPrimitiveTypes();
	for (const auto &primType : primTypes) {
		ctx->text.addf("dd 0 ; %d %s", typeCounter, primType.c_str());
		++typeCounter;
	}
}

void codeGenInitMethodSelectorTable(SContext *ctx,
                                    const unordered_map<string, AST::TypeDeclaration*> &typeMap) {
	using namespace AST;
	// fill in selector table with unique declared methods (that are in base classes)
	for (auto &[name, type]: typeMap) {
		for (auto *method : type->methodContainSet) {
			if (method->hasModifier(Modifier::Variant::Static))
				continue;

			string label = getProcedureName(method);
			auto it = ctx->methodSelector.find(label);
			if (it != ctx->methodSelector.end())
				continue;

			int index = ctx->methodTable.size();
			ctx->methodTable.emplace_back(make_unique<MethodInfo>(index, method));
			auto pr = ctx->methodSelector.insert(make_pair(label, ctx->methodTable.back().get()));
			ASSERT(pr.second);
		}
	}
}

}  // namespace CodeGen

using namespace CodeGen;

BackendResult doBackend(const MiddleendResult &middleend) {
	using namespace AST;
	BackendResult result;
	SContext context, *ctx = &context;

	codeGenInitMethodSelectorTable(ctx, middleend.semanticDB.typeMap);

	// constructor and method implementations
	int typeIndex = -1;
	for (auto &[name, type] : middleend.semanticDB.typeMap) {
		++typeIndex;

		if (type->isInterface)
			continue;

		ctx->typeName = name;
		ctx->text = SText();

		{ // constructors
			for (auto *ctor : type->constructorSet) {

				string labelName = getProcedureName(ctor);
				ctx->text.declGlobalAndBegin(labelName);

				ctx->_numParam = ctor->parameters.size();

					//   1 st arg
					//   ...
					//   n-1 th arg
					//   n th arg
					//   old eip
					//   old ebp <-- ebp = esp
				ctx->text.add(R"(
push ebp
mov ebp, esp
)");

				ctor->body->codeGenerate(ctx);

				ctx->text.add(R"(
mov esp, ebp
pop ebp
ret
)");
			}
		}

    { // methods
      for (auto *method : type->methodContainSet) {
      	if (!method)
      		continue;
	      if (method->_enclosingClass != type)
	      	continue;
	      if (!method->body)
	      	continue;

	      string labelName = getProcedureName(method);
	      ctx->text.declGlobalAndBegin(labelName);
	      ctx->_numParam = method->parameters.size();
	      ctx->text.add(R"(
push ebp
mov ebp, esp
)");
	      method->body->codeGenerate(ctx);
	      ctx->text.add(R"(
mov esp, ebp
pop ebp
ret
)");
      }
    }

		{
			// static fields
			ctx->text.add("section .data\n align 2\n");
			for (auto &field : type->fieldContainSet) {
				if (!field->hasModifier(Modifier::Variant::Static))
					continue;

				strdecl512(label, "%s.%s", type->fqn.c_str(),
								field->varDecl->identifier.c_str());
				ctx->text.declGlobalAndBegin(label);
				ctx->text.add("dd 0");
			}

		}

    codeGenEmitTypeInfo(ctx, type, typeIndex, middleend.semanticDB.typeMap);

		string fileName = name + ".s";
		result.sFiles.push_back(SFile{fileName, context.text.toString()});
	}

	// stub file (type info for primitive types (place holder), _start)
	{
		ctx->text = SText();
		int primIndex = ++typeIndex;
		auto primTypes = getPrimitiveTypes();

		for (const auto &primType : primTypes) {
			strdecl512(typeInfoName, "%s_typeinfo", primType.c_str());

			ctx->text.addf("\n\nalign 2");
			ctx->text.declGlobalAndBegin(typeInfoName);
			ctx->text.addf("dd %d ; %s", primIndex, primType.c_str());
			ctx->text.addf("; Method selector");

			for (const auto &methodInfo : ctx->methodTable) {
				ctx->text.addf("dd 0 ; %d", methodInfo->tableIndex);
			}

			ctx->text.add("; Subtype testing");
			int typeCounter = 0;
			for (const auto &type : middleend.semanticDB.typeMap) {
				ctx->text.addf("dd 0; %d %s", typeCounter, type.first.c_str());
				++typeCounter;
			}

			for (const auto &otherPrimType : primTypes) {
				ctx->text.addf("dd 0 ; %d %s", typeCounter, otherPrimType.c_str());
				++typeCounter;
			}

			++primIndex;
		}

		ctx->text.declGlobalAndBegin("_start");
		ctx->text.add("mov eax, 123");
		ctx->text.call("__debexit");

		result.sFiles.push_back(SFile{"stub.s", ctx->text.toString()});
	}
	return result;
}

BackendResult doBackend2(const MiddleendResult &middleend) {

	vector<string> runtimeSymbols;
	runtimeSymbols.push_back("__malloc");
	runtimeSymbols.push_back("__debexit");
	runtimeSymbols.push_back("__exception");
	runtimeSymbols.push_back("NATIVEjava.io.OutputStream.nativeWrite");

	SText s;
	s.addExternSymbol(runtimeSymbols);
	s.addConstant("hello", "Hello from ASM!");

	s.add("section .text");
	s.declGlobalAndBegin("_start");

	s.add(R"(
mov ebx, 0
mov ecx, helloLen
loop:
cmp ebx, ecx
je loopOut
mov edx, hello
mov eax, [edx + ebx]
push ebx
push ecx
call NATIVEjava.io.OutputStream.nativeWrite
pop ecx
pop ebx
add ebx, 1
jmp loop
loopOut:
mov eax, 123
call __debexit
	 )");

	BackendResult result;
	result.sFiles.push_back(SFile{"stub.s", s.toString()});
	return result;
}


namespace AST {

//////////////////////////////////////////////////////////////////////////////
//
// Expression
//
//////////////////////////////////////////////////////////////////////////////

void Literal::codeGenerate(CodeGen::SContext *ctx) {
	auto item = (Literal*)this;

	strdecl512(label, "%s_const_%d", ctx->typeName.c_str(), ++ctx->counter);
	string labelS = string(label);

	unsigned int effectiveValue = 0;
	bool isInt = false;

	switch (item->value.index()) {
		case 0:
			// unsigned int
			effectiveValue = std::get<0>(item->value);
			isInt = true;
			break;

		case 1:
			// bool
			effectiveValue = std::get<1>(item->value);
			isInt = true;

			break;
		case 2:
			// char
			effectiveValue = std::get<2>(item->value);
			isInt = true;

			break;
		case 3:
			// string
      // TODO : Titus
      // need to call class instance creation of string
			effectiveValue = 0;
			isInt = true;
			break;

		case 4:
			// null
			effectiveValue = 0;
			isInt = true;

			break;
	}

	if (isInt) {
		ctx->text.addConstant(labelS, effectiveValue);
    ctx->text.addf("mov eax, [%s]", label);
		ctx->lastExprLValue = false;
	}
}

void ArrayCreationExpression::codeGenerate(CodeGen::SContext *ctx) {
	ctx->text.add("; BEGIN - ArrayCreationExpression");

	auto item = (ArrayCreationExpression*)this;
	TypeResult *theTypeResult = &item->typeResult;

	ASSERT(theTypeResult->isArray);

	string typeInfoName;
	if (theTypeResult->isPrimitive) {
		switch (theTypeResult->primitiveType) {
			case TypePrimitive::Boolean:
				typeInfoName = "_Boolean";
				break;
			case TypePrimitive::Byte:
				typeInfoName = "_Byte";
				break;
			case TypePrimitive::Short:
				typeInfoName = "_Short";
				break;
			case TypePrimitive::Int:
				typeInfoName = "_Int";
				break;
			case TypePrimitive::Char:
				typeInfoName = "_Char";
				break;
			default:
				ASSERT(false);
				break;
		}
	} else {
		typeInfoName = theTypeResult->userDefinedType->fqn;
	}

	typeInfoName += "_typeinfo";

	item->size->codeGenerate(ctx);

	if (ctx->lastExprLValue) {
		ctx->text.add("mov eax, [eax]");
	}

	ctx->text.add("push eax"); // pushed number of elements
	ctx->text.addf("add eax, %d", ARRAY_DATA_OFFSET);
	ctx->text.add("shl eax, 2");
	ctx->text.call("__malloc");

	ctx->text.addExternSymbol(typeInfoName);
	ctx->text.addf("mov dword [eax + %d], %s", OBJECT_CLASS * 4,
	               typeInfoName.c_str());
	ctx->text.addf("mov dword [eax + %d], 1", OBJECT_ISARRAY * 4);
	ctx->text.add("mov ebx, [esp]");
	ctx->text.addf("mov [eax + %d], ebx", ARRAY_LENGTH_OFFSET * 4); // number of elements (length)

	ctx->text.add(R"(
mov ebx, 0
mov ecx, [esp]
pop edx
)"); // pop edx: number of elements (not used)

	int counter = ++ctx->counter;

	string loopLabel;
	strAppend(&loopLabel, "%s_arrcreate_loop_%d", ctx->typeName.c_str(), counter);
	string loopOutLabel;
	strAppend(&loopOutLabel, "%s_arrcreate_loopOut_%d", ctx->typeName.c_str(), counter);

	ctx->text.addf("%s:", loopLabel.c_str());
	ctx->text.add("cmp ebx, ecx");
	ctx->text.addf("je %s", loopOutLabel.c_str());

	ctx->text.add(R"(
push eax
push ebx
push ecx)");

	if (theTypeResult->isPrimitive) {
		ctx->text.add("mov eax, 0");
	} else {
		ctx->text.call("%s_clsInstCreatWarp", typeInfoName.c_str());
	}

	ctx->text.add(R"(
mov edx, eax
pop ecx
pop ebx
pop eax)");

	ctx->text.addf("mov [eax + ebx * 4 + %d], edx", ARRAY_DATA_OFFSET * 4);

	ctx->text.add("add ebx, 1");
	ctx->text.addf("jmp %s\n%s:", loopLabel.c_str(), loopOutLabel.c_str());

	ctx->text.add("; END - ArrayCreationExpression");
}

void MethodInvocation::codeGenerate(CodeGen::SContext *ctx) {
	ctx->text.add("; BEGIN - MethodInvocation");

	auto item = (MethodInvocation*)this;
	CodeGen::SText *text = &ctx->text;

	int numArg = 0;
	if (item->source.index() == 0) {
		// non static method
		auto &lExpr = std::get<0>(item->source);

		// this
		lExpr->codeGenerate(ctx);

		if (ctx->lastExprLValue) {
			ctx->text.add("mov eax, [eax]");
		}
		ctx->text.add("push eax");
		++numArg;
	}

	// arguments
	for (auto &arg : item->args) {
		arg->codeGenerate(ctx);
		if (ctx->lastExprLValue) {
			ctx->text.add("mov eax, [eax]");
		}
		ctx->text.add("push eax");
		++numArg;
	}

	// figure out procedure pointer
	if (item->source.index() == 0) {
		// non static method
		auto &lExpr = std::get<0>(item->source);
		TypeResult *theTypeResult = &lExpr->typeResult;
		ASSERT(!theTypeResult->isArray);
		ASSERT(!theTypeResult->isPrimitive);

		// all method uses selector...
		string procName = CodeGen::getProcedureName(item->declaration);
		auto it = ctx->methodSelector.find(procName);
		ASSERT(it != ctx->methodSelector.end());

		text->add("mov eax, esp");
		ASSERT(numArg > 0);
		strdecl512(inst, "add eax, %d", (numArg - 1) * 4);
		text->add(inst);
		// get "this" pointer
		text->add("mov eax, [eax]");
		// get class pointer
		text->add("mov eax, [eax]");

		int procOffset = (CLASS_SELECTOR + it->second->tableIndex);
		snprintf(inst, ARRAY_SIZE(inst), "add eax, %d", procOffset * 4);
		text->add(inst);
		text->add("mov eax, [eax]");
		text->addf("call eax ; %s", it->first.c_str());

	} else if (item->source.index() == 1) {
		// static method
		auto nameType = (NameType*)std::get<1>(item->source).get();
		ASSERT(nameType->nodeType == NodeType::NameType);

		string procName = CodeGen::getProcedureName(item->declaration);

		text->call("%s", procName.c_str());
	} else {
		ASSERT(false);
	}

	// result is in eax (if any)
	strdecl512(inst, "add esp, %d", numArg * 4);
	text->add(inst);
	ctx->lastExprLValue = false;

	ctx->text.add("; END - MethodInvocation");
}

void AssignmentExpression::codeGenerate(CodeGen::SContext *ctx) {
	ctx->text.add("; BEGIN - AssignmentExpression");

	CodeGen::SText *text = &ctx->text;
	auto item = (AssignmentExpression*)this;

	item->lhs->codeGenerate(ctx);
	ASSERT(ctx->lastExprLValue);
	text->add("push eax");
	item->rhs->codeGenerate(ctx);
	text->add("pop ebx");
	if (ctx->lastExprLValue) {
		text->add("mov eax, [eax]");
	}
	text->add("mov [ebx], eax");
	text->add("mov eax, ebx");
	ctx->lastExprLValue = true;

	ctx->text.add("; END - AssignmentExpression");
}

void NameExpression::codeGenerate(CodeGen::SContext *ctx) {
	auto item = (NameExpression*)this;
	item->converted->codeGenerate(ctx);
}

void CastExpression::codeGenerate(CodeGen::SContext *ctx) {
	// TODO: Wei Heng
	ctx->text.add("; BEGIN - CastExpression");
	ctx->text.add("; END - CastExpression");
}

void FieldAccess::codeGenerate(CodeGen::SContext *ctx) {
	ctx->text.add("; BEGIN - FieldAccess");

	CodeGen::SText *text = &ctx->text;

	int varIndex = source.index();

	if (varIndex == 1) {
		// static field

		auto &nameType = std::get<1>(source);
		ASSERT(nameType->nodeType == NodeType::NameType);

		strdecl512(label, "%s.%s", nameType->declaration->fqn.c_str(),
		           member.c_str());
		ctx->text.addExternSymbol(label);
		text->addf("mov eax, %s", label);
		ctx->lastExprLValue = true;
		ctx->text.add("; END - FieldAccess");
    return;
	}

	// arbitrary expr
	auto &lExpr = std::get<0>(source);
	lExpr->codeGenerate(ctx);

	TypeResult *theTypeResult = &lExpr->typeResult;

	if (theTypeResult->isArray) {
		// array
		ASSERT(member == "length");
		if (ctx->lastExprLValue) {
			text->add("mov eax, [eax]");
		}

		// length is the first field
		strdecl512(inst, "add eax, %d", OBJECT_FIELD * 4);
		text->add(inst);
		ctx->lastExprLValue = true;
		ctx->text.add("; END - FieldAccess");
		return;
	}

	// non array
	ASSERT(!theTypeResult->isPrimitive);

	if (ctx->lastExprLValue) {
		text->add("mov eax, [eax]");
	}
	strdecl512(inst, "add eax, %d", (decl->varDecl->index + OBJECT_FIELD) * 4);
	text->add(inst);
	ctx->lastExprLValue = true;
	ctx->text.add("; END - FieldAccess");
}

void LocalVariableExpression::codeGenerate(CodeGen::SContext *ctx) {
	ctx->text.add("; BEGIN - LocalVariableExpression");

	ctx->text.add("mov eax, ebp");

	if (declaration->index < ctx->_numParam) {
		// is a parameter
		int offset = ctx->_numParam - declaration->index + 1;
		strdecl512(inst, "add eax, %d", offset * 4);
		ctx->text.add(inst);
	} else {
		// is a local variable
		int offset = declaration->index - ctx->_numParam + 1;
		strdecl512(inst, "sub eax, %d", offset * 4);
		ctx->text.add(inst);
	}

	ctx->lastExprLValue = true;
	ctx->text.add("; END - LocalVariableExpression");
}

void ClassInstanceCreationExpression::codeGenerate(CodeGen::SContext *ctx) {
	// TODO : Titus
	ctx->text.add("; BEGIN - ClassInstanceCreationExpression");
	ctx->lastExprLValue = false;
	ctx->text.add("; END - ClassInstanceCreationExpression");
}

void ArrayAccess::codeGenerate(CodeGen::SContext *ctx) {
	// TODO: Wei Heng
	ctx->text.add("; BEGIN - ArrayAccess");
	ctx->lastExprLValue = true;
	ctx->text.add("; END - ArrayAccess");
}

//////////////////////////////////////////////////////////////////////////////
//
// Statement
//
//////////////////////////////////////////////////////////////////////////////

void LocalVariableDeclarationStatement::codeGenerate(CodeGen::SContext *ctx) {
	// TODO: Wei Heng
	ctx->text.add("; BEGIN - LocalVariableDeclarationStatement");

	ctx->text.add("; END - LocalVariableDeclarationStatement");
}

void ExpressionStatement::codeGenerate(CodeGen::SContext *ctx) {
	auto item = (ExpressionStatement*)this;
	if (!item->expression)
		return;
	item->expression->codeGenerate(ctx);
}

void Block::codeGenerate(CodeGen::SContext *ctx) {
	ctx->text.add("; BEGIN - Block");
	auto item = (Block*)this;
	for (auto &stmt : item->statements) {
		stmt->codeGenerate(ctx);
	}
	ctx->text.add("; END - Block");
}

} // namespace AST


