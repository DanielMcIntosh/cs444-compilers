#include "semantic.h"
#include "dagSort.h"
#include "ast/compilationUnit.h"

using namespace std;
using namespace AST;

#include "ast/compilationUnit.h"
#include "ast/typeDeclaration.h"
#include "ast/fieldDeclaration.h"
#include "ast/variableDeclaration.h"
#include "ast/methodDeclaration.h"
#include "ast/name.h"
#include "ast/importDeclaration.h"
#include "ast/modifier.h"
#include "ast/constructorDeclaration.h"
#include <unordered_set>

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
	"TypeDeclarationClashImport",
	"PrefixNameIsType",
	"NotPackage",
	"ExprResolution",
	"DuplicateFieldDeclaration",
	"DuplicateMethodDeclaration",
	"DuplicateConstructorDeclaration",
	"AbstractClassNotAbstract",
	"AmbiguousReturnType",
	"OverrideStatic",
	"OverrideDifferentReturn",
	"OverridePublic",
};

static_assert(static_cast<int>(SemanticErrorType::Max) == ARRAY_SIZE(gSemanticErrorTypeName));

void semanticInit(SemanticDB *db, const vector<FrontendResult> &frontendResult) {
	for (auto &result: frontendResult) {
		auto *cpu = reinterpret_cast<CompilationUnit *>(result.astResult.ast.get());
		db->cpus.push_back(cpu);
	}
}

std::tuple<TypeDeclaration *, SemanticErrorType>
SemanticDB::resolveSingleImport(const CompilationUnit *cpu, const string &simpleName) const
{
	TypeDeclaration *ret = nullptr;
	for (auto &imp : cpu->imports) {
		if (imp->multiImport)
			continue;

		if (imp->importName->id != simpleName)
			continue;

		string fullImp = imp->importName->flatten();
		auto it = typeMap.find(fullImp);
		if (it == typeMap.end())
			continue;

		if (ret != nullptr)
			return {nullptr, SemanticErrorType::SingleImportAmbiguous};

		ret = it->second;
	}

	if (ret != nullptr)
		return {ret, SemanticErrorType::None};

	return {nullptr, SemanticErrorType::NotFoundImport};
}

std::tuple<TypeDeclaration *, SemanticErrorType>
SemanticDB::resolveMultiImport(const CompilationUnit *cpu, const string &simpleName) const
{
	TypeDeclaration *ret = nullptr;
	for (auto &imp : cpu->imports) {
		if (!imp->multiImport)
			continue;

		string fullImp = imp->importName->flatten() + "." + simpleName;
		auto it = typeMap.find(fullImp);
		if (it == typeMap.end())
			continue;

		if (ret != nullptr)
			return {nullptr, SemanticErrorType::MultiImportAmbiguous};

		ret = it->second;
	}

	if (ret != nullptr)
		return {ret, SemanticErrorType::None};

	return {nullptr, SemanticErrorType::NotFoundImport};
}

std::tuple<TypeDeclaration *, SemanticErrorType>
SemanticDB::resolveType(const AST::NameType *type, const AST::CompilationUnit *cpu) const
{
	return resolveTypeHelper(type, type->flatten(), cpu, nullptr);
}

std::tuple<TypeDeclaration *, SemanticErrorType>
SemanticDB::resolveType(const AST::NameType *type, AST::TypeDeclaration *source) const
{
	return resolveTypeHelper(type, type->flatten(), source->cpu, source);
}

std::tuple<TypeDeclaration *, SemanticErrorType>
SemanticDB::resolveTypeHelper(const NameType *type, const string &typeName, const CompilationUnit *cpu, TypeDeclaration *source) const
{
	if (typeName.find('.') != string::npos)  { // qualified name
		auto it = typeMap.find(typeName);
		if (it == typeMap.end())
			return {nullptr, SemanticErrorType::NotFoundImport};

		{
			// check prefix
			auto pos = typeName.rfind('.');
			if (pos != string::npos) {
				auto [decl, err] = resolveTypeHelper(type, typeName.substr(0, pos), cpu, source);
				if (err == SemanticErrorType::None) {
					return {nullptr, SemanticErrorType::PrefixNameIsType};
				}
			}
		}

		return {it->second, SemanticErrorType::None};
	}

	// simple name
	// 1. enclosing class/interface
	{
		if (source && typeName == source->name) {
			return {source, SemanticErrorType::None};
		}
	}
	//
	// 2. single import
	{
		auto [decl, err] = resolveSingleImport(cpu, typeName);
		if (err == SemanticErrorType::None)
			return {decl, err};
		if (err != SemanticErrorType::NotFoundImport)
			return {nullptr, err};
	}
	//
	// 3. same package
	{
		string fullImp = cpu->packageName + string(".") + typeName;
		if (auto it = typeMap.find(fullImp);
			it != typeMap.end())
		{
			return {it->second, SemanticErrorType::None};
		}
	}
	//
	// 4. multi import
	{
		auto [decl, err] = resolveMultiImport(cpu, typeName);
		if (err == SemanticErrorType::None)
			return {decl, err};
		if (err != SemanticErrorType::NotFoundImport)
			return {nullptr, err};
	}

	return {nullptr, SemanticErrorType::NotFoundImport};
}

