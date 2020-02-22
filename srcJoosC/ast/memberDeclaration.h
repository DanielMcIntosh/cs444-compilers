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
}

namespace AST
{

class FieldDeclaration;
class MemberDeclaration;
class ConstructorDeclaration;
class MethodDeclaration;
class TypeDeclaration;

class MemberDeclaration: public Node
{
public:
	static std::unique_ptr<MemberDeclaration> create(const Parse::Tree *ptNode);

	std::vector<std::unique_ptr<Modifier>> modifiers;

	virtual bool equals(FieldDeclaration *) = 0;
	virtual bool equals(MemberDeclaration *) = 0;
	virtual bool equals(ConstructorDeclaration *) = 0;
	virtual bool equals(MethodDeclaration *) = 0;

	virtual Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) = 0;
protected:
	MemberDeclaration(std::vector<std::unique_ptr<Modifier>> mods);
};

} //namespace AST
