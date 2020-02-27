#pragma once
/**
 * Declaration of either a Class or Interface type
 */
#include "ast/node.h"
#include "ast/fieldDeclaration.h"
#include "ast/methodDeclaration.h"
#include "ast/constructorDeclaration.h"
#include <memory>
#include <vector>
#include <string>

namespace Semantic
{
	struct SemanticDB;
	enum class SemanticErrorType;
}

namespace AST
{

class FieldDeclaration;
class MethodDeclaration;
class Modifier;
class NameType;
class MemberDeclaration;
class ConstructorDeclaration;

class CompilationUnit;

// might not be sub-classed (i.e. can have empty 'type declarations' which are just a semicolon)
class TypeDeclaration: public Node
{
public:
	static std::unique_ptr<TypeDeclaration> create(const Parse::Tree *ptNode);
	explicit TypeDeclaration(const Parse::TTypeDeclaration *ptNode);
	explicit TypeDeclaration(const Parse::TClassDeclaration *ptNode);
	explicit TypeDeclaration(const Parse::TInterfaceDeclaration *ptNode);
	std::string toCode() const override;

	Semantic::SemanticErrorType resolveSuperTypeNames(Semantic::SemanticDB const& semantic);
	Semantic::SemanticErrorType resolveBodyTypeNames(Semantic::SemanticDB const& semantic);
	Semantic::SemanticErrorType resolveBodyExprs();

	Semantic::SemanticErrorType	generateHierarchySets(TypeDeclaration *, TypeDeclaration *);

	std::vector<TypeDeclaration *> getChildren();

	bool hasModifier(Modifier::Variant) const;

	// Fully qualified name (with package string)
	std::string fqn;
	// The compilation unit in which this type is declared.
	CompilationUnit *cpu = nullptr;
protected:
	bool isInterface;
	std::vector<std::unique_ptr<Modifier>> modifiers;
	// set for membership testing, including all implicit modifiers
	std::array<bool,static_cast<size_t>(Modifier::Variant::Max)> modifierSet{};

public:
	std::string name;
protected:
	// null for interfaces and classes without a superclass
	std::unique_ptr<NameType> superClass;
	// implements if we're a class, extends if we're an interface
	std::vector<std::unique_ptr<NameType>> interfaces;
	std::vector<std::unique_ptr<MemberDeclaration>> members;

	// Used in topological sort of class hierarchy.
	std::vector<TypeDeclaration *> children;

	std::vector<ConstructorDeclaration *> constructorSet;

	//
	// Implements formal hierarchy checking
	// Exact container types may be changed to facilitate easier access
	// or iteration
	//

	// Super.
	// Need to contain all top level parents
	std::vector<TypeDeclaration *> superSet;

	template <class DeclType>
	struct MemberSets{
		// Declare.
		// Should be a copy of "members" field above. Exists to make things clear.
		std::vector<DeclType *> declareSet;

		// Inherit.
		// Should copy from all parents.
		std::vector<DeclType *> inheritSet;

		// Contain.
		// Should be a concatenation of declareSet and inheritSet above.
		std::vector<DeclType *> containSet;
	};

	MemberSets<FieldDeclaration> fieldSets;
	MemberSets<MethodDeclaration> methodSets;
};

} //namespace AST
