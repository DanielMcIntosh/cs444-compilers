#include "ast/statement.h"
#include "ast/block.h"
#include "ast/expressionStatement.h"
#include "ast/localVariableDeclarationStatement.h"
#include "ast/returnStatement.h"
#include "ast/conditionalStatement.h"
#include "ast/forStatement.h"
#include "ast/ifThenElseStatement.h"
#include "parse/parseTreeBase.h"
#include "semantic/semantic.h"

namespace AST
{

// static
std::unique_ptr<Statement> Statement::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (isSingleton(ptNode))
	{
		return Statement::create(ptNode->children[0]);
	}

	switch(ptNode->type) {
		case Parse::NonTerminalType::Block:
			return Block::create(ptNode);
		case Parse::NonTerminalType::ExpressionStatement:
			return ExpressionStatement::create(ptNode);
		case Parse::NonTerminalType::LocalVariableDeclarationStatement:
			return LocalVariableDeclarationStatement::create(ptNode);
		case Parse::NonTerminalType::ReturnStatement:
			return ReturnStatement::create(ptNode);
		case Parse::NonTerminalType::IfThenStatement:
		case Parse::NonTerminalType::WhileStatement:
		case Parse::NonTerminalType::WhileStatementNoShortIf:
			return ConditionalStatement::create(ptNode);
		case Parse::NonTerminalType::ForStatement:
		case Parse::NonTerminalType::ForStatementNoShortIf:
			return ForStatement::create(ptNode);
		case Parse::NonTerminalType::IfThenElseStatement:
		case Parse::NonTerminalType::IfThenElseStatementNoShortIf:
			return IfThenElseStatement::create(ptNode);
		default:
			FAILED("inappropriate PT type for Statement: " + std::to_string((int)ptNode->type));
	}
}

Semantic::SemanticErrorType Statement::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *source)
{
	return Semantic::SemanticErrorType::None;
}

} //namespace AST
