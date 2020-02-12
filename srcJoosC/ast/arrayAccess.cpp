#include "ast/arrayAccess.h"
#include "ast/expression.h"
#include "parse/parseTree.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<ArrayAccess> ArrayAccess::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::ArrayAccess:
		return std::make_unique<ArrayAccess>(static_cast<const Parse::TArrayAccess*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for ArrayAccess: " + std::to_string((int)ptNode->type));
	}
}
ArrayAccess::ArrayAccess(const Parse::TArrayAccess *ptNode)
{
}

} //namespace AST
