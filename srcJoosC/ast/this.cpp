#include "ast/this.h"
#include "parse/parseTree.h"

namespace AST
{

// static
std::unique_ptr<This> This::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::This2:
		return std::make_unique<This>(static_cast<const Parse::TThis2*>(ptNode));
	default:
		FAILED("inappropriate PT type for This: " + std::to_string((int)ptNode->type));
	}
}
// mostly a dummy class - the equivalent of the Literal class, but for a "this" expression
This::This(const Parse::TThis2 *ptNode)
{
}

std::string This::toCode() const
{
	return "this";
}

} //namespace AST
