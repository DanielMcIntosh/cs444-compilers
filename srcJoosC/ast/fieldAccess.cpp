#include "ast/fieldAccess.h"
#include "parse/parseTree.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<FieldAccess> FieldAccess::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (ptNode->oneNt)
	{
		return FieldAccess::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::FieldAccess:
		return std::make_unique<FieldAccess>(static_cast<const Parse::TFieldAccess*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for FieldAccess: " + std::to_string((int)ptNode->type));
	}
}
FieldAccess::FieldAccess(const Parse::TFieldAccess *ptNode)
{
}

} //namespace AST
