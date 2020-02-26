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

	TYPE_BEGIN,
	PrimitiveType = TYPE_BEGIN,
	NameType,
	TYPE_END,

	MEMBER_DECLARATION_BEGIN = TYPE_END,
	ConstructorDeclaration = MEMBER_DECLARATION_BEGIN,
	FieldDeclaration,
	MethodDeclaration,
	MEMBER_DECLARATION_END,

	STATEMENT_BEGIN = MEMBER_DECLARATION_END,
	Block = STATEMENT_BEGIN,
	ExpressionStatement,
	LocalVariableDeclarationStatement,
	ReturnStatement,
	ConditionalStatement,
	STATEMENT_END,

	EXPRESSION_BEGIN = STATEMENT_END,
	AssignmentExpression = EXPRESSION_BEGIN,
	BinaryExpression,
	CastExpression,
	Name,
	UnaryExpression,
	ArrayAccess,
	ArrayCreationExpression,
	ClassInstanceCreationExpression,
	FieldAccess,
	Literal,
	MethodInvocation,
	LocalVariableExpression,
	NameExpression,
	EXPRESSION_END,

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
