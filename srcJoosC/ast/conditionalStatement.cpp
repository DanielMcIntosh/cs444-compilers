#include "ast/conditionalStatement.h"
#include "ast/statement.h"
#include "ast/expression.h"
#include "ast/type.h"
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
	Semantic::Scope mainScope(parentScope);
	Semantic::SemanticErrorType err;
	if (init)
	{
		err = init->resolveExprs(mainScope);
		GOFAIL_IF_ERR(err);
	}
	if (condition)
	{
		err = condition->resolveAndDeduce(mainScope);
		GOFAIL_IF_ERR(err);
	}
	if (increment)
	{
		err = increment->resolveAndDeduce(mainScope);
		GOFAIL_IF_ERR(err);
	}
	err = body->resolveExprs(mainScope);
	GOFAIL_IF_ERR(err);
	if (elseBody)
	{
		Semantic::Scope elseScope(parentScope);
		err = elseBody->resolveExprs(elseScope);
		GOFAIL_IF_ERR(err);
	}
	OK();

	fail:
	return err;
}

//////////////////////////////////////////////////////////////////////////////
//
// resolveTypes
//
//////////////////////////////////////////////////////////////////////////////

Semantic::SemanticErrorType ConditionalStatement::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	if (init)
	{
		if (Semantic::SemanticErrorType err = init->resolveTypes(semantic, enclosingClass);
			err != Semantic::SemanticErrorType::None)
		{
			return err;
		}
	}
	if (condition)
	{
		if (Semantic::SemanticErrorType err = condition->resolveTypes(semantic, enclosingClass);
				err != Semantic::SemanticErrorType::None)
		{
			return err;
		}
	}
	if (increment)
	{
		if (Semantic::SemanticErrorType err = increment->resolveTypes(semantic, enclosingClass);
				err != Semantic::SemanticErrorType::None)
		{
			return err;
		}
	}
	if (Semantic::SemanticErrorType err = body->resolveTypes(semantic, enclosingClass);
		err != Semantic::SemanticErrorType::None)
	{
		return err;
	}
	if (elseBody)
	{
		if (Semantic::SemanticErrorType err = elseBody->resolveTypes(semantic, enclosingClass);
			err != Semantic::SemanticErrorType::None)
		{
			return err;
		}
	}
	return Semantic::SemanticErrorType::None;
}

//////////////////////////////////////////////////////////////////////////////
//
// create functions
//
//////////////////////////////////////////////////////////////////////////////

// static
std::unique_ptr<ConditionalStatement> ConditionalStatement::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::IfThenStatement:
		return std::make_unique<ConditionalStatement>(static_cast<const Parse::TIfThenStatement*>(ptNode));
	case Parse::NonTerminalType::IfThenElseStatement:
		return std::make_unique<ConditionalStatement>(static_cast<const Parse::TIfThenElseStatement*>(ptNode));
	case Parse::NonTerminalType::IfThenElseStatementNoShortIf:
		return std::make_unique<ConditionalStatement>(static_cast<const Parse::TIfThenElseStatementNoShortIf*>(ptNode));
	case Parse::NonTerminalType::WhileStatement:
		return std::make_unique<ConditionalStatement>(static_cast<const Parse::TWhileStatement*>(ptNode));
	case Parse::NonTerminalType::WhileStatementNoShortIf:
		return std::make_unique<ConditionalStatement>(static_cast<const Parse::TWhileStatementNoShortIf*>(ptNode));
	case Parse::NonTerminalType::ForStatement:
		return std::make_unique<ConditionalStatement>(static_cast<const Parse::TForStatement*>(ptNode));
	case Parse::NonTerminalType::ForStatementNoShortIf:
		return std::make_unique<ConditionalStatement>(static_cast<const Parse::TForStatementNoShortIf*>(ptNode));
	default:
		FAILED("inappropriate PT type for ConditionalStatement: " + std::to_string((int)ptNode->type));
	}
}

//////////////////////////////////////////////////////////////////////////////
//
// Constructors
//
//////////////////////////////////////////////////////////////////////////////

ConditionalStatement::ConditionalStatement(const Parse::TIfThenStatement *ptNode)
  :	condType(ConditionType::If),
	init(nullptr),
	condition(Expression::create(ptNode->expression)),
	increment(nullptr),
	body(Statement::create(ptNode->statement)),
	elseBody(nullptr)
{
	nodeType = NodeType::ConditionalStatement;
}
ConditionalStatement::ConditionalStatement(const Parse::TIfThenElseStatement *ptNode)
  :	condType(ConditionType::If),
	init(nullptr),
	condition(Expression::create(ptNode->expression)),
	increment(nullptr),
	body(Statement::create(ptNode->statementNoShortIf)),
	elseBody(Statement::create(ptNode->statement))
{
	nodeType = NodeType::ConditionalStatement;
}
ConditionalStatement::ConditionalStatement(const Parse::TIfThenElseStatementNoShortIf *ptNode)
  :	condType(ConditionType::If),
	init(nullptr),
	condition(Expression::create(ptNode->expression)),
	increment(nullptr),
	body(Statement::create(ptNode->statementNoShortIf)),
	elseBody(Statement::create(ptNode->statementNoShortIf2))
{
	nodeType = NodeType::ConditionalStatement;
}

ConditionalStatement::ConditionalStatement(const Parse::TWhileStatement *ptNode)
  :	condType(ConditionType::While),
	init(nullptr),
	condition(Expression::create(ptNode->expression)),
	increment(nullptr),
	body(Statement::create(ptNode->statement)),
	elseBody(nullptr)
{
	nodeType = NodeType::ConditionalStatement;
}
ConditionalStatement::ConditionalStatement(const Parse::TWhileStatementNoShortIf *ptNode)
  :	condType(ConditionType::While),
	init(nullptr),
	condition(Expression::create(ptNode->expression)),
	increment(nullptr),
	body(Statement::create(ptNode->statementNoShortIf)),
	elseBody(nullptr)
{
	nodeType = NodeType::ConditionalStatement;
}

ConditionalStatement::ConditionalStatement(const Parse::TForStatement *ptNode)
  :	condType(ConditionType::For),
	init(Statement::create(ptNode->forInit)),
	condition(Expression::create(ptNode->expression)),
	increment(Expression::create(ptNode->forUpdate)),
	body(Statement::create(ptNode->statement)),
	elseBody(nullptr)
{
	nodeType = NodeType::ConditionalStatement;
}
ConditionalStatement::ConditionalStatement(const Parse::TForStatementNoShortIf *ptNode)
  :	condType(ConditionType::For),
	init(Statement::create(ptNode->forInit)),
	condition(Expression::create(ptNode->expression)),
	increment(Expression::create(ptNode->forUpdate)),
	body(Statement::create(ptNode->statementNoShortIf)),
	elseBody(nullptr)
{
	nodeType = NodeType::ConditionalStatement;
}

//////////////////////////////////////////////////////////////////////////////
//
// toCode
//
//////////////////////////////////////////////////////////////////////////////

std::string ConditionalStatement::toCode() const
{
	if (condType == ConditionType::For) {
		assert(!elseBody);
		return "for (" + (init ? init->toCode() : "") + " "
		       + (condition ? condition->toCode() : "") + "; "
		       + (increment ? increment->toCode() : "") + ")\n"
		       + body->toCode();
	} else {
		assert(!init && !increment);
		std::string str = "" + condType + " (" + condition->toCode() + ")\n";
		str += body->toCode();
		if (elseBody)
		{
			str += "\nelse\n";
			str += elseBody->toCode();
		}
		return str;
	}
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
