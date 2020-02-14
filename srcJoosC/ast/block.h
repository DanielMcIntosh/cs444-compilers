#pragma once

#include "ast/statement.h"
#include <memory>
#include <vector>

namespace AST
{

class Block: public Statement
{
public:
	static std::unique_ptr<Block> create(const Parse::Tree *ptNode);
	Block(const Parse::TBlock *ptNode);

	std::vector<std::unique_ptr<Statement>> statements;

	std::string toCode() override;
};

} //namespace AST
