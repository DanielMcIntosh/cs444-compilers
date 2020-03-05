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

	[[gnu::pure]]
	virtual bool equals(const FieldDeclaration *) const;
	[[gnu::pure]]
	virtual bool equals(const MemberDeclaration *) const;
	[[gnu::pure]]
	virtual bool equals(const ConstructorDeclaration *) const;
	[[gnu::pure]]
	virtual bool equals(const MethodDeclaration *) const;

	virtual Semantic::SemanticErrorType resolveTypes(Semantic::SemanticDB const& semantic) = 0;
	virtual Semantic::SemanticErrorType resolveExprs() = 0;

	bool hasModifier(Modifier::Variant) const;


  //
  // a4
  //

  virtual void staticAnalysis(StaticAnalysisCtx *ctx);
  
protected:
	explicit MemberDeclaration(std::vector<std::unique_ptr<Modifier>> mods);


protected:
	std::vector<std::unique_ptr<Modifier>> modifiers;
	// set for membership testing, including all implicit modifiers
	std::array<bool,static_cast<size_t>(Modifier::Variant::Max)> modifierSet{};
public:
	TypeDeclaration *_enclosingClass;
};

} //namespace AST
