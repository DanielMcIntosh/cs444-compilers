#include "ast/expression.h"
#include "ast/assignmentExpression.h"
#include "ast/binaryExpression.h"
#include "ast/castExpression.h"
#include "ast/name.h"
#include "ast/unaryExpression.h"
#include "ast/arrayAccess.h"
#include "ast/arrayCreationExpression.h"
#include "ast/classInstanceCreationExpression.h"
#include "ast/fieldAccess.h"
#include "ast/literal.h"
#include "ast/methodInvocation.h"
#include "ast/this.h"
#include "parse/parseTreeBase.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<Expression> Expression::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (ptNode->oneNt)
	{
		return Expression::create(ptNode->children[0]);
	}

	switch(ptNode->type) {
		case Parse::NonTerminalType::Assignment:
			return AssignmentExpression::create(ptNode);
		case Parse::NonTerminalType::AdditiveExpression:
		case Parse::NonTerminalType::AndExpression:
		case Parse::NonTerminalType::ConditionalAndExpression:
		case Parse::NonTerminalType::ConditionalOrExpression:
		case Parse::NonTerminalType::EqualityExpression:
		case Parse::NonTerminalType::InclusiveOrExpression:
		case Parse::NonTerminalType::MultiplicativeExpression:
		case Parse::NonTerminalType::RelationalExpression:
			return BinaryExpression::create(ptNode);
		case Parse::NonTerminalType::CastExpression:
			return CastExpression::create(ptNode);
		case Parse::NonTerminalType::Name:
			return std::make_unique<NameExpression>(std::move(*Name::create(ptNode)));
		case Parse::NonTerminalType::UnaryExpression:
		case Parse::NonTerminalType::UnaryExpressionNotPlusMinus:
			return UnaryExpression::create(ptNode);
		case Parse::NonTerminalType::ArrayAccess:
			return ArrayAccess::create(ptNode);
		case Parse::NonTerminalType::ArrayCreationExpression:
			return ArrayCreationExpression::create(ptNode);
		case Parse::NonTerminalType::ClassInstanceCreationExpression:
			return ClassInstanceCreationExpression::create(ptNode);
		case Parse::NonTerminalType::FieldAccess:
			return FieldAccess::create(ptNode);
		case Parse::NonTerminalType::Literal:
			return Literal::create(ptNode);
		case Parse::NonTerminalType::MethodInvocation:
			return MethodInvocation::create(ptNode);
		case Parse::NonTerminalType::This2:
			return This::create(ptNode);
		default:
			throw std::runtime_error("inapropriate PT type for Expression: " + std::to_string((int)ptNode->type));
	}
}

} //namespace AST
