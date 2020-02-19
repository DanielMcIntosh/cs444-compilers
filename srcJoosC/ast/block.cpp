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
		FAILED("inappropriate PT type for Block: " + std::to_string((int)ptNode->type));
	}
}
Block::Block(const Parse::TBlock *ptNode)
  : statements(std::move(NodeList<Statement>(ptNode->blockStatements).list))
{
}

std::string Block::toCode()
{
	std::string str = "{\n";
	for (auto &stmt : statements)
	{
		str += stmt->toCode() + "\n";
	}
	str += "}";
	return str;
}

} //namespace AST
