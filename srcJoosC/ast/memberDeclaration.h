#pragma once

#include "ast/node.h"
#include "ast/modifier.h"
#include <vector>
#include <memory>
#include <string>

namespace AST
{

class FieldDeclaration;
class MemberDeclaration;
class ConstructorDeclaration;
class MethodDeclaration;

class MemberDeclaration: public Node
{
public:
	static std::unique_ptr<MemberDeclaration> create(const Parse::Tree *ptNode);

	std::vector<std::unique_ptr<Modifier>> modifiers;
	std::string identifier;

  virtual bool equals(FieldDeclaration *) = 0;
  virtual bool equals(MemberDeclaration *) = 0;
  virtual bool equals(ConstructorDeclaration *) = 0;
  virtual bool equals(MethodDeclaration *) = 0;
protected:
	MemberDeclaration(std::vector<std::unique_ptr<Modifier>> mods, std::string id);
};

} //namespace AST
