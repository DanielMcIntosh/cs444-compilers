#include "semantic.h"

#include <utility>
#include <algorithm>
#include <unordered_set>

namespace Semantic {

const char *gSemanticErrorTypeName[] = {
	"None",
	"SingleImportAmbiguous",
	"MultiImportAmbiguous",
	"NotFoundImport",
	"MultipleDefinitionOfClassInterface",
	"CycleInHierarchy",
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

void setupTypeDependency(NameType *target, TypeDeclaration *decl,
                         TypeDeclaration *source, bool forClass) {
	target->decl = decl;
	if (forClass)
		decl->children.push_back(source);
}

enum SemanticErrorType semanticResolveType(SemanticDB *db, Type *type, const CompilationUnit *cpu,
                                           TypeDeclaration *source, bool forClass) {
	auto *namedType = dynamic_cast<NameType *>(type);
	ASSERT(namedType);
	if (!namedType->prefix.empty())  { // qualified name
		string fqn = flatten(namedType->prefix, namedType->id);
		auto it = db->typeMap.find(fqn);
		if (it == db->typeMap.end())
			return SemanticErrorType::NotFoundImport;

		setupTypeDependency(namedType, it->second, source, forClass);
		return SemanticErrorType::None;
	}

	// simple name
	// 1. enclosing class/interface
	{
		if (namedType->id == source->name) {
			setupTypeDependency(namedType, source, source, forClass);
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

			if (imp->importName->id != namedType->id)
				continue;

			string fullImp = flatten(imp->importName->prefix, imp->importName->id);
			auto it = db->typeMap.find(fullImp);
			if (it == db->typeMap.end())
				continue;

			if (found)
				return SemanticErrorType::SingleImportAmbiguous;

			setupTypeDependency(namedType, it->second, source, forClass);
			found = true;
		}

		if (found)
			return SemanticErrorType::None;
	}
	//
	// 3. same package
	{
		string fullImp = cpu->packageName + string(".") + namedType->id;
		auto it = db->typeMap.find(fullImp);
		if (it != db->typeMap.end()) {
			setupTypeDependency(namedType, it->second, source, forClass);
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

			string fullImp = flatten(imp->importName->prefix, imp->importName->id) + "." + namedType->id;
			auto it = db->typeMap.find(fullImp);
			if (it == db->typeMap.end())
				continue;

			if (found)
				return SemanticErrorType::MultiImportAmbiguous;

			setupTypeDependency(namedType, it->second, source, forClass);
			found = true;
		}

		if (found)
			return SemanticErrorType::None;
	}

	return SemanticErrorType::NotFoundImport;
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
			SemanticErrorType error = semanticResolveType(sdb, type->superClass.get(), cpu, type, true);
			if (error != SemanticErrorType::None) {
				sdb->error = error;
				return;
			}
		}

		for (auto &itf : type->interfaces) {
			SemanticErrorType error = semanticResolveType(sdb, itf.get(), cpu, type, true);
			if (error != SemanticErrorType::None) {
				sdb->error = error;
				return;
			}
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

		}
	}
}

}
