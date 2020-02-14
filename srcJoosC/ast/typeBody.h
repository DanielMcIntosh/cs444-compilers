#pragma once

#include "ast/node.h"
#include "ast/memberDeclaration.h"
#include <memory>
#include <vector>

namespace AST
{

class TypeBody: public Node
{
public:
	std::vector<std::unique_ptr<MemberDeclaration>> members;

	static std::unique_ptr<TypeBody> create(const Parse::Tree *ptNode);
	explicit TypeBody(const Parse::TClassBody *ptNode);
	explicit TypeBody(const Parse::TInterfaceBody *ptNode);

	std::string toCode() override;
};

} //namespace AST
