#include "ast/node.h"
#include "ast/allASTHeaders.h"
#include "ast/allPseudoASTHeaders.h"
#include "ast/nodeList.h"
#include "parse/parseTree.h"

namespace AST
{

// static
[[gnu::pure]]
bool Node::isSingleton(const Parse::Tree *ptNode)
{
	switch (ptNode->type) {
		case Parse::NonTerminalType::ParenthesizedExpression:
			return true;
		case Parse::NonTerminalType::Name:
		case Parse::NonTerminalType::CompilationUnit:
		case Parse::NonTerminalType::VariableDeclarator:
			return false;
		default:
			return ptNode->oneNt && !isListType(ptNode);
	}
}

std::unique_ptr<Node> Node::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (isSingleton(ptNode))
	{
		return Node::create(ptNode->children[0]);
	}

	switch (ptNode->type)
	{
		case Parse::NonTerminalType::Literal:
			return Literal                          	::create(static_cast<const Parse::TLiteral*>(ptNode));
		case Parse::NonTerminalType::PrimitiveType:
			return PrimitiveType                    	::create(static_cast<const Parse::TPrimitiveType*>(ptNode));
		case Parse::NonTerminalType::ArrayType:
			return Type                             	::create(static_cast<const Parse::TArrayType*>(ptNode));
		case Parse::NonTerminalType::Name:
			return Name                             	::create(static_cast<const Parse::TName*>(ptNode));
		case Parse::NonTerminalType::CompilationUnit:
			return CompilationUnit                  	::create(static_cast<const Parse::TCompilationUnit*>(ptNode));
		case Parse::NonTerminalType::ImportDeclarations:
			return NodeList<ImportDeclaration>      	::create(static_cast<const Parse::TImportDeclarations*>(ptNode));
		case Parse::NonTerminalType::PackageDeclaration:
			return PackageDeclaration               	::create(static_cast<const Parse::TPackageDeclaration*>(ptNode));
		case Parse::NonTerminalType::SingleTypeImportDeclaration:
			return ImportDeclaration                	::create(static_cast<const Parse::TSingleTypeImportDeclaration*>(ptNode));
		case Parse::NonTerminalType::TypeImportOnDemandDeclaration:
			return ImportDeclaration                	::create(static_cast<const Parse::TTypeImportOnDemandDeclaration*>(ptNode));
		case Parse::NonTerminalType::TypeDeclaration:
			return TypeDeclaration                  	::create(static_cast<const Parse::TTypeDeclaration*>(ptNode));
		case Parse::NonTerminalType::Modifiers:
			return NodeList<Modifier>               	::create(static_cast<const Parse::TModifiers*>(ptNode));
		case Parse::NonTerminalType::Modifier:
			return Modifier                         	::create(static_cast<const Parse::TModifier*>(ptNode));
		case Parse::NonTerminalType::ClassDeclaration:
			return TypeDeclaration                  	::create(static_cast<const Parse::TClassDeclaration*>(ptNode));
		case Parse::NonTerminalType::InterfaceTypeList:
			return NodeList<NameType>               	::create(static_cast<const Parse::TInterfaceTypeList*>(ptNode));
		case Parse::NonTerminalType::ClassBody:
			return TypeBody                         	::create(static_cast<const Parse::TClassBody*>(ptNode));
		case Parse::NonTerminalType::ClassMemberDeclarations:
			return NodeList<MemberDeclaration>      	::create(static_cast<const Parse::TClassMemberDeclarations*>(ptNode));
		case Parse::NonTerminalType::FieldDeclaration:
			return FieldDeclaration                 	::create(static_cast<const Parse::TFieldDeclaration*>(ptNode));
		case Parse::NonTerminalType::VariableDeclarator:
			return VariableDeclarator               	::create(static_cast<const Parse::TVariableDeclarator*>(ptNode));
		case Parse::NonTerminalType::MethodDeclaration:
			return MethodDeclaration                	::create(static_cast<const Parse::TMethodDeclaration*>(ptNode));
		case Parse::NonTerminalType::MethodHeader:
			return MethodHeader                     	::create(static_cast<const Parse::TMethodHeader*>(ptNode));
		case Parse::NonTerminalType::MethodDeclarator:
			return MethodDeclarator                 	::create(static_cast<const Parse::TMethodDeclarator*>(ptNode));
		case Parse::NonTerminalType::FormalParameterList:
			return NodeList<VariableDeclaration>    	::create(static_cast<const Parse::TFormalParameterList*>(ptNode));
		case Parse::NonTerminalType::FormalParameter:
			return VariableDeclaration              	::create(static_cast<const Parse::TFormalParameter*>(ptNode));
		case Parse::NonTerminalType::AbstractMethodBody:
			return AbstractMethodBody               	::create(static_cast<const Parse::TAbstractMethodBody*>(ptNode));
		case Parse::NonTerminalType::ConstructorDeclaration:
			return ConstructorDeclaration           	::create(static_cast<const Parse::TConstructorDeclaration*>(ptNode));
		case Parse::NonTerminalType::ConstructorDeclarator:
			return MethodDeclarator                 	::create(static_cast<const Parse::TConstructorDeclarator*>(ptNode));
		case Parse::NonTerminalType::InterfaceDeclaration:
			return TypeDeclaration                  	::create(static_cast<const Parse::TInterfaceDeclaration*>(ptNode));
		case Parse::NonTerminalType::ExtendsInterfaces:
			return NodeList<NameType>               	::create(static_cast<const Parse::TExtendsInterfaces*>(ptNode));
		case Parse::NonTerminalType::InterfaceBody:
			return TypeBody                         	::create(static_cast<const Parse::TInterfaceBody*>(ptNode));
		case Parse::NonTerminalType::InterfaceMemberDeclarations:
			return NodeList<MemberDeclaration>      	::create(static_cast<const Parse::TInterfaceMemberDeclarations*>(ptNode));
		case Parse::NonTerminalType::AbstractMethodDeclaration:
			return MethodDeclaration                	::create(static_cast<const Parse::TAbstractMethodDeclaration*>(ptNode));
		case Parse::NonTerminalType::Block:
			return Block                            	::create(static_cast<const Parse::TBlock*>(ptNode));
		case Parse::NonTerminalType::BlockStatements:
			return NodeList<Statement>              	::create(static_cast<const Parse::TBlockStatements*>(ptNode));
		case Parse::NonTerminalType::LocalVariableDeclarationStatement:
			return LocalVariableDeclarationStatement	::create(static_cast<const Parse::TLocalVariableDeclarationStatement*>(ptNode));
		case Parse::NonTerminalType::VariableDeclaration:
			return VariableDeclaration              	::create(static_cast<const Parse::TVariableDeclaration*>(ptNode));
		case Parse::NonTerminalType::ExpressionStatement:
			return ExpressionStatement              	::create(static_cast<const Parse::TExpressionStatement*>(ptNode));
		case Parse::NonTerminalType::IfThenStatement:
			return ConditionalStatement             	::create(static_cast<const Parse::TIfThenStatement*>(ptNode));
		case Parse::NonTerminalType::IfThenElseStatement:
			return IfThenElseStatement              	::create(static_cast<const Parse::TIfThenElseStatement*>(ptNode));
		case Parse::NonTerminalType::IfThenElseStatementNoShortIf:
			return IfThenElseStatement              	::create(static_cast<const Parse::TIfThenElseStatementNoShortIf*>(ptNode));
		case Parse::NonTerminalType::WhileStatement:
			return ConditionalStatement             	::create(static_cast<const Parse::TWhileStatement*>(ptNode));
		case Parse::NonTerminalType::WhileStatementNoShortIf:
			return ConditionalStatement             	::create(static_cast<const Parse::TWhileStatementNoShortIf*>(ptNode));
		case Parse::NonTerminalType::ForStatement:
			return ForStatement                     	::create(static_cast<const Parse::TForStatement*>(ptNode));
		case Parse::NonTerminalType::ForStatementNoShortIf:
			return ForStatement                     	::create(static_cast<const Parse::TForStatementNoShortIf*>(ptNode));
		case Parse::NonTerminalType::ReturnStatement:
			return ReturnStatement                  	::create(static_cast<const Parse::TReturnStatement*>(ptNode));
		case Parse::NonTerminalType::This2:
			return This                             	::create(static_cast<const Parse::TThis2*>(ptNode));
		case Parse::NonTerminalType::ClassInstanceCreationExpression:
			return ClassInstanceCreationExpression  	::create(static_cast<const Parse::TClassInstanceCreationExpression*>(ptNode));
		case Parse::NonTerminalType::ArgumentList:
			return NodeList<Expression>             	::create(static_cast<const Parse::TArgumentList*>(ptNode));
		case Parse::NonTerminalType::ArrayCreationExpression:
			return ArrayCreationExpression          	::create(static_cast<const Parse::TArrayCreationExpression*>(ptNode));
		case Parse::NonTerminalType::FieldAccess:
			return FieldAccess                      	::create(static_cast<const Parse::TFieldAccess*>(ptNode));
		case Parse::NonTerminalType::MethodInvocation:
			return MethodInvocation                 	::create(static_cast<const Parse::TMethodInvocation*>(ptNode));
		case Parse::NonTerminalType::ArrayAccess:
			return ArrayAccess                      	::create(static_cast<const Parse::TArrayAccess*>(ptNode));
		case Parse::NonTerminalType::UnaryExpression:
			return UnaryExpression                  	::create(static_cast<const Parse::TUnaryExpression*>(ptNode));
		case Parse::NonTerminalType::UnaryExpressionNotPlusMinus:
			return UnaryExpression                  	::create(static_cast<const Parse::TUnaryExpressionNotPlusMinus*>(ptNode));
		case Parse::NonTerminalType::CastExpression:
			return CastExpression                   	::create(static_cast<const Parse::TCastExpression*>(ptNode));
		case Parse::NonTerminalType::MultiplicativeExpression:
			return BinaryExpression                 	::create(static_cast<const Parse::TMultiplicativeExpression*>(ptNode));
		case Parse::NonTerminalType::AdditiveExpression:
			return BinaryExpression                 	::create(static_cast<const Parse::TAdditiveExpression*>(ptNode));
		case Parse::NonTerminalType::RelationalExpression:
			return BinaryExpression                 	::create(static_cast<const Parse::TRelationalExpression*>(ptNode));
		case Parse::NonTerminalType::EqualityExpression:
			return BinaryExpression                 	::create(static_cast<const Parse::TEqualityExpression*>(ptNode));
		case Parse::NonTerminalType::AndExpression:
			return BinaryExpression                 	::create(static_cast<const Parse::TAndExpression*>(ptNode));
		case Parse::NonTerminalType::InclusiveOrExpression:
			return BinaryExpression                 	::create(static_cast<const Parse::TInclusiveOrExpression*>(ptNode));
		case Parse::NonTerminalType::ConditionalAndExpression:
			return BinaryExpression                 	::create(static_cast<const Parse::TConditionalAndExpression*>(ptNode));
		case Parse::NonTerminalType::ConditionalOrExpression:
			return BinaryExpression                 	::create(static_cast<const Parse::TConditionalOrExpression*>(ptNode));
		case Parse::NonTerminalType::Assignment:
			return AssignmentExpression             	::create(static_cast<const Parse::TAssignment*>(ptNode));
		default:
			return nullptr;
	}
}

}
