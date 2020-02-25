#include "ast/statement.h"
#include "ast/variableDeclaration.h"
#include "ast/localVariableDeclarationStatement.h"
#include "ast/conditionalStatement.h"
#include "ast/nodeList.h"
#include "ast/type.h"
#include "parse/parseTree.h"
#include "semantic/scope.h"
#include "semantic/semantic.h"

namespace AST
{

//////////////////////////////////////////////////////////////////////////////
//
// resolveExprs 
//
//////////////////////////////////////////////////////////////////////////////

Semantic::SemanticErrorType Block::resolveExprs(Semantic::Scope &parentScope)
{
	Semantic::Scope scope(parentScope);
	for (auto &stmt: statements)
	{
		if (Semantic::SemanticErrorType err = stmt->resolveExprs(scope);
			err != Semantic::SemanticErrorType::None)
		{
			return err;
		}
	}
	return Semantic::SemanticErrorType::None;
}

Semantic::SemanticErrorType Statement::resolveExprs(Semantic::Scope &parentScope)
{
	return Semantic::SemanticErrorType::None;
}

Semantic::SemanticErrorType LocalVariableDeclarationStatement::resolveExprs(Semantic::Scope &parentScope)
{
	if (!parentScope.add(declaration))
	{
		return Semantic::SemanticErrorType::ExprResolution;
	}
	return Semantic::SemanticErrorType::None;
}  
  
//////////////////////////////////////////////////////////////////////////////
//
// resolveTypes
//
//////////////////////////////////////////////////////////////////////////////

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

Semantic::SemanticErrorType ExpressionStatement::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	return expression->resolveTypes(semantic, enclosingClass);
}

Semantic::SemanticErrorType Statement::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *source)
{
	return Semantic::SemanticErrorType::None;
}

Semantic::SemanticErrorType LocalVariableDeclarationStatement::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	return declaration->resolveTypes(semantic, enclosingClass);
}

Semantic::SemanticErrorType
ReturnStatement::resolveTypes(Semantic::SemanticDB const &semantic, TypeDeclaration *enclosingClass) {
	return returnValue->resolveTypes(semantic, enclosingClass);
}  
    
//////////////////////////////////////////////////////////////////////////////
//
// create functions
//
//////////////////////////////////////////////////////////////////////////////

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

// static
std::unique_ptr<ExpressionStatement> ExpressionStatement::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
		case Parse::NonTerminalType::ExpressionStatement:
			return std::make_unique<ExpressionStatement>(static_cast<const Parse::TExpressionStatement*>(ptNode));
		default:
			FAILED("inappropriate PT type for ExpressionStatement: " + std::to_string((int)ptNode->type));
	}
}
  
// static
std::unique_ptr<LocalVariableDeclarationStatement> LocalVariableDeclarationStatement::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
		case Parse::NonTerminalType::LocalVariableDeclarationStatement:
			return std::make_unique<LocalVariableDeclarationStatement>(static_cast<const Parse::TLocalVariableDeclarationStatement*>(ptNode));
		default:
			FAILED("inappropriate PT type for LocalVariableDeclarationStatement: " + std::to_string((int)ptNode->type));
	}
}

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
			FAILED("inappropriate PT type for ReturnStatement: " + std::to_string((int)ptNode->type));
	}
}

//////////////////////////////////////////////////////////////////////////////
//
// toCode
//
//////////////////////////////////////////////////////////////////////////////

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

std::string ExpressionStatement::toCode() const {
	return expression ? expression->toCode() + ";" : ";";
}

std::string LocalVariableDeclarationStatement::toCode() const
{
	return declaration->toCode() + ";";
}

std::string ReturnStatement::toCode() const
{
	return "return " + (returnValue ? returnValue->toCode() : "") + ";";
}

//////////////////////////////////////////////////////////////////////////////
//
// Constructors
//
//////////////////////////////////////////////////////////////////////////////
  
Block::Block(const Parse::TBlock *ptNode)
	: statements(std::move(NodeList<Statement>(ptNode->blockStatements).list))
{
}

ExpressionStatement::ExpressionStatement(const Parse::TExpressionStatement *ptNode)
	: expression(Expression::create(ptNode->statementExpression))
{
}

LocalVariableDeclarationStatement::LocalVariableDeclarationStatement(const Parse::TLocalVariableDeclarationStatement *ptNode)
	: declaration(std::make_unique<VariableDeclaration>(ptNode->variableDeclaration))
{
}

ReturnStatement::ReturnStatement(const Parse::TReturnStatement *ptNode):
	returnValue(Expression::create(ptNode->expression))
{
}

} //namespace AST
