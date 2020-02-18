#pragma once

#include "ast/memberDeclaration.h"
#include "ast/variableDeclaration.h"
#include "ast/block.h"
#include <memory>

namespace AST
{
class MethodDeclarator;

class ConstructorDeclaration: public MemberDeclaration
{
public:
	static std::unique_ptr<ConstructorDeclaration> create(const Parse::Tree *ptNode);
	explicit ConstructorDeclaration(const Parse::TConstructorDeclaration *ptNode);

	std::vector<std::unique_ptr<VariableDeclaration>> parameters;
	std::unique_ptr<Block> body;

	std::string toCode() override;

  virtual bool equals(FieldDeclaration *) override;
  virtual bool equals(MemberDeclaration *) override;
  virtual bool equals(ConstructorDeclaration *) override;
  virtual bool equals(MethodDeclaration *) override;
private:
	// not convinced this is the best way of dealing with needing 2 members from declarator
	ConstructorDeclaration(std::vector<std::unique_ptr<Modifier>> mods, MethodDeclarator &&declarator, std::unique_ptr<Block> block);
};

} //namespace AST
