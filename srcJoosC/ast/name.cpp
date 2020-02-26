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
	nodeType = NodeType::Name;
	if (ptNode->name)
	{
		Name pre = Name(ptNode->name);
		prefix = std::move(pre.prefix);
		prefix.push_back(std::move(pre.id));
	}
}

Name::Name(std::vector<std::string> pre, std::string identifier)
  :	prefix(std::move(pre)),
	id(std::move(identifier))
{
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

// pre-compute typePrefix in case expression-resolution reaches rule 3 and has to resolve a_1.a_2. ... a_k to a Type
SemanticErrorType Name::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	std::vector<std::string> curPrefix;
	for (std::string str : prefix)
	{
		// leverage NameType's type resolution
		auto temp = std::make_unique<NameType>(Name(curPrefix, str));
		if (temp->resolve(semantic, enclosingClass) == SemanticErrorType::None)
		{
			typePrefix = std::move(temp);
			return SemanticErrorType::None;
		}

		curPrefix.push_back(str);
	}

	// Nothing in prefix resolved to a type, try the whole thing
	auto temp = std::make_unique<NameType>(*this);
	if (temp->resolve(semantic, enclosingClass) == SemanticErrorType::None)
	{
		typePrefix = std::move(temp);
		return SemanticErrorType::None;
	}

	// even if we fail to resolve a type prefix, we can't return an error, because we might still be a valid expression
	return SemanticErrorType::None;
}

SemanticErrorType Name::resolveExprs(Semantic::Scope const& parentScope)
{
	// TODO:
	return SemanticErrorType::None;
}

bool Name::operator==(const Name &other) {
	return prefix == other.prefix && id == other.id;
}

} //namespace AST
