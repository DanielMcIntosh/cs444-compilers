#pragma once

#include "ast/node.h"
#include "ast/modifier.h"
#include <vector>
#include <memory>
#include <string>

namespace AST
{

class MemberDeclaration: public Node
{
public:
	static std::unique_ptr<MemberDeclaration> create(const Parse::Tree *ptNode);

	std::vector<std::unique_ptr<Modifier>> modifiers;
	std::string identifier;
protected:
	MemberDeclaration(const Parse::TModifiers *ptModifiers, std::string const& id);
};

} //namespace AST
