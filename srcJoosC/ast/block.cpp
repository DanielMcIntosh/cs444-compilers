#include "ast/block.h"
#include "ast/statement.h"
#include "parse/parseTree.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<Block> Block::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::Block:
		return std::make_unique<Block>(static_cast<const Parse::TBlock*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for Block: " + std::to_string((int)ptNode->type));
	}
}
Block::Block(const Parse::TBlock *ptNode)
{
}

} //namespace AST
