#include "ast/name.h"
#include "ast/expression.h"
#include "ast/type.h"
#include "parse/parseTree.h"

#include <memory>
#include <vector>
#include <algorithm>

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
		throw std::runtime_error("inappropriate PT type for Name: " + std::to_string((int)ptNode->type));
	}
}

Name::Name(const Parse::TName *ptNode)
{
	auto *tree = static_cast<const Parse::Tree *>(ptNode);
	auto ident = ptFindByType(const_cast<Parse::Tree*>(tree), Identifier);
	std::reverse(ident.begin(), ident.end());
	for (size_t i = 0; i < ident.size() - 1; ++i) {
		prefix.push_back(ident[i]->value);
	}
	id = ident.back()->value;
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
