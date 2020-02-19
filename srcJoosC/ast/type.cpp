#include "ast/type.h"
#include "ast/primitiveType.h"
#include "ast/name.h"
#include "parse/parseTreeBase.h"
#include <memory>

namespace AST
{

struct TypeDeclTypeInfo {
	TypeDeclaration *typeDecl;
	vector<Type *> enclosingTypes;
};

struct CPUTypeInfo {
	CompilationUnit *cpu;
	vector<TypeDeclTypeInfo> enclosingTypeDecl;
};

struct TypeManager {
	vector<CPUTypeInfo> cpus;
} gTypeManager;

// static
std::unique_ptr<Type> Type::create(const Parse::Tree *ptNode)
{
	std::unique_ptr<Type> value;
	// Type is never nullable, but "void" doesn't show up in the PT, so we use nullptr to indicate type void
	if (ptNode == nullptr) {
		value = PrimitiveType::create(nullptr);
	} else if (isSingleton(ptNode)) {
		value = Type::create(ptNode->children[0]);
	} else {
		switch(ptNode->type) {
			case Parse::NonTerminalType::ArrayType:
			{
				std::unique_ptr<Type> ret = Type::create(ptNode->children[0]);
				ret->isArray = true;
				value = std::move(ret);
				break;
			}
			case Parse::NonTerminalType::PrimitiveType:
				value = PrimitiveType::create(ptNode);
				break;
			case Parse::NonTerminalType::Name:
				value = std::make_unique<NameType>(std::move(*Name::create(ptNode)));
				break;
			default:
				FAILED("inappropriate PT type for Type: " + std::to_string((int)ptNode->type));
		}

	}

	ASSERT(value);
	gTypeManager.cpus.back().enclosingTypeDecl.back().enclosingTypes.push_back(value.get());
	return value;
}

Semantic::SemanticErrorType Type::resolve(Semantic::SemanticDB *db,
																					const CompilationUnit *cpu,
																					TypeDeclaration *typeDecl) {
	return Semantic::SemanticErrorType::None;
}

void Type::setCurrentCompilationUnit(CompilationUnit *item) {
	gTypeManager.cpus.push_back({item, {}});
}

void Type::setCurrentTypeDeclaration(TypeDeclaration *item) {
	gTypeManager.cpus.back().enclosingTypeDecl.push_back({item, {}});
}

void Type::reset() {
	gTypeManager.cpus.clear();
}

Semantic::SemanticErrorType Type::resolveAllBodyType(Semantic::SemanticDB *db) {
	for (auto &cpu : gTypeManager.cpus) {
		for (auto &typeDecl : cpu.enclosingTypeDecl) {
			for (auto &type : typeDecl.enclosingTypes) {
				if (type->decl)
					continue;
				Semantic::SemanticErrorType error = type->resolve(db, cpu.cpu, typeDecl.typeDecl);
				if (error != Semantic::SemanticErrorType::None)
					return error;
			}
		}
	}
	return Semantic::SemanticErrorType::None;
}

} //namespace AST
