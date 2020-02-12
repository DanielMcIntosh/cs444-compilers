#include "ast/abstractMethodBody.h"
#include "parse/parseTree.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<AbstractMethodBody> AbstractMethodBody::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::AbstractMethodBody:
		return std::make_unique<AbstractMethodBody>(static_cast<const Parse::TAbstractMethodBody*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for AbstractMethodBody: " + std::to_string((int)ptNode->type));
	}
}
// mostly a dummy class
AbstractMethodBody::AbstractMethodBody(const Parse::TAbstractMethodBody *ptNode)
{
}

} //namespace AST
