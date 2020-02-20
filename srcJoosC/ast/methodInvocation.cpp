#include "ast/methodInvocation.h"
#include "ast/name.h"
#include "ast/expression.h"
#include "ast/nodeList.h"
#include "parse/parseTree.h"
#include <memory>
#include <vector>

namespace AST
{

// static
std::unique_ptr<MethodInvocation> MethodInvocation::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::MethodInvocation:
		return std::make_unique<MethodInvocation>(static_cast<const Parse::TMethodInvocation*>(ptNode));
	default:
		FAILED("inappropriate PT type for MethodInvocation: " + std::to_string((int)ptNode->type));
	}
}
MethodInvocation::MethodInvocation(const Parse::TMethodInvocation *ptNode)
  : args(std::move(NodeList<Expression>(ptNode->argumentList).list))
{
	if (ptNode->name != nullptr)
	{
		identifier = Name::create(ptNode->name);
	} else
	{
		obj = Expression::create(ptNode->primary);
		identifier = ptNode->identifier->value;
	}
}

std::string MethodInvocation::toCode() const
{
	std::string str = "(";
	if (obj)
	{
		str += obj->toCode() + ".";
		str += std::get<std::string>(identifier);
	} else
	{
		str += std::get<std::unique_ptr<Name>>(identifier)->toCode();
	}
	str += "(";
	for (auto &arg : args)
	{
		str += arg->toCode() + ", ";
	}
	// pop the extra ", "
	if (!args.empty())
	{
		str.pop_back();
		str.pop_back();
	}
	str += "))";
	return str;
}

} //namespace AST
