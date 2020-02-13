#include "ast/block.h"
#include "ast/statement.h"
#include "ast/nodeList.h"
#include "parse/parseTree.h"

#include "utility.h"

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
		throw std::runtime_error("inappropriate PT type for Block: " + std::to_string((int)ptNode->type));
	}
}
Block::Block(const Parse::TBlock *ptNode)
{
	switch (ptNode->v) {
		case Parse::TBlockV::LCBrRCBr:
			break;
		case Parse::TBlockV::LCBrBlockStatementsRCBr:
			statements = std::move(NodeList<Statement>::create(ptNode->blockStatements)->list);
			break;
		default:
			ASSERT(false);
	}
}

} //namespace AST
