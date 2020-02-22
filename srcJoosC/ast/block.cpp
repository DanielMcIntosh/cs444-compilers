#include "ast/block.h"
#include "ast/statement.h"
#include "ast/nodeList.h"
#include "parse/parseTree.h"
#include "semantic/semantic.h"

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

std::string Block::toCode() const
{
	std::string str = "{\n";
	for (auto &stmt : statements)
	{
		str += stmt->toCode() + "\n";
	}
	str += "}";
	return str;
}

Semantic::SemanticErrorType Block::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	for (auto &stmt: statements)
	{
		if (Semantic::SemanticErrorType err = stmt->resolveTypes(semantic, enclosingClass);
			err != Semantic::SemanticErrorType::None)
		{
			return err;
		}
	}
	return Semantic::SemanticErrorType::None;
}

} //namespace AST
