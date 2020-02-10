#include "ast/classInstanceCreationExpression.h"
#include "ast/type.h"
#include "ast/expression.h"
#include "ast/nodeList.h"
#include "parse/parseTree.h"
#include <vector>
#include <memory>

namespace AST
{

// static
std::unique_ptr<ClassInstanceCreationExpression> ClassInstanceCreationExpression::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (ptNode->oneNt)
	{
		return ClassInstanceCreationExpression::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::ClassInstanceCreationExpression:
		return std::make_unique<ClassInstanceCreationExpression>(static_cast<const Parse::TClassInstanceCreationExpression*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for ClassInstanceCreationExpression: " + std::to_string((int)ptNode->type));
	}
}
ClassInstanceCreationExpression::ClassInstanceCreationExpression(const Parse::TClassInstanceCreationExpression *ptNode)
{
	/*
	int cur = 0;
	++cur; // new
	type = std::dynamic_pointer_cast<Type>(children[cur++].astNode);
	auto argList = std::dynamic_pointer_cast<ArgumentList>(children[cur++].astNode);
	args = argList->list;
	*/
}

} //namespace AST
