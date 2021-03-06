#include "codegen.h"
#include "ast/allASTHeaders.h"

#include <variant>
#include <algorithm>

using namespace std;

// all calculation results should be left in eax

namespace AST {

void ConditionalStatement::codeGenerate(CodeGen::SContext *ctx) {
	static thread_local int uniqueNumber = 0;
	std::string uniqueIdentifier = std::to_string(uniqueNumber++);

	ctx->text.add("; BEGIN - ConditionalStatement" + uniqueIdentifier);
	int stackSizeAtStart = ctx->stackSize;

	if (init)
	{
		init->codeGenerate(ctx);
	}

	ctx->text.add("CondStart" + uniqueIdentifier + ":");
	if (condition)
	{
		condition->codeGenerate(ctx);
		ctx->text.add("cmp eax, 0; ConditionalStatement" + uniqueIdentifier + " (" + condition->toCode() + ")");
		ctx->text.add("je CondElse" + uniqueIdentifier);
	}

	body->codeGenerate(ctx);

	switch(condType)
	{
		case ConditionType::While:
		case ConditionType::For:
		{
			if (increment) {
				increment->codeGenerate(ctx);
			}
			ctx->text.add("jmp CondStart" + uniqueIdentifier);
			break;
		}
		case ConditionType::If:
		{
			ctx->text.add("jmp CondEnd" + uniqueIdentifier);
			break;
		}
		default:
			assert(false);
	}

	ctx->text.add("CondElse" + uniqueIdentifier + ":");
	if (elseBody)
	{
		elseBody->codeGenerate(ctx);
	}

	ctx->text.add("CondEnd" + uniqueIdentifier + ":");

	if (ctx->stackSize != stackSizeAtStart)
	{
		// reset the stack to where it was before the start of this conditional statement
		int delta = (ctx->stackSize - stackSizeAtStart) * 4;
		ctx->text.add("add esp, " + std::to_string(delta) + "; END - ConditionalStatement" + uniqueIdentifier + " (pop loop variables)");
		ctx->stackSize = stackSizeAtStart;
	} else
	{
		ctx->text.add("; END - ConditionalStatement" + uniqueIdentifier);
	}
}

void ReturnStatement::codeGenerate(CodeGen::SContext *ctx) {
	ctx->text.add("; BEGIN - ReturnStatement (" + toCode() + ")");
	if (returnValue)
		returnValue->codeGenerate(ctx);
	ctx->text.add(R"(mov esp, ebp
pop ebp
ret)");
	ctx->text.add("; END - ReturnStatement (" + toCode() + ")");
}

void BinaryExpression::codeGenerate(CodeGen::SContext *ctx, bool returnLValue) {
	assert(!returnLValue);
	static thread_local int uniqueNumber = 0;
	std::string uniqueIdentifier = std::to_string(uniqueNumber++);

	ctx->text.add("; BEGIN - BinaryExpression" + uniqueIdentifier + " (" + toCode() + ")");

	// string concatenation
	if (typeResult.isJavaString())
	{
		// call lhs.concat(rhs)
		std::vector<std::unique_ptr<Expression>> args;
		args.push_back(std::move(std::get<0>(rhs)));
		MethodInvocation concatInvoke(std::move(lhs), "concat", std::move(args));
		// hack - rather fragile, there are several conditions which have to be met for this to be safe.
		// Some of the most significant of those are: 1) MethodInvocation::resolve only uses scope
		// for access violation checks, but String::concat is public, so those checks are skipped
		// 2) the children of concatInvoke have already had resolveAndDeduce called on them
		// 3) there's a lot of things that are un-initialized in concatInvoke (e.g. concatInvoke.typeResult)
		// we don't use/care about any of them (in either resolve or codeGenerate)
		concatInvoke.resolve(Semantic::Scope(nullptr));
		concatInvoke.codeGenerate(ctx);

		// move lhs and rhs back from concatInvoke
		// may not be necessary since codeGenerate is the last compilation step, but we'll do it just to be safe
		lhs = std::move(std::get<0>(concatInvoke.source));
		rhs = std::move(concatInvoke.args[0]);

		ctx->text.add("; END - BinaryExpression" + uniqueIdentifier + " (" + toCode() + ")");
		return;
	}

	lhs->codeGenerate(ctx);

	if (op == Variant::InstanceOf)
	{
		//TODO
		ctx->text.add("mov eax, 1"); // right now fake true
		ctx->text.add("; END - BinaryExpression" + uniqueIdentifier + " (" + toCode() + ")");
		return;
	}

	// special case to deal with LazyAnd and LazyOr since they don't always evaluate the rhs
	switch(op)
	{
		case Variant::LazyAnd:
			ctx->text.add("cmp eax, 0");
			ctx->text.add("je ExprEnd" + uniqueIdentifier);
			std::get<0>(rhs)->codeGenerate(ctx);
			break;
		case Variant::LazyOr:
			ctx->text.add("cmp eax, 0");
			ctx->text.add("jne ExprEnd" + uniqueIdentifier);
			std::get<0>(rhs)->codeGenerate(ctx);
			break;
		default:
			ctx->text.add("push eax");
			std::get<0>(rhs)->codeGenerate(ctx);
			ctx->text.add("mov ebx, eax");
			ctx->text.add("pop eax");
			break;
	}
	//process rhs & compute result
	switch(op)
	{
		case Variant::Add:
			ctx->text.add("add eax, ebx");
			break;
		case Variant::Sub:
			ctx->text.add("sub eax, ebx");
			break;
		case Variant::Mult:
			ctx->text.add("imul ebx");
			break;
		case Variant::Div:
		case Variant::Mod:
			// check for div by 0
			ctx->text.addExternSymbol("exception");
			ctx->text.add("cmp ebx, 0; div by 0 check");
			ctx->text.add("je exception");
			// perform the division
			ctx->text.add("cdq");
			ctx->text.add("idiv ebx");
			if (op == Variant::Mod)
				ctx->text.add("mov eax, edx");
			break;
		case Variant::Lt:
			ctx->text.add("cmp eax, ebx");
			ctx->text.add("setl al");
			ctx->text.add("movzx eax, al");
			break;
		case Variant::Gt:
			ctx->text.add("cmp eax, ebx");
			ctx->text.add("setg al");
			ctx->text.add("movzx eax, al");
			break;
		case Variant::LtEq:
			ctx->text.add("cmp eax, ebx");
			ctx->text.add("setle al");
			ctx->text.add("movzx eax, al");
			break;
		case Variant::GtEq:
			ctx->text.add("cmp eax, ebx");
			ctx->text.add("setge al");
			ctx->text.add("movzx eax, al");
			break;
		case Variant::Eq:
			ctx->text.add("cmp eax, ebx");
			ctx->text.add("sete al");
			ctx->text.add("movzx eax, al");
			break;
		case Variant::NEq:
			ctx->text.add("cmp eax, ebx");
			ctx->text.add("setne al");
			ctx->text.add("movzx eax, al");
			break;
		case Variant::EagerAnd:
			// if ebx is 0, overwrite eax with 0, otherwise leave eax as is
			// can't use set as that would overwrite the value in eax when ebx is non-zero
			ctx->text.add("cmp ebx, 0");
			ctx->text.add("cmove eax, ebx");
			break;
		case Variant::EagerOr:
			ctx->text.add("or eax, ebx");
			break;
		case Variant::LazyAnd:
		case Variant::LazyOr:
			ctx->text.add("ExprEnd" + uniqueIdentifier + ":");
			break;
		default:
			assert(false);
	}

	ctx->text.add("; END - BinaryExpression" + uniqueIdentifier + " (" + toCode() + ")");
}

void UnaryExpression::codeGenerate(CodeGen::SContext *ctx, bool returnLValue) {
	assert(!returnLValue);
	ctx->text.add("; BEGIN - UnaryExpression (" + toCode() + ")");
	expr->codeGenerate(ctx);
	switch(op)
	{
		case Variant::Minus:
			ctx->text.add("neg eax");
			break;
		case Variant::Bang:
			ctx->text.add("cmp eax, 0");
			ctx->text.add("sete al");
			ctx->text.add("movzx eax, al");
			break;
		default:
			assert(false);
	}
	ctx->text.add("; END - UnaryExpression (" + toCode() + ")");
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
	for (const auto& literal : stringLiterals) {
		ASSERT(OBJECT_CLASS == 0);
		ASSERT(OBJECT_ISARRAY == 1);
		ASSERT(ARRAY_LENGTH_OFFSET == 2);
		ASSERT(ARRAY_DATA_OFFSET == 3);
		addf("%s: dd %s", literal.name.c_str(), "_Char_typeinfo");
		addf("dd 1");
		addf("dd %ld", literal.value.length());

		if (literal.value.empty())
			continue;

		string result;
		char buffer[16];
		for (char c : literal.value) {
			snprintf(buffer, 16, "0x%x,", c);
			result += buffer;
		}
		result.pop_back();

		this->lines.push_back("dd " + result);
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

void SText::addStringLiteral(const string &name, const string &value) {
	stringLiterals.push_back(SConstant{name, value});
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
		string implLabel;

		ASSERT(!methodInfo->declaration->hasModifier(AST::Modifier::Variant::Static));

		for (const auto &hyper : type->hyperSet) {
			if (hyper != methodInfo->declaration->_enclosingClass)
				continue;

			for (const auto &ourContain : type->methodContainSet) {
				if (ourContain->_enclosingClass != type)
					continue;

				if (ourContain->hasModifier(AST::Modifier::Variant::Static))
					continue;

				bool equals = ourContain->identifier == methodInfo->declaration->identifier &&
								      ourContain->parameters.size() == methodInfo->declaration->parameters.size();

				if (!equals)
					continue;

				for (size_t paramIdx = 1; paramIdx < ourContain->parameters.size(); ++paramIdx) {
					equals &= ourContain->parameters[paramIdx]->typeEquals(methodInfo->declaration->parameters[paramIdx].get());
				}

				if (!equals)
					continue;

				implLabel = getProcedureName(ourContain);
				goto found;
			}
		}

		found:
		if (implLabel.empty()) {
			for (const auto &ourMethod : type->methodContainSet) {
				if (ourMethod->equals(methodInfo->declaration) &&
					ourMethod->body) {
					implLabel = label;
					break;
				}
			}
		}

		if (!implLabel.empty()) {
			ctx->text.addExternSymbol(label);
			ctx->text.addf("dd %s; %d %s", implLabel.c_str(), mCtr, label.c_str());
		} else {
			ctx->text.addf("dd 0; %d %s", mCtr, label.c_str());
		}

		++mCtr;
	}

	ctx->text.addf(" ; Subtype table");

	// calculate subtype testing table
	// in this table, any type is a subtype of itself
	int typeCounter = 0;
	for (auto &[otherTypeName, otherType] : typeMap) {
		if (std::find(type->hyperSet.begin(), type->hyperSet.end(), otherType) != type->hyperSet.end() ||
			type == otherType) {
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
	SContext context(middleend.semanticDB.typeMap), *ctx = &context;

	codeGenInitMethodSelectorTable(ctx, middleend.semanticDB.typeMap);

	// constructor and method implementations
	int typeIndex = -1;
	for (auto &[name, type] : middleend.semanticDB.typeMap) {
		++typeIndex;

		if (type->isInterface)
			continue;

		ctx->typeName = name;
		ctx->text = SText();

		type->codeGenerate(ctx);

		codeGenEmitTypeInfo(ctx, type, typeIndex, middleend.semanticDB.typeMap);

		string fileName = name + ".s";
		result.sFiles.push_back(SFile{fileName, context.text.toString()});
	}

	// stub file (type info for primitive types (place holder), _start)
	{
		ctx->text = SText();

		ctx->text.declGlobalAndBegin("exception");
		ctx->text.call("__exception");

		ctx->text.declGlobalAndBegin("_start");

		// static field initializer
		for (const auto &[name, type] : middleend.semanticDB.typeMap) {
			type->codeGenerateStaticInit(ctx);
		}

		// call test
		bool found = false;
		for (const auto &[name, type] : middleend.semanticDB.typeMap) {
			if (gEntryPointFile) {
				// files are passed on command line. use the designated source file
				if (type->sourceFilePath != string(gEntryPointFile))
					continue;
			}
			// else just find a class that contains that method..

			for (const auto &method : type->methodContainSet) {
				if (method->identifier == "test" &&

				    method->parameters.empty() && method->hasModifier(Modifier::Variant::Static)) {
					ASSERT(!found);
					found = true;
					ctx->text.call("%s", getProcedureName(method).c_str());
				}
			}
		}
		ASSERT(found);
		ctx->text.add("mov ebx, eax");
		ctx->text.add("mov eax, 1");
		ctx->text.add("int 0x80");

		int primIndex = ++typeIndex;
		auto primTypes = getPrimitiveTypes();

		for (const auto &primType : primTypes) {
			strdecl512(typeInfoName, "%s_typeinfo", primType.c_str());

			ctx->text.addf("\n\nalign 2");
			ctx->text.declGlobalAndBegin(typeInfoName);
			ctx->text.addf("dd %d ; %s", primIndex, primType.c_str());
			ctx->text.addf("; Method selector");

			for (const auto &methodInfo : ctx->methodTable) {
				if (methodInfo->declaration->_enclosingClass->fqn == "java.lang.Object") {
					string label = getProcedureName(methodInfo->declaration);
					ctx->text.addExternSymbol(label);
					ctx->text.addf("dd %s; %d", label.c_str(), methodInfo->tableIndex);
				} else {
					ctx->text.addf("dd 0 ; %d", methodInfo->tableIndex);
				}
			}

			ctx->text.add("; Subtype testing");
			int typeCounter = 0;
			for (const auto &type : middleend.semanticDB.typeMap) {
				int isSub = type.first == "java.lang.Object" ? 1 : 0;
				ctx->text.addf("dd %d; %d %s", isSub, typeCounter, type.first.c_str());
				++typeCounter;
			}

			for (const auto &otherPrimType : primTypes) {
				ctx->text.addf("dd 0 ; %d %s", typeCounter, otherPrimType.c_str());
				++typeCounter;
			}

			++primIndex;
		}

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
	s.addStringLiteral("hello", "Hello from ASM!");

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

void TypeDeclaration::codeGenerate(CodeGen::SContext *ctx) {
	// constructors
	for (auto *ctor : this->constructorSet) {
		ctor->codeGenerate(ctx);
	}

	// methods
	for (auto *method : this->methodContainSet) {
		if (!method)
			continue;
		if (method->_enclosingClass != this)
			continue;
		method->codeGenerate(ctx);
	}

	// static fields
	ctx->text.add("section .data\n align 2\n");
	for (auto *field : this->fieldContainSet) {
		if (field == nullptr || !field->hasModifier(Modifier::Variant::Static))
			continue;

		ctx->text.declGlobalAndBegin(this->fqn + "." + field->varDecl->identifier);
		ctx->text.add("dd 0");
	}
}

void TypeDeclaration::codeGenerateStaticInit(CodeGen::SContext *ctx)
{
	// Default initialize all static fields to 0. This  has to happen before
	// we run their initializers in case some of them refer to un-initialized
	// members (e.g. within a static method call) (See JLS 8.3.2.3)
	for (auto *field : this->fieldContainSet) {
		if (field == nullptr)
			continue;
		if (!field->hasModifier(Modifier::Variant::Static))
			continue;

		field->asFieldAccess()->codeGenerate(ctx, true);
		ctx->text.add("mov dword [eax], 0");
	}

	for (auto *field : this->fieldContainSet) {
		if (field == nullptr || !field->hasModifier(Modifier::Variant::Static))
			continue;


		if (!field->varDecl->initializer) {
			ctx->text.add("push dword 0");
		} else {
			field->varDecl->initializer->codeGenerate(ctx);
			ctx->text.add("push eax");
		}

		field->asFieldAccess()->codeGenerate(ctx, true);
		// pop the initializer directly into field
		ctx->text.add("pop dword [eax]");
	}
}

void MethodDeclaration::codeGenerate(CodeGen::SContext *ctx)
{
	if (!body)
		return;

	ctx->text.declGlobalAndBegin(getProcedureName(this));
	ctx->_numParam = parameters.size();
	ctx->text.add(R"(
push ebp
mov ebp, esp
)");
	body->codeGenerate(ctx);
	ctx->text.add(R"(
mov esp, ebp
pop ebp
ret
)");
}

void ConstructorDeclaration::codeGenerate(CodeGen::SContext *ctx)
{
	ctx->text.declGlobalAndBegin(getProcedureName(this));

	ctx->_numParam = parameters.size();

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

	// 1. call super()
	if (defaultSuper != nullptr) {
		// load "this"
		parameters[0]->asLocalVarExpr()->codeGenerate(ctx);
		ctx->text.addf("push eax");

		ctx->text.call("%s", getProcedureName(defaultSuper).c_str());
		ctx->text.add("pop eax");
	}

	// 2. default initialize all non static fields to 0
	// has to happen before we run their initializers in case some of them
	// refer to un-initialized members (e.g. within a method call)
	for (auto *field : _enclosingClass->fieldContainSet) {
		if (field == nullptr)
			continue;
		if (field->hasModifier(Modifier::Variant::Static))
			continue;
		if (field->_enclosingClass != _enclosingClass)
			continue;

		field->asFieldAccess(parameters[0]->asLocalVarExpr())->codeGenerate(ctx, true);
		ctx->text.add("mov dword [eax], 0");
	}

	// 3. actual body (also contains field initializers)
	body->codeGenerate(ctx);

	ctx->text.add(R"(
mov esp, ebp
pop ebp
ret
)");
}

void codeGenClassInstanceCreatePreamble(CodeGen::SContext *ctx, TypeDeclaration *typeDecl) {
	ctx->text.addf("mov eax, %ld", (OBJECT_FIELD + typeDecl->fieldContainSet.size()) * 4);
	ctx->text.call("__malloc");

	ctx->text.add("push eax"); // final return value

	strdecl512(label, "%s_typeinfo", typeDecl->fqn.c_str());
	ctx->text.addExternSymbol(label);
	ctx->text.addf("mov dword [eax], %s", label);
	ctx->text.addf("mov dword [eax + %d], 0", OBJECT_ISARRAY * 4);
}

void codeGenClassInstanceCreateEpilogue(CodeGen::SContext *ctx, int numArg) {
	ctx->text.add("add esp, " + std::to_string(numArg * 4) + "; ClassInstanceCreationExpression - pop args");
	ctx->text.add("pop eax"); // final return value
}

//////////////////////////////////////////////////////////////////////////////
//
// Expression
//
//////////////////////////////////////////////////////////////////////////////

void Literal::codeGenerate(CodeGen::SContext *ctx, bool returnLValue) {
	assert(!returnLValue);
	auto item = (Literal*)this;

	unsigned int effectiveValue = 0;

	switch (item->value.index()) {
		case 3: {
			// string
			strdecl512(label, "const_%d", ++ctx->counter);
			string labelS = string(label);

			ConstructorDeclaration *ctorDecl = nullptr;
			for (auto &ctor : stringDecl->constructorSet) {
				if (ctor->parameters.size() == 2 &&
				    ctor->parameters[1]->type->isArray &&
				    ctor->parameters[1]->identifier == "chars") {
					ASSERT(!ctorDecl);
					ctorDecl = ctor;
				}
			}
			ASSERT(ctorDecl);

			ctx->text.addExternSymbol("_Char_typeinfo");

			ctx->text.addStringLiteral(label, std::get<3>(item->value));

			codeGenClassInstanceCreatePreamble(ctx, stringDecl);

			int numArg = 0;
			ctx->text.add("push eax"); ++numArg;
			ctx->text.addf("push dword %s", label);  ++numArg;
			ctx->text.call("%s", getProcedureName(ctorDecl).c_str());

			codeGenClassInstanceCreateEpilogue(ctx, numArg);

			return;
		}
		case 0:
			// unsigned int
			effectiveValue = std::get<0>(item->value);
			break;
		case 1:
			// bool
			effectiveValue = std::get<1>(item->value);
			break;
		case 2:
			// char
			effectiveValue = std::get<2>(item->value);
			break;
		case 4:
			// null
			effectiveValue = 0;
			break;
	}

	ctx->text.add("mov dword eax, " + std::to_string(effectiveValue) + ";   Literal (" + toCode() + ")");
}

void ArrayCreationExpression::codeGenerate(CodeGen::SContext *ctx, bool returnLValue) {
	assert(!returnLValue);
	ctx->text.add("; BEGIN - ArrayCreationExpression (" + toCode() + ")");

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

	// check for negative array size
	ctx->text.add("cmp eax, 0; negative array size check");
	ctx->text.addExternSymbol("exception");
	ctx->text.add("jl exception");

	ctx->text.add("push eax"); // pushed number of elements
	ctx->text.addf("add eax, %d", ARRAY_DATA_OFFSET); // multiply by 4 is done next line
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
	ctx->text.addf("mov dword [eax + %d + ebx * 4], 0", ARRAY_DATA_OFFSET * 4);

	ctx->text.add("add ebx, 1");
	ctx->text.addf("jmp %s\n%s:", loopLabel.c_str(), loopOutLabel.c_str());

	ctx->text.add("; END - ArrayCreationExpression (" + toCode() + ")");
}

void MethodInvocation::codeGenerate(CodeGen::SContext *ctx, bool returnLValue) {
	assert(!returnLValue);
	ctx->text.add("; BEGIN - MethodInvocation (" + toCode() + ")");

	auto item = (MethodInvocation*)this;
	CodeGen::SText *text = &ctx->text;

	int numArg = 0;
	if (item->source.index() == 0) {
		// non static method
		auto &lExpr = std::get<0>(item->source);

		// this
		lExpr->codeGenerate(ctx);

		// null check
		ctx->text.addExternSymbol("exception");
		ctx->text.add("cmp eax, 0; null check");
		ctx->text.add("je exception");

		ctx->text.add("push eax");
		++numArg;
	}

	// arguments
	for (auto &arg : item->args) {
		arg->codeGenerate(ctx);
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

		ASSERT(numArg > 0);
		// get "this" pointer
		text->add("mov eax, [esp + " + std::to_string((numArg - 1) * 4) + "]; load \"this\" from args[0]");
		// get class pointer
		text->add("mov eax, [eax + " + std::to_string(OBJECT_CLASS * 4) + "]; load klass ptr");

		int procOffset = (CLASS_SELECTOR + it->second->tableIndex);
		text->add("mov eax, [eax + " + std::to_string(procOffset * 4) + "]; load function ptr");
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

	text->add("add esp, " + std::to_string(numArg * 4) + "; MethodInvocation - pop args");

	ctx->text.add("; END - MethodInvocation (" + toCode() + ")");
}

void AssignmentExpression::codeGenerate(CodeGen::SContext *ctx, bool returnLValue) {
	ctx->text.add("; BEGIN - AssignmentExpression (" + toCode() + ")");

	CodeGen::SText *text = &ctx->text;

	lhs->codeGenerate(ctx, true);
	text->add("push eax");
	text->add("push ebx");
	rhs->codeGenerate(ctx);
	text->add("pop ecx"); // lhs tag
	text->add("pop ebx"); // lhs

	if (lhs->nodeType == NodeType::ArrayAccess) {
		if (lhs->typeResult.isReferenceType()) {
			text->add("push eax"); // rhs
			text->add("push ebx"); // lhs

			strdecl256(endLabel, "assn_skip_null_%d", ++ctx->counter);
			text->addf("cmp eax, 0");
			text->addf("je %s", endLabel);

			ctx->text.addf("mov ebx, [eax + %d]", OBJECT_CLASS * 4); // rhs tag
			ctx->text.addf("mov edx, [ecx + %d]", CLASS_TAG * 4);
			ctx->text.addf("add edx, %lu", ctx->methodTable.size() + 1);
			ctx->text.addf("mov ecx, [edx * 4 + ebx]");
			ctx->text.add("cmp ecx, 0");
			ctx->text.add("je exception");

			text->addf("%s:", endLabel);
			text->add("pop ebx"); // rhs
			text->add("pop eax"); // lhs
		}
	}


	text->add("mov [ebx], eax");
	if (returnLValue)
		text->add("mov eax, ebx");

	ctx->text.add("; END - AssignmentExpression (" + toCode() + ")");
}

void NameExpression::codeGenerate(CodeGen::SContext *ctx, bool returnLValue) {
	converted->codeGenerate(ctx, returnLValue);
}

void genSubtypeCheck(CodeGen::SContext *ctx, const Type *type) {
	// checks if obj in eax is a subtype of type
	// leaves eax unchanged, clobbers ebx and ecx
	int i = 0;
	for (const auto& [k, v] : ctx->typeMap) {
		if (v->asType()->equals(type)) break;
		++i;
	}
	int offset = ctx->methodTable.size() + i + 1;
	ctx->text.addf("mov ebx, [eax + %d]", OBJECT_CLASS * 4);
	ctx->text.addf("mov ecx, [ebx + %d] ; check subtype", offset * 4);
	ctx->text.add("cmp ecx, 0");
	ctx->text.add("je exception");
}

void CastExpression::codeGenerate(CodeGen::SContext *ctx, bool returnLValue) {
	assert(!returnLValue);
	ctx->text.add("; BEGIN - CastExpression (" + toCode() + ")");
	rhs->codeGenerate(ctx, returnLValue);
	ctx->text.addExternSymbol("exception");

	string endLabel;
	strAppend(&endLabel, "end_of_cast_%d", ++ctx->counter);

	// skip null
	ctx->text.add("cmp eax, 0");
	ctx->text.addf("je %s", endLabel.c_str());

	if (type->isArray) {
		if (rhs->typeResult.isArray) {
			// check assignability of element types
			if (type->nodeType == NodeType::NameType) {
				// casting to NameType array (NameType guaranteed)

				// throw if rhs points to primitive array
				for (const auto& prim : getPrimitiveTypes()) {
					ctx->text.addExternSymbol(prim + "_typeinfo");
					ctx->text.addf("cmp dword [eax + %d], %s_typeinfo", OBJECT_CLASS * 4, prim.c_str());
					ctx->text.addf("je exception");
				}

				genSubtypeCheck(ctx, type.get());

			} else {
				// casting to primitive array, rhs guaranteed to be valid
			}
		} else {
			// guaranteed to be Object/Cloneable/Serializable, to follow reference

			// throw if rhs does not point to array type
			ctx->text.addf("cmp dword [eax + %d], 0", OBJECT_ISARRAY * 4);
			ctx->text.addf("je exception");

			// check assignability of element types
			if (type->nodeType == NodeType::NameType) {
				// casting to NameType array

				// throw if rhs points to primitive array
				for (const auto& prim : getPrimitiveTypes()) {
					ctx->text.addExternSymbol(prim + "_typeinfo");
					ctx->text.addf("cmp dword [eax + %d], %s_typeinfo", OBJECT_CLASS * 4, prim.c_str());
					ctx->text.addf("je exception");
				}

				genSubtypeCheck(ctx, type.get());

			} else {
				// casting to primitive array
				const auto& prim = static_cast<PrimitiveType*>(type.get());
				switch (prim->type) {
					case PrimitiveType::Variant::Int:
						ctx->text.addExternSymbol("_Int_typeinfo");
						ctx->text.addf("cmp dword [eax + %d], _Int_typeinfo", OBJECT_CLASS * 4);
						break;
					case PrimitiveType::Variant::Short:
						ctx->text.addExternSymbol("_Short_typeinfo");
						ctx->text.addf("cmp dword [eax + %d], _Short_typeinfo", OBJECT_CLASS * 4);
						break;
					case PrimitiveType::Variant::Byte:
						ctx->text.addExternSymbol("_Byte_typeinfo");
						ctx->text.addf("cmp dword [eax + %d], _Byte_typeinfo", OBJECT_CLASS * 4);
						break;
					case PrimitiveType::Variant::Char:
						ctx->text.addExternSymbol("_Char_typeinfo");
						ctx->text.addf("cmp dword [eax + %d], _Char_typeinfo", OBJECT_CLASS * 4);
						break;
					case PrimitiveType::Variant::Boolean:
						ctx->text.addExternSymbol("_Boolean_typeinfo");
						ctx->text.addf("cmp dword [eax + %d], _Boolean_typeinfo", OBJECT_CLASS * 4);
						break;
					case PrimitiveType::Variant::Void:
						break;
					default:
						ASSERT(false);
						break;
				}
				ctx->text.addf("jne exception");
			}
		}
	} else {
		if (type->nodeType == NodeType::NameType) {
			const auto& decl = static_cast<NameType*>(type.get())->declaration;
			if (decl->fqn != "java.lang.Object" &&
				decl->fqn != "java.lang.Cloneable" &&
				decl->fqn != "java.io.Serializable") {
				// rhs is guaranteed to be a non-array NameType

				genSubtypeCheck(ctx, type.get());
			}
		}
	}
	ctx->text.addf("%s:", endLabel.c_str());
	ctx->text.add("; END - CastExpression (" + toCode() + ")");
}

void FieldAccess::codeGenerate(CodeGen::SContext *ctx, bool returnLValue) {
	CodeGen::SText *text = &ctx->text;

	int varIndex = source.index();

	if (varIndex == 1) {
		// static field

		auto &nameType = std::get<1>(source);
		ASSERT(nameType->nodeType == NodeType::NameType);

		std::string label = nameType->declaration->fqn + "." + member;
		ctx->text.addExternSymbol(label);
		if (returnLValue)
			text->add("mov eax, " + label + "; FieldAccess (" + toCode() + ")");
		else
			text->add("mov eax, [" + label + "]; FieldAccess (" + toCode() + ")");
    return;
	}

	// arbitrary expr
	auto &lExpr = std::get<0>(source);
	lExpr->codeGenerate(ctx);

	// null check
	text->addExternSymbol("exception");
	text->add("cmp eax, 0; null check");
	text->add("je exception");

	TypeResult *theTypeResult = &lExpr->typeResult;

	if (theTypeResult->isArray) {
		// array
		ASSERT(member == "length");

		// length is the first field
		if (returnLValue)
			text->add("add eax, " + std::to_string(OBJECT_FIELD * 4) + "; FieldAccess (" + toCode() + ")");
		else
			text->add("mov eax, [eax + " + std::to_string(OBJECT_FIELD * 4) + "]; FieldAccess (" + toCode() + ")");
		return;
	}

	// non array
	ASSERT(!theTypeResult->isPrimitive);

	if (returnLValue)
		text->add("add eax, " + std::to_string((decl->varDecl->index + OBJECT_FIELD) * 4) + "; FieldAccess (" + toCode() + ")");
	else
		text->add("mov eax, [eax + " + std::to_string((decl->varDecl->index + OBJECT_FIELD) * 4) + "]; FieldAccess (" + toCode() + ")");
}

void LocalVariableExpression::codeGenerate(CodeGen::SContext *ctx, bool returnLValue) {
	// have to adjust by +/- 1 because ebp and eip get pushed between the parameters and the local variables
	// whether we adjust by +1 or -1 depends on whether it's a local variable or parameter
	int offset = ctx->_numParam - declaration->index + (declaration->index < ctx->_numParam ? 1 : -1);
	if (returnLValue)
	{
		ctx->text.add("; BEGIN - LocalVariableExpression (" + toCode() + ")");
		ctx->text.add("mov eax, ebp");
		ctx->text.add("add eax, " + std::to_string(offset * 4));
		ctx->text.add("; END - LocalVariableExpression (" + toCode() + ")");
	}
	else
	{
		ctx->text.add("mov eax, [ebp + " + std::to_string(offset * 4) + "]; LocalVariableExpression (" + toCode() + ")");
	}
}

void ClassInstanceCreationExpression::codeGenerate(CodeGen::SContext *ctx, bool returnLValue) {
	assert(!returnLValue);
	ctx->text.add("; BEGIN - ClassInstanceCreationExpression (" + toCode() + ")");

	TypeDeclaration *typeDecl = this->type->declaration;

	codeGenClassInstanceCreatePreamble(ctx, typeDecl);

	int numArg = 0;
	ctx->text.add("push eax"); ++numArg;

	for (auto &arg : this->args) {
		arg->codeGenerate(ctx);
		ctx->text.add("push eax");
		++numArg;
	}

	ctx->text.call("%s", getProcedureName(this->declaration).c_str());

	codeGenClassInstanceCreateEpilogue(ctx, numArg);

	ctx->text.add("; END - ClassInstanceCreationExpression (" + toCode() + ")");
}

void ArrayAccess::codeGenerate(CodeGen::SContext *ctx, bool returnLValue) {
	ctx->text.add("; BEGIN - ArrayAccess (" + toCode() + ")");

	this->array->codeGenerate(ctx);

	//null array check
	ctx->text.addExternSymbol("exception");
	ctx->text.add("cmp eax, 0; null check");
	ctx->text.add("je exception;");

	ctx->text.add("push eax");
	this->index->codeGenerate(ctx);
	ctx->text.add("pop ebx");

	// runtime bounds check
	ctx->text.addf("mov ecx, [ebx + %d]; array length", ARRAY_LENGTH_OFFSET * 4);
	ctx->text.add("cmp eax, ecx; array bounds check");
	ctx->text.addExternSymbol("exception");
	ctx->text.add("jge exception");

	ctx->text.add("cmp eax, 0; negative index check");
	ctx->text.add("jl exception");

	ctx->text.addf("lea eax, [ebx + %d + eax * 4]", ARRAY_DATA_OFFSET * 4);
	if (!returnLValue) {
		ctx->text.add("mov eax, [eax]");
	}

	// set ebx to type tag, to be used in AssignmentExpression::codeGenerate
	if (returnLValue && typeResult.isReferenceType()) {
		ctx->text.addf("mov ebx, [ebx + %d]", OBJECT_CLASS * 4);
	}

	ctx->text.add("; END - ArrayAccess (" + toCode() + ")");
}

//////////////////////////////////////////////////////////////////////////////
//
// Statement
//
//////////////////////////////////////////////////////////////////////////////

void LocalVariableDeclarationStatement::codeGenerate(CodeGen::SContext *ctx) {
	// TODO: add subtype check
	ctx->text.add("; BEGIN - LocalVariableDeclarationStatement (" + toCode() + ")");

	if (!this->declaration->initializer) {
		ctx->text.add("mov dword eax, 0");
	} else {
		this->declaration->initializer->codeGenerate(ctx);
	}
	ctx->text.add("push eax");

	++ctx->stackSize;
	ctx->text.add("; END - LocalVariableDeclarationStatement (" + toCode() + ")");
}

void ExpressionStatement::codeGenerate(CodeGen::SContext *ctx) {
	if (!expression)
		return;
	expression->codeGenerate(ctx);
}

void Block::codeGenerate(CodeGen::SContext *ctx) {
	ctx->text.add("; BEGIN - Block");
	int stackSizeAtStart = ctx->stackSize;

	for (auto &stmt : statements) {
		stmt->codeGenerate(ctx);
	}

	if (ctx->stackSize != stackSizeAtStart)
	{
		// reset the stack to where it was before the start of this block
		int delta = (ctx->stackSize - stackSizeAtStart) * 4;
		ctx->text.add("add esp, " + std::to_string(delta) + "; END - Block (pop local variables)");
		ctx->stackSize = stackSizeAtStart;
	} else
	{
		ctx->text.add("; END - Block");
	}
}

} // namespace AST


