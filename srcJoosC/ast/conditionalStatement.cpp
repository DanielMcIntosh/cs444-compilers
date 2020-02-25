#include "ast/conditionalStatement.h"
#include "ast/statement.h"
#include "ast/expression.h"
#include "parse/parseTree.h"
#include "semantic/semantic.h"
#include "semantic/scope.h"
#include <memory>
#include <ostream>

namespace AST
{

//////////////////////////////////////////////////////////////////////////////
//
// resolveExprs
//
//////////////////////////////////////////////////////////////////////////////

Semantic::SemanticErrorType ConditionalStatement::resolveExprs(Semantic::Scope &parentScope)
{
	// TODO: resolve condition
	// TODO: override in "ForStatement"
	return body->resolveExprs(parentScope);
}

Semantic::SemanticErrorType IfThenElseStatement::resolveExprs(Semantic::Scope &parentScope)
{
	if (Semantic::SemanticErrorType err = ConditionalStatement::resolveExprs(parentScope);
		err != Semantic::SemanticErrorType::None)
	{
		return err;
	}
	Semantic::Scope elseScope(parentScope);
	return elseBody->resolveExprs(elseScope);
}

Semantic::SemanticErrorType ForStatement::resolveExprs(Semantic::Scope &parentScope)
{
	Semantic::Scope scope(parentScope);
	if (init)
	{
		if (Semantic::SemanticErrorType err = init->resolveExprs(scope);
			err != Semantic::SemanticErrorType::None)
		{
			return err;
		}
	}
	return ConditionalStatement::resolveExprs(scope);
}

//////////////////////////////////////////////////////////////////////////////
//
// resolveTypes
//
//////////////////////////////////////////////////////////////////////////////

Semantic::SemanticErrorType ConditionalStatement::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	if (body)
	{
		if (Semantic::SemanticErrorType err = body->resolveTypes(semantic, enclosingClass);
			err != Semantic::SemanticErrorType::None)
		{
			return err;
		}
	}
	return Semantic::SemanticErrorType::None;
}

Semantic::SemanticErrorType ForStatement::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	if (init)
	{
		if (Semantic::SemanticErrorType err = init->resolveTypes(semantic, enclosingClass);
			err != Semantic::SemanticErrorType::None)
		{
			return err;
		}
	}
	return ConditionalStatement::resolveTypes(semantic, enclosingClass);
}
  
Semantic::SemanticErrorType IfThenElseStatement::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	if (Semantic::SemanticErrorType err = ConditionalStatement::resolveTypes(semantic, enclosingClass);
		err != Semantic::SemanticErrorType::None)
	{
		return err;
	}
	return elseBody->resolveTypes(semantic, enclosingClass);
}    
  
//////////////////////////////////////////////////////////////////////////////
//
// create functions
//
//////////////////////////////////////////////////////////////////////////////
  
// static
std::unique_ptr<IfThenElseStatement> IfThenElseStatement::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
		case Parse::NonTerminalType::IfThenElseStatement:
			return std::make_unique<IfThenElseStatement>(static_cast<const Parse::TIfThenElseStatement*>(ptNode));
		case Parse::NonTerminalType::IfThenElseStatementNoShortIf:
			return std::make_unique<IfThenElseStatement>(static_cast<const Parse::TIfThenElseStatementNoShortIf*>(ptNode));
		default:
			FAILED("inappropriate PT type for IfThenElseStatement: " + std::to_string((int)ptNode->type));
	}
}

// static
std::unique_ptr<ConditionalStatement> ConditionalStatement::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::IfThenStatement:
		return std::make_unique<ConditionalStatement>(static_cast<const Parse::TIfThenStatement*>(ptNode));
	case Parse::NonTerminalType::WhileStatement:
		return std::make_unique<ConditionalStatement>(static_cast<const Parse::TWhileStatement*>(ptNode));
	case Parse::NonTerminalType::WhileStatementNoShortIf:
		return std::make_unique<ConditionalStatement>(static_cast<const Parse::TWhileStatementNoShortIf*>(ptNode));
	default:
		FAILED("inappropriate PT type for ConditionalStatement: " + std::to_string((int)ptNode->type));
	}
}

// static
std::unique_ptr<ForStatement> ForStatement::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
		case Parse::NonTerminalType::ForStatement:
			return std::make_unique<ForStatement>(static_cast<const Parse::TForStatement*>(ptNode));
		case Parse::NonTerminalType::ForStatementNoShortIf:
			return std::make_unique<ForStatement>(static_cast<const Parse::TForStatementNoShortIf*>(ptNode));
		default:
			FAILED("inappropriate PT type for ForStatement: " + std::to_string((int)ptNode->type));
	}
}

