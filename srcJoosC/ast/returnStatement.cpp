#include "ast/returnStatement.h"
#include "ast/statement.h"
#include "ast/expression.h"
#include "parse/parseTree.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<ReturnStatement> ReturnStatement::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::ReturnStatement:
		return std::make_unique<ReturnStatement>(static_cast<const Parse::TReturnStatement*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for ReturnStatement: " + std::to_string((int)ptNode->type));
	}
}
ReturnStatement::ReturnStatement(const Parse::TReturnStatement *ptNode)
{
}

} //namespace AST
