#pragma once

#include <ast/statement.h>
//#include <ast/localVariableDeclaration.h>
#include <memory>

namespace AST
{

class LocalVariableDeclarationStatement: public Statement
{
public:
	LocalVariableDeclarationStatement(std::vector<Parser::ASTToken>& children);

	//std::shared_ptr<LocalVariableDeclaration> declaration;
};

} //namespace AST
