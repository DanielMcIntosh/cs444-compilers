#pragma once
/**
 * Declaration of either a Class or Interface type
 */
#include "ast/node.h"
#include "ast/type.h"
#include "ast/modifier.h"
#include "ast/memberDeclaration.h"
#include <memory>
#include <vector>
#include <string>

namespace AST
{

// might not be sub-classed (i.e. can have empty 'type declarations' which are just a semicolon)
class TypeDeclaration: public Node
{
public:
	TypeDeclaration(std::vector<Parser::ASTToken>& children);

	bool isInterface;
	std::vector<std::shared_ptr<Modifier>> modifiers;
	std::string name;
	// null for interfaces
	std::shared_ptr<Type> superClass;
	// implements if we're a class, extends if we're an interface
	std::vector<std::shared_ptr<Type>> interfaces;
	std::vector<std::shared_ptr<MemberDeclaration>> members;
};

} //namespace AST
