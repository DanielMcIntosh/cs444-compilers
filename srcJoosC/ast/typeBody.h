#pragma once

#include "ast/node.h"
#include <memory>
#include <vector>

namespace AST
{

class MemberDeclaration;

class TypeBody: public Node
{
public:
	std::vector<std::unique_ptr<MemberDeclaration>> members;

	static std::unique_ptr<TypeBody> create(const Parse::Tree *ptNode);
	explicit TypeBody(const Parse::TClassBody *ptNode);
	explicit TypeBody(const Parse::TInterfaceBody *ptNode);

	std::string toCode() const override;
};

} //namespace AST
