#include "semantic.h"

#include <utility>
#include <algorithm>
#include <unordered_set>

#include "ast/compilationUnit.h"
#include "ast/typeDeclaration.h"
#include "ast/fieldDeclaration.h"
#include "ast/variableDeclaration.h"
#include "ast/methodDeclaration.h"
#include "ast/constructorDeclaration.h"

namespace Semantic {

const char *gSemanticErrorTypeName[] = {
	"None",
	"SingleImportAmbiguous",
	"MultiImportAmbiguous",
	"NotFoundImport",
	"MultipleDefinitionOfClassInterface",
	"CycleInHierarchy",
	"ImplementSameInterface",
	"ExtendImplementSame",
	"ImplementNonInterface",
	"ExtendNonClass",
	"ExtendClass",
	"ExtendFinalClass",
};

static_assert(static_cast<int>(SemanticErrorType::Max) == ARRAY_SIZE(gSemanticErrorTypeName));

void semanticInit(SemanticDB *db, const vector<FrontendResult> &frontendResult) {
	for (auto &result: frontendResult) {
		auto *cpu = dynamic_cast<CompilationUnit *>(result.astResult.ast.get());
		ASSERT(cpu);
		db->cpus.push_back(cpu);
	}
}

string flatten(const vector<string> &list, const string &str) {
	string res;
	for (const auto &s : list) {
		res.append(s);
		res.append(".");
	}
	res.append(str);
	return res;
}

struct DagSortContext {
	unordered_set<TypeDeclaration *> visited;
	unordered_set<TypeDeclaration *> tempVisited;
	vector<TypeDeclaration *> result;
	bool failed = false;
};

void dagSortHelper(TypeDeclaration *type, DagSortContext *ctx) {
	if (ctx->visited.count(type))
		return;

	if (ctx->tempVisited.count(type)) {
		ctx->failed = true;
		return;
	}

	ctx->tempVisited.insert(type);

	for (auto *child : type->children) {
		dagSortHelper(child, ctx);
	}

	ctx->tempVisited.erase(type);
	ctx->visited.insert(type);
	ctx->result.push_back(type);
}

bool dagSort(vector<TypeDeclaration *> *allTypes) {
	DagSortContext ctx;
	for (auto *type : *allTypes) {
		if (ctx.visited.count(type))
			continue;

		dagSortHelper(type, &ctx);
	}

	if (ctx.failed)
		return false;

	reverse(ctx.result.begin(), ctx.result.end());
	*allTypes = ctx.result;
	return true;
}

enum SemanticErrorType semanticResolveType(SemanticDB *db, Type *type, const string &typeName,
                                           const CompilationUnit *cpu, TypeDeclaration *source) {
	if (typeName.find('.') != string::npos)  { // qualified name
		auto it = db->typeMap.find(typeName);
		if (it == db->typeMap.end())
			return SemanticErrorType::NotFoundImport;

		type->decl = it->second;
		return SemanticErrorType::None;
	}

	// simple name
	// 1. enclosing class/interface
	{
		if (typeName == source->name) {
			type->decl = source;
			return SemanticErrorType::None;
		}
	}
	//
	// 2. single import
	{
		bool found = false;
		for (auto &imp : cpu->imports) {
			if (imp->multiImport)
				continue;

			if (imp->importName->id != typeName)
				continue;

			string fullImp = flatten(imp->importName->prefix, imp->importName->id);
			auto it = db->typeMap.find(fullImp);
			if (it == db->typeMap.end())
				continue;

			if (found)
				return SemanticErrorType::SingleImportAmbiguous;

			type->decl = it->second;
			found = true;
		}

		if (found)
			return SemanticErrorType::None;
	}
	//
	// 3. same package
	{
		string fullImp = cpu->packageName + string(".") + typeName;
		auto it = db->typeMap.find(fullImp);
		if (it != db->typeMap.end()) {
			type->decl = it->second;
			return SemanticErrorType::None;
		}
	}
	//
	// 4. multi import
	{
		bool found = false;
		for (auto &imp : cpu->imports) {
			if (!imp->multiImport)
				continue;

			string fullImp = flatten(imp->importName->prefix, imp->importName->id) + "." + typeName;
			auto it = db->typeMap.find(fullImp);
			if (it == db->typeMap.end())
				continue;

			if (found)
				return SemanticErrorType::MultiImportAmbiguous;

			type->decl = it->second;
			found = true;
		}

		if (found)
			return SemanticErrorType::None;
	}

	return SemanticErrorType::NotFoundImport;
}

SemanticErrorType semanticeResolveTypesInClass(SemanticDB *db, TypeDeclaration *type, 
																	const CompilationUnit *cpu) {
	for (auto &member : type->members) {
		auto *field = dynamic_cast<FieldDeclaration *>(member.get());
		if (field) {
			SemanticErrorType error = field->type->resolve(db, cpu, type);
			if (error != SemanticErrorType::None)
				return error;
			continue;
		}

		auto *method = dynamic_cast<MethodDeclaration *>(member.get());
		if (method) {
			if (method->returnType) {
				SemanticErrorType error = method->returnType->resolve(db, cpu, type);
				if (error != SemanticErrorType::None)
					return error;				
			}

			for (auto &parameter : method->parameters) {
				SemanticErrorType error = parameter->type->resolve(db, cpu, type);
				if (error != SemanticErrorType::None)
					return error;
			}

			continue;
		}

		auto *ctor = dynamic_cast<ConstructorDeclaration *>(member.get());
		if (ctor) {
			for (auto &parameter : ctor->parameters) {
				SemanticErrorType error = parameter->type->resolve(db, cpu, type);
				if (error != SemanticErrorType::None)
					return error;
			}
			continue;
		}

		ASSERT(false);
	}

	return SemanticErrorType::None;
}

void semanticDo(SemanticDB *sdb) {
	for (auto *cpu: sdb->cpus) {
		cpu->resolveEnclosingPackageAndApplyToTypeDecl();
	}

	for (auto *cpu : sdb->cpus) {
		if (!cpu->typeDeclaration)
			continue;

		auto it = sdb->typeMap.find(cpu->typeDeclaration->fqn);
		if (it != sdb->typeMap.end()) {
			sdb->error = SemanticErrorType::MultipleDefinitionOfClassInterface;
			return;
		}

		sdb->typeMap[cpu->typeDeclaration->fqn] = cpu->typeDeclaration.get();
	}

	for (auto *cpu : sdb->cpus) {
		if (!cpu->typeDeclaration)
			continue;

		{ // inject java.lang.* multiimport
			auto imp = make_unique<ImportDeclaration>();
			auto name = make_unique<Name>();
			name->prefix.push_back("java");
			name->id = "lang";
			imp->multiImport = true;
			imp->importName = move(name);
			cpu->imports.push_back(move(imp));
		}

		TypeDeclaration *type = cpu->typeDeclaration.get();
		if (type->superClass) {
			SemanticErrorType error = type->superClass->resolve(sdb, cpu, type);
			if (error != SemanticErrorType::None) {
				sdb->error = error;
				return;
			}
			type->superClass->decl->children.push_back(type);
		}

		for (auto &itf : type->interfaces) {
			SemanticErrorType error = itf->resolve(sdb, cpu, type);
			if (error != SemanticErrorType::None) {
				sdb->error = error;
				return;
			}
			itf->decl->children.push_back(type);
		}
	}

	{
		vector<TypeDeclaration *> allTypes;
		for (const auto &[name, ptr] : sdb->typeMap) {
			allTypes.push_back(ptr);
		}

		if (!dagSort(&allTypes)) {
			sdb->error = SemanticErrorType::CycleInHierarchy;
			return;
		}

		// Implements formal hierarchy checking algorithm.
		for (auto *type : allTypes) {
			SemanticErrorType error = semanticeResolveTypesInClass(sdb, type, type->cpu);
			if (error != SemanticErrorType::None) {
				sdb->error = error;
				return;
			}

			TypeDeclaration *super = type->superClass ? type->superClass->decl : nullptr;

			//
			// various extends
			//
			unordered_set<TypeDeclaration *> extends;
			for (auto &itf : type->interfaces) {
				if (!type->isInterface && !itf->decl->isInterface) {
					sdb->error = SemanticErrorType::ImplementNonInterface;
					return;
				}

				if (itf->decl == super) {
					sdb->error = SemanticErrorType::ExtendImplementSame;
					return;
				}
				
				auto it = extends.find(itf->decl);
				if (it != extends.end()) {
					sdb->error = SemanticErrorType::ImplementSameInterface;
					return;
				}

				extends.insert(itf->decl);
			}

			//
			// populate initial super set
			//
			unordered_set<TypeDeclaration *> newSuper;
			if (super) {
				if (!type->isInterface && super->isInterface) {
					sdb->error = SemanticErrorType::ExtendNonClass;
					return;
				}

				if (type->isInterface && !super->isInterface) {
					sdb->error = SemanticErrorType::ExtendClass;
					return;
				}

				for (auto &mod : super->modifiers) {
					if (mod->type == Modifier::Variant::Final) {
						sdb->error = SemanticErrorType::ExtendFinalClass;
						return;
					}
				}

				newSuper.insert(super);
				for (TypeDeclaration *decl : super->superSet) {
					newSuper.insert(decl);
				}
			}

			for (auto *ext : extends) {
				newSuper.insert(ext);
				for (TypeDeclaration *decl : ext->superSet) {
					newSuper.insert(decl);
				}
			}

			
		}
	}
}

}
