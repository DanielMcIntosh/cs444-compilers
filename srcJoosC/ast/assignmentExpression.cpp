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
	if (ptNode->oneNt)
	{
		return AssignmentExpression::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::Assignment:
		return std::make_unique<AssignmentExpression>(static_cast<const Parse::TAssignment*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for AssignmentExpression: " + std::to_string((int)ptNode->type));
	}
}
AssignmentExpression::AssignmentExpression(const Parse::TAssignment *ptNode)
{
}

} //namespace AST
