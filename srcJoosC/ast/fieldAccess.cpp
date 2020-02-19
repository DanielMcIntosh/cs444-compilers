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
	switch(ptNode->type) {
	case Parse::NonTerminalType::FieldAccess:
		return std::make_unique<FieldAccess>(static_cast<const Parse::TFieldAccess*>(ptNode));
	default:
		FAILED("inappropriate PT type for FieldAccess: " + std::to_string((int)ptNode->type));
	}
}
FieldAccess::FieldAccess(const Parse::TFieldAccess *ptNode)
  : object(Expression::create(ptNode->primary)),
	member(ptNode->identifier->value)
{
}

std::string FieldAccess::toCode()
{
	return "(" + object->toCode() + "." + member + ")";
}

} //namespace AST
