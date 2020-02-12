#include "ast/localVariableDeclarationStatement.h"
#include "ast/statement.h"
#include "parse/parseTree.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<LocalVariableDeclarationStatement> LocalVariableDeclarationStatement::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (ptNode->oneNt)
	{
		return LocalVariableDeclarationStatement::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::LocalVariableDeclarationStatement:
		return std::make_unique<LocalVariableDeclarationStatement>(static_cast<const Parse::TLocalVariableDeclarationStatement*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for LocalVariableDeclarationStatement: " + std::to_string((int)ptNode->type));
	}
}
LocalVariableDeclarationStatement::LocalVariableDeclarationStatement(const Parse::TLocalVariableDeclarationStatement *ptNode)
{
}

} //namespace AST