//////////////////////////////////////////////////////////////////////////////
//
// Constructors
//
//////////////////////////////////////////////////////////////////////////////  
  
IfThenElseStatement::IfThenElseStatement(const Parse::TIfThenElseStatement *ptNode)
	: ConditionalStatement(ConditionalStatement::ConditionType::If, Expression::create(ptNode->expression), Statement::create(ptNode->statementNoShortIf)),
	  elseBody(Statement::create(ptNode->statement))
{
}
IfThenElseStatement::IfThenElseStatement(const Parse::TIfThenElseStatementNoShortIf *ptNode)
	: ConditionalStatement(ConditionalStatement::ConditionType::If, Expression::create(ptNode->expression), Statement::create(ptNode->statementNoShortIf)),
	  elseBody(Statement::create(ptNode->statementNoShortIf2))
{
}


ConditionalStatement::ConditionalStatement(const Parse::TIfThenStatement *ptNode)
  : condType(ConditionalStatement::ConditionType::If),
    condition(Expression::create(ptNode->expression)),
    body(Statement::create(ptNode->statement))
{
}
ConditionalStatement::ConditionalStatement(const Parse::TWhileStatement *ptNode)
  : condType(ConditionalStatement::ConditionType::While),
  condition(Expression::create(ptNode->expression)),
  body(Statement::create(ptNode->statement))
{
}
ConditionalStatement::ConditionalStatement(const Parse::TWhileStatementNoShortIf *ptNode)
  : condType(ConditionalStatement::ConditionType::While),
    condition(Expression::create(ptNode->expression)),
    body(Statement::create(ptNode->statementNoShortIf))
{
}

// protected
ConditionalStatement::ConditionalStatement(ConditionType type, std::unique_ptr<Expression> cond, std::unique_ptr<Statement> statement)
  : condType(type),
	condition(std::move(cond)),
	body(std::move(statement))
{
}

ForStatement::ForStatement(const Parse::TForStatement *ptNode)
	: ConditionalStatement(ConditionalStatement::ConditionType::For, Expression::create(ptNode->expression), Statement::create(ptNode->statement)),
	  init(Statement::create(ptNode->forInit)),
	  increment(Expression::create(ptNode->forUpdate))
{
}
ForStatement::ForStatement(const Parse::TForStatementNoShortIf *ptNode)
	: ConditionalStatement(ConditionalStatement::ConditionType::For, Expression::create(ptNode->expression), Statement::create(ptNode->statementNoShortIf)),
	  init(Statement::create(ptNode->forInit)),
	  increment(Expression::create(ptNode->forUpdate))
{
}  

//////////////////////////////////////////////////////////////////////////////
//
// toCode
//
//////////////////////////////////////////////////////////////////////////////

std::string ConditionalStatement::toCode() const
{
	std::string str = "" + condType + "(" + condition->toCode() + ")\n";
	str += body->toCode();
	return str;
}

std::string ForStatement::toCode() const {
	return "for (" + (init ? init->toCode() : "") + " "
	       + (condition ? condition->toCode() : "") + "; "
	       + (increment ? increment->toCode() : "") + ")\n"
	       + body->toCode();
}

std::string IfThenElseStatement::toCode() const
{
	std::string str = "if (" + condition->toCode() + ")\n";
	str += body->toCode();
	str += "\nelse\n";
	str += elseBody->toCode();
	return str;
}

//////////////////////////////////////////////////////////////////////////////
//
// Others
//
//////////////////////////////////////////////////////////////////////////////

std::string operator+=(std::string& str, ConditionalStatement::ConditionType type)
{
    switch(type)
    {
		case ConditionalStatement::ConditionType::If:   	return str += "if";
		case ConditionalStatement::ConditionType::While:	return str += "while";
		case ConditionalStatement::ConditionType::For:  	return str += "for";
		case ConditionalStatement::ConditionType::Max:		;// fallthrough
		// no default to trigger compiler warning on missing case
    }
    FAILED("String conversion on invalid condition type: " + std::to_string((int)type));
}
std::string operator+(std::string str, ConditionalStatement::ConditionType type)
{
	return str += type;
}

std::ostream& operator<<(std::ostream& os, ConditionalStatement::ConditionType type)
{
	if (type >= ConditionalStatement::ConditionType::Max) {
		os.setstate(std::ios_base::failbit);
		return os;
	}
	return os << ("" + type);
}

} //namespace AST
