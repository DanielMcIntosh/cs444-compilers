#pragma once

#include <memory>
#include <vector>
#include "parse/parseTreeBase.h"

namespace AST
{

enum class NodeType {
	Undefined,
	CompilationUnit,
	ImportDeclaration,
	MemberDeclaration,
	Modifier,
	TypeDeclaration,
	VariableDeclaration,
	MethodDeclarator,
	MethodHeader,
	TypeBody,
	VariableDeclarator,
	Name,

	PrimitiveType,
	NameType,

	ConstructorDeclaration,
	FieldDeclaration,
	MethodDeclaration,

	Block,
	ExpressionStatement,
	LocalVariableDeclarationStatement,
	ReturnStatement,
	ConditionalStatement,

	AssignmentExpression,
	BinaryExpression,
	CastExpression,
	UnaryExpression,
	ArrayAccess,
	ArrayCreationExpression,
	ClassInstanceCreationExpression,
	FieldAccess,
	Literal,
	MethodInvocation,
	LocalVariableExpression,
	NameExpression,
};
  
class Node
{
public:
	static std::unique_ptr<Node> create(const Parse::Tree *ptNode);
	Node();
	virtual ~Node() = default;

	[[gnu::pure]]
	static bool isSingleton(const Parse::Tree *ptNode);

	virtual std::string toCode() const = 0;

	NodeType nodeType;
};

}
