#include "ast/name.h"
#include "ast/expression.h"
#include "ast/type.h"
#include "ast/typeDeclaration.h"
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
	if (isSingleton(ptNode))
	{
		return Name::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::Name:
		return std::make_unique<Name>(static_cast<const Parse::TName*>(ptNode));
	default:
		FAILED("inappropriate PT type for Name: " + std::to_string((int)ptNode->type));
	}
}

Name::Name(const Parse::TName *ptNode)
{
	nodeType = NodeType::Name;
	if (ptNode->name)
	{
		Name pre = Name(ptNode->name);
		ids = std::move(pre.ids);
	}
	ids.push_back(ptNode->identifier->value);
}

Name::Name(std::vector<std::string> idList)
  :	ids(std::move(idList))
{
	assert(!ids.empty());
	nodeType = NodeType::Name;
}

std::string Name::flatten() const
{
	std::string str;
	for (auto &id : ids)
	{
		str += id + ".";
	}
	// pop off the trailing "."
	str.pop_back();
	return str;
}

std::string Name::toCode() const
{
	return flatten();
}

std::string Name::getId() const
{
	return ids.back();
}

bool Name::operator==(const Name &other) {
	return ids == other.ids;
}

} //namespace AST
