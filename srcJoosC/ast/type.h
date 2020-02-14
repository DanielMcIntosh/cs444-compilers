#pragma once

#include "ast/node.h"

#include <string>

namespace AST
{

class TypeDeclaration;

class Type: public Node
{
public:
	static std::unique_ptr<Type> create(const Parse::Tree *ptNode);

	bool isArray = false;

  std::string fqn;
  TypeDeclaration *decl;
protected:
	Type() = default;
};

} //namespace AST
