#include "ast/name.h"
#include "ast/expression.h"
#include "ast/type.h"
#include "parse/parseTree.h"
#include <memory>
#include <vector>

namespace AST
{

// static
std::unique_ptr<Name> Name::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (ptNode->oneNt)
	{
		return Name::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::Name:
		return std::make_unique<Name>(static_cast<const Parse::TName*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for Name: " + std::to_string((int)ptNode->type));
	}
}
Name::Name(const Parse::TName *ptNode)
{
}

NameType::NameType(Name &&other)
  : prefix(std::move(other.prefix)),
	id(std::move(other.id))
{
}

NameExpression::NameExpression(Name &&other)
  : prefix(std::move(other.prefix)),
	id(std::move(other.id))
{
}

} //namespace AST
