#pragma once

#include "ast/memberDeclaration.h"
#include "ast/type.h"
#include "ast/expression.h"
#include "ast/variableDeclarator.h"
#include <memory>

namespace AST
{

class FieldDeclaration: public MemberDeclaration
{
public:
	static std::unique_ptr<FieldDeclaration> create(const Parse::Tree *ptNode);
	explicit FieldDeclaration(const Parse::TFieldDeclaration *ptNode);

	// maybe change this to hold a VariableDeclaration instead?
	// would have to remove identifier from MemberDeclaration so we don't inherit an extra identifier
	std::unique_ptr<Type> type;
	// nullable
	std::unique_ptr<Expression> initializer;

	std::string toCode() override;

  virtual bool equals(FieldDeclaration *) override;
  virtual bool equals(MemberDeclaration *) override;
  virtual bool equals(ConstructorDeclaration *) override;
  virtual bool equals(MethodDeclaration *) override;
private:
	FieldDeclaration(std::vector<std::unique_ptr<Modifier>> mods, VariableDeclarator &&declarator, std::unique_ptr<Type> t);
};

} //namespace AST
