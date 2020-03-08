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
// staticAnalysis
//
//////////////////////////////////////////////////////////////////////////////

	void ConditionalStatement::staticAnalysis(StaticAnalysisCtx *ctx) {
		if (!ctx->in) {
			ctx->hasError = true;
		}
		switch (condType) {
		case ConditionType::If: {
			if (!elseBody) {
				bool inL = ctx->in;
				body->staticAnalysis(ctx);
				ctx->out = ctx->out || inL;
			} else {
				auto nCtx1 = *ctx;
				body->staticAnalysis(&nCtx1);
				auto nCtx2 = *ctx;
				elseBody->staticAnalysis(&nCtx2);
				ctx->out = nCtx1.out || nCtx2.out;
				ctx->hasError |= nCtx1.hasError || nCtx2.hasError;
			}
			break;
		}
		case ConditionType::While: {
			auto expr = condition->tryEval();
			if (expr.isTrue()) {
				body->staticAnalysis(ctx);
				ctx->out = false;
				break;
			}

			if (expr.isFalse()) {
				auto nCtx = *ctx;
				nCtx.in = false;
				body->staticAnalysis(&nCtx);
				ctx->out = ctx->in;
				ctx->hasError |= nCtx.hasError;
				break;
			}

			bool inL = ctx->in;
			body->staticAnalysis(ctx);
			ctx->out = inL;
			break;
		}
		case ConditionType::For: {
			if (!condition) {
				body->staticAnalysis(ctx);
				ctx->out = false;
				break;
			}

			auto expr = condition->tryEval();
			if (expr.isFalse()) {
				auto nCtx = *ctx;
				nCtx.in = false;
				body->staticAnalysis(&nCtx);
				ctx->out = ctx->in;
				ctx->hasError |= nCtx.hasError;
				break;
			}

			if (expr.isTrue()) {
				body->staticAnalysis(ctx);
				ctx->out = false;
				break;
			}

			bool inL = ctx->in;
			body->staticAnalysis(ctx);
			ctx->out = inL;
			break;
		}
		default:
			ASSERT(false);
			break;
		}
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
