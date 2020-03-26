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

class MemberDeclaration;
class FieldDeclaration;
class ConstructorDeclaration;
class MethodDeclaration;
class Modifier;
class NameType;
class ClassInstanceCreationExpression;
class MethodInvocation;
class FieldAccess;

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

	Semantic::SemanticErrorType resolveSuperTypeNames(Semantic::SemanticDB const& semantic, TypeDeclaration *object);
	Semantic::SemanticErrorType resolveBodyTypeNames(Semantic::SemanticDB const& semantic);
	Semantic::SemanticErrorType exprResolutionPrep();
	Semantic::SemanticErrorType precheckFieldInitializers();
	Semantic::SemanticErrorType resolveBodyExprs();

	Semantic::SemanticErrorType	generateHierarchySets(TypeDeclaration *, TypeDeclaration *);

  //
  // a4
  //

  void staticAnalysis(StaticAnalysisCtx *ctx);

	ConstructorDeclaration *findConstructor(ClassInstanceCreationExpression *invocation);
	MethodDeclaration *findMethod(MethodInvocation *invocation);
	FieldDeclaration *findField(FieldAccess *access);

	std::vector<TypeDeclaration *> getChildren();
	std::unique_ptr<NameType> asType();

	bool hasModifier(Modifier::Variant) const;
	bool isSamePackage(const TypeDeclaration *other) const;
	bool isSubClassOf(const TypeDeclaration *) const;

	// Fully qualified name (with package string)
	std::string fqn;
	// The compilation unit in which this type is declared.
	CompilationUnit *cpu = nullptr;
	bool isInterface;
protected:
	std::vector<std::unique_ptr<Modifier>> modifiers;
	// set for membership testing, including all implicit modifiers
	std::array<bool,static_cast<size_t>(Modifier::Variant::Max)> modifierSet{};

public:
	std::string name;

	// null for interfaces and classes without a superclass
	std::unique_ptr<NameType> superClass;
	// implements if we're a class, extends if we're an interface
	std::vector<std::unique_ptr<NameType>> interfaces;
	std::vector<std::unique_ptr<MemberDeclaration>> members;

	// Used in topological sort of class hierarchy.
	std::vector<TypeDeclaration *> children;

	std::vector<ConstructorDeclaration *> constructorSet;

	// Super.
	// Contains direct parents
	std::vector<TypeDeclaration *> superSet;

	// Contains direct and indirect parents
	std::vector<TypeDeclaration *> hyperSet;


	// For classes, these should line up with the data layout and vtable layout respectively
	// (when you skip the static fields/methods?)
	std::vector<FieldDeclaration *> fieldContainSet;
	std::vector<MethodDeclaration *> methodContainSet;

	// path of the source file containing this type
	std::string sourceFilePath;
};

} //namespace AST
