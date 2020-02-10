#include "ast/methodHeader.h"
#include "ast/node.h"
#include "ast/modifier.h"
#include "ast/methodDeclarator.h"
#include "parse/parseTree.h"
#include <vector>
#include <memory>

namespace AST
{

// static
std::unique_ptr<MethodHeader> MethodHeader::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (ptNode->oneNt)
	{
		return MethodHeader::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::MethodHeader:
		return std::make_unique<MethodHeader>(static_cast<const Parse::TMethodHeader*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for MethodHeader: " + std::to_string((int)ptNode->type));
	}
}
MethodHeader::MethodHeader(const Parse::TMethodHeader *ptNode)
{
}

} //namespace AST
