#include "ast/name.h"
#include "ast/expression.h"
#include "ast/type.h"
#include "ast/typeDeclaration.h"
#include "parse/parseTree.h"
#include "semantic/semantic.h"
#include "semantic/scope.h"

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

// pre-compute typePrefix in case expression-resolution reaches rule 3 and has to resolve a_1.a_2. ... a_k to a Type
SemanticErrorType Name::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	std::vector<std::string> curPrefix;
	for (std::string str : ids)
	{
		curPrefix.push_back(str);
		// leverage NameType's type resolution
		auto temp = std::make_unique<NameType>(Name(curPrefix));
		if (temp->resolve(semantic, enclosingClass) == SemanticErrorType::None)
		{
			typePrefix = std::move(temp);
			return SemanticErrorType::None;
		}
	}

	// even if we fail to resolve a type prefix, we can't return an error, because we might still be a valid expression
	return SemanticErrorType::None;
}

SemanticErrorType Name::resolveExprs(Semantic::Scope const& scope)
{
	// TODO:
	return SemanticErrorType::None;
}

bool Name::operator==(const Name &other) {
	return ids == other.ids;
}

} //namespace AST
