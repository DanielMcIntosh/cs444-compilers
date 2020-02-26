#pragma once

#include "ast/node.h"
#include "ast/modifier.h"
#include <vector>
#include <memory>
#include <string>

namespace Semantic
{
	struct SemanticDB;
	enum class SemanticErrorType;
	class Scope;
}

namespace AST
{

class Modifier;
class FieldDeclaration;
class MemberDeclaration;
class ConstructorDeclaration;
class MethodDeclaration;
class TypeDeclaration;

class MemberDeclaration: public Node
{
public:
	static std::unique_ptr<MemberDeclaration> create(const Parse::Tree *ptNode);

	virtual bool equals(FieldDeclaration *);
	virtual bool equals(MemberDeclaration *);
	virtual bool equals(ConstructorDeclaration *);
	virtual bool equals(MethodDeclaration *);

	// TODO: temporary, to remove
	virtual int getTypeId() = 0;

	virtual Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) = 0;
	virtual Semantic::SemanticErrorType resolveExprs(Semantic::Scope &parentScope) = 0;
	// temporary - should be removed once we can rely on TypeDeclaration.fieldSets and TypeDeclaration.methodSets
	virtual Semantic::SemanticErrorType initScope(Semantic::Scope &parentScope);

	bool hasModifier(Modifier::Variant) const;
protected:
	MemberDeclaration(std::vector<std::unique_ptr<Modifier>> mods);

	std::vector<std::unique_ptr<Modifier>> modifiers;
	// set for membership testing, including all implicit modifiers
	std::array<bool,static_cast<size_t>(Modifier::Variant::Max)> modifierSet{};
};

} //namespace AST
