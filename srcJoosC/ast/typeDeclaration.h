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
	static std::unique_ptr<TypeDeclaration> create(const Parse::Tree *ptNode);
	TypeDeclaration(const Parse::TTypeDeclaration *ptNode);
	TypeDeclaration(const Parse::TClassDeclaration *ptNode);
	TypeDeclaration(const Parse::TInterfaceDeclaration *ptNode);

	bool isInterface;
	std::vector<std::unique_ptr<Modifier>> modifiers;
	std::string name;
	// null for interfaces
	// TODO: these should be NameType
	std::unique_ptr<Type> superClass;
	// implements if we're a class, extends if we're an interface
	std::vector<std::unique_ptr<Type>> interfaces;
	std::vector<std::unique_ptr<MemberDeclaration>> members;

	std::string toCode() override;

	// Fully qualified name (with package string)
	std::string fqn;

	std::vector<TypeDeclaration *> children;
};

} //namespace AST
