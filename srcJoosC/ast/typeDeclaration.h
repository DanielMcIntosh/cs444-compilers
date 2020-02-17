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
	explicit TypeDeclaration(const Parse::TTypeDeclaration *ptNode);
	explicit TypeDeclaration(const Parse::TClassDeclaration *ptNode);
	explicit TypeDeclaration(const Parse::TInterfaceDeclaration *ptNode);

	bool isInterface;
	std::vector<std::unique_ptr<Modifier>> modifiers;
	std::string name;
	// TODO: these should be NameType
	// null for interfaces and classes without a superclass
	std::unique_ptr<Type> superClass;
	// implements if we're a class, extends if we're an interface
	std::vector<std::unique_ptr<Type>> interfaces;
	std::vector<std::unique_ptr<MemberDeclaration>> members;

	std::string toCode() override;

	// Fully qualified name (with package string)
	std::string fqn;

	// Used in topological sort of class hierarchy.
	std::vector<TypeDeclaration *> children;

	//
	// Implements formal hierarchy checking
	// Exact container types may be changed to facilitate easier access
	// or iteration
	//

	// Super.
	// Need to contain all top level parents
	std::vector<TypeDeclaration *> superSet;

	// Declare.
	// Should be a copy of "members" field above. Exists to make things clear.
	std::vector<MemberDeclaration *> declareSet;

	// Inherit.
	// Should copy from all parents.
	std::vector<MemberDeclaration *> inheritSet;

	// Contain.
	// Should be a concatination of declareSet and inheritSet above.
	std::vector<MemberDeclaration *> containSet;
};

} //namespace AST
