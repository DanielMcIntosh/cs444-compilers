#include "ast/name.h"
#include "ast/expression.h"
#include "ast/type.h"
#include "parse/parseTree.h"
#include "semantic/semantic.h"

#include <memory>
#include <vector>

using Semantic::SemanticErrorType;

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
  : id(ptNode->identifier->value)
{
	if (ptNode->name)
	{
		Name pre = Name(ptNode->name);
		prefix = std::move(pre.prefix);
		prefix.push_back(std::move(pre.id));
	}
}

std::string Name::flatten() const
{
	std::string str;
	for (auto &pre : prefix)
	{
		str += pre + ".";
	}
	str += id;
	return str;
}

std::string Name::toCode() const
{
	return flatten();
}

SemanticErrorType Name::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	return SemanticErrorType::None;
}

bool Name::operator==(const Name &other) {
	return prefix == other.prefix && id == other.id;
}

} //namespace AST
