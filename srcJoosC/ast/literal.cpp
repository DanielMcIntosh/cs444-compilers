#include "ast/literal.h"
#include "parse/parseTree.h"

namespace AST
{

// static
std::unique_ptr<Literal> Literal::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (ptNode->oneNt)
	{
		return Literal::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::Literal:
		return std::make_unique<Literal>(static_cast<const Parse::TLiteral*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for Literal: " + std::to_string((int)ptNode->type));
	}
}
Literal::Literal(const Parse::TLiteral *ptNode)
{
}

} //namespace AST
