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
		throw std::runtime_error("inappropriate PT type for MethodInvocation: " + std::to_string((int)ptNode->type));
	}
}
MethodInvocation::MethodInvocation(const Parse::TMethodInvocation *ptNode)
{
	/*
	int cur = 0;
	// Primary.Identifier() or Primary.Identifier(ArgList)
	if (children[1].lexeme == ".")
	{
		obj = std::dynamic_pointer_cast<Primary>(children[cur++].astNode);
		++cur; // dot
		identifier = children[cur++].lexeme;
	} else
	{
		identifier = std::dynamic_pointer_cast<Name>(children[cur++].astNode);
	}
	++cur; // open paren
	if (!Parser::isTerminal(children[cur].sym))
	{
		auto argList = std::dynamic_pointer_cast<ArgumentList>(children[cur++].astNode);
		args = argList->list;
	}
	++cur; //close paren
	*/
}

} //namespace AST