void semanticDo(SemanticDB *sdb) {
	for (auto *cpu : sdb->cpus) {
		if (!cpu->typeDeclaration)
			continue;

		auto it = sdb->typeMap.find(cpu->typeDeclaration->fqn);
		if (it != sdb->typeMap.end()) {
			sdb->error = SemanticErrorType::MultipleDefinitionOfClassInterface;
			return;
		}

		sdb->typeMap[cpu->typeDeclaration->fqn] = cpu->typeDeclaration.get();

		{
			// build package trie
			char *fqn = strdup(cpu->typeDeclaration->fqn.c_str());
			char *state;
			char *component = strtok_r(fqn, ".", &state);
			Trie *trieHead = &sdb->packageTrie;
			while (component) {
				string name(component);

				bool found = false;
				for (auto &child : trieHead->children) {
					if (child->name == name) {
						trieHead = child.get();
						found = true;
						break;
					}
				}

				if (!found) {
					trieHead->children.push_back(make_unique<Trie>());
					Trie *trie = trieHead->children.back().get();
					trie->theTypeDecl = nullptr;
					trie->name = name;
					trieHead = trieHead->children.back().get();
				}

				component = strtok_r(nullptr, ".", &state);
			}

			trieHead->theTypeDecl = cpu->typeDeclaration.get();
			free(fqn);
		}
	}

	{
		// check the trie
		vector<Trie *> stack{&sdb->packageTrie};
		while (!stack.empty()) {
			Trie *trie = stack.back();
			stack.pop_back();
			if (trie->theTypeDecl && !trie->children.empty()) {
				sdb->error = SemanticErrorType::PrefixNameIsType;
				return;
			}
			for (auto &child : trie->children) {
				stack.push_back(child.get());
			}
		}
	}

	for (auto *cpu : sdb->cpus) {
		if (!cpu->typeDeclaration)
			continue;

		{ // inject java.lang.* multiimport
			auto imp = make_unique<ImportDeclaration>();
			auto name = make_unique<Name>(std::vector<std::string>{"java"}, "lang");
			imp->multiImport = true;
			imp->importName = move(name);
			cpu->imports.push_back(move(imp));
		}

		cpu->importDeduplication();

		{
			// check imports are actually packages
			for (auto &imp : cpu->imports) {
				Trie *trieHead = &sdb->packageTrie;

				vector<string> iter = imp->importName->prefix;
				iter.push_back(imp->importName->id);

				for (auto &component : iter) {
					bool found = false;
					for (auto &child : trieHead->children) {
						if (child->name == component) {
							trieHead = child.get();
							found = true;
							break;
						}
					}

					if (!found || (trieHead->theTypeDecl && imp->multiImport)) {
						sdb->error = SemanticErrorType::NotPackage;
						return;
					}
				}
			}
		}

		{
			// check simple import clash
			unordered_set<string> classes;
			for (auto &imp : cpu->imports) {
				if (imp->multiImport)
					continue;
				if (classes.count(imp->importName->id)) {
					sdb->error = SemanticErrorType::SingleImportAmbiguous;
					return;
				}
				classes.insert(imp->importName->id);
			}
		}

		TypeDeclaration *typeDecl = cpu->typeDeclaration.get();

		// resolve superclass and 'implements' types, and initialize TypeDeclaration::children
		if (SemanticErrorType err = typeDecl->resolveSuperTypeNames(*sdb);
			err != SemanticErrorType::None)
		{
			sdb->error = err;
			return;
		}

		{ // type declaration clash with imports
			if (auto [out, err] = sdb->resolveSingleImport(cpu, typeDecl->name);
				err != SemanticErrorType::NotFoundImport && out != typeDecl)
			{
				sdb->error = SemanticErrorType::TypeDeclarationClashImport;
				return;
			}

			for (auto &import : cpu->imports) {
				if (import->multiImport)
					continue;
				if (import->importName->flatten() == typeDecl->fqn)
					continue;
				if (import->importName->id == typeDecl->name) {
					sdb->error = SemanticErrorType::TypeDeclarationClashImport;
					return;
				}
			}
		}
	}

	vector<TypeDeclaration *> allTypes;
	for (const auto &[name, ptr] : sdb->typeMap) {
		allTypes.push_back(ptr);
	}

	if (!dagSort(allTypes)) {
		sdb->error = SemanticErrorType::CycleInHierarchy;
		return;
	}

	for (auto *typeDecl : allTypes)
	{
		if (SemanticErrorType err = typeDecl->resolveBodyTypeNames(*sdb);
			err != SemanticErrorType::None)
		{
			sdb->error = err;
			return;
		}
	}

	// Generate super, extends, declare
	for (auto *typeDecl : allTypes) {
		if (SemanticErrorType err = typeDecl->generateHierarchySets();
			err != SemanticErrorType::None)
		{
			sdb->error = err;
			return;
		}
	}

	for (auto *typeDecl : allTypes)
	{
		if (SemanticErrorType err = typeDecl->resolveBodyExprs();
			err != SemanticErrorType::None)
		{
			sdb->error = err;
			return;
		}
	}
}

Trie::Trie(): theTypeDecl(nullptr) {

}
}
