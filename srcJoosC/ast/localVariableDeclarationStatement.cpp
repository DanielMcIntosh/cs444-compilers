#include "ast/localVariableDeclarationStatement.h"
#include "ast/statement.h"
#include "parse/parseTree.h"
#include "semantic/scope.h"
#include "semantic/semantic.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<LocalVariableDeclarationStatement> LocalVariableDeclarationStatement::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::LocalVariableDeclarationStatement:
		return std::make_unique<LocalVariableDeclarationStatement>(static_cast<const Parse::TLocalVariableDeclarationStatement*>(ptNode));
	default:
		FAILED("inappropriate PT type for LocalVariableDeclarationStatement: " + std::to_string((int)ptNode->type));
	}
}
LocalVariableDeclarationStatement::LocalVariableDeclarationStatement(const Parse::TLocalVariableDeclarationStatement *ptNode)
  : declaration(std::make_unique<VariableDeclaration>(ptNode->variableDeclaration))
{
}

std::string LocalVariableDeclarationStatement::toCode() const
{
	return declaration->toCode() + ";";
}

Semantic::SemanticErrorType LocalVariableDeclarationStatement::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	return declaration->resolveTypes(semantic, enclosingClass);
}

Semantic::SemanticErrorType LocalVariableDeclarationStatement::resolveExprs(Semantic::Scope &parentScope)
{
	if (!parentScope.add(declaration))
	{
		return Semantic::SemanticErrorType::ExprResolution;
	}
	return Semantic::SemanticErrorType::None;
}

} //namespace AST
