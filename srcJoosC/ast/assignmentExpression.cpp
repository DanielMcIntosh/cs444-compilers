#include "ast/assignmentExpression.h"
#include "ast/expression.h"
#include "parse/parseTree.h"

#include <memory>

namespace AST
{

// static
std::unique_ptr<AssignmentExpression> AssignmentExpression::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::Assignment:
		return std::make_unique<AssignmentExpression>(static_cast<const Parse::TAssignment*>(ptNode));
	default:
		FAILED("inappropriate PT type for AssignmentExpression: " + std::to_string((int)ptNode->type));
	}
}
AssignmentExpression::AssignmentExpression(const Parse::TAssignment *ptNode)
  : lhs(Expression::create(ptNode->leftHandSide)),
	rhs(Expression::create(ptNode->assignmentExpression))
{
}

std::string AssignmentExpression::toCode() const
{
	return "(" + lhs->toCode() + "=" + rhs->toCode() + ")";
}

} //namespace AST
