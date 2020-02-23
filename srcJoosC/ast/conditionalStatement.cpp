#include "ast/conditionalStatement.h"
#include "ast/statement.h"
#include "ast/expression.h"
#include "parse/parseTree.h"
#include "semantic/semantic.h"
#include <memory>
#include <ostream>

namespace AST
{

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

std::string ConditionalStatement::toCode() const
{
	std::string str = "" + condType + "(" + condition->toCode() + ")\n";
	str += body->toCode();
	return str;
}

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
