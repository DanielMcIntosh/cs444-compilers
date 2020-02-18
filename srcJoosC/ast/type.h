#pragma once

#include "ast/node.h"
#include "semantic/semantic.h"

#include <string>

namespace AST
{

class TypeDeclaration;
class CompilationUnit;
class PrimitiveType;
class NameType;

class Type: public Node
{
public:
	static std::unique_ptr<Type> create(const Parse::Tree *ptNode);

	bool isArray = false;
	TypeDeclaration *decl = nullptr;

	virtual Semantic::SemanticErrorType resolve(Semantic::SemanticDB *db, 
																							const CompilationUnit *cpu,
																							TypeDeclaration *typeDecl);

  virtual bool equals(PrimitiveType *) = 0;
  virtual bool equals(NameType *) = 0;
  virtual bool equals(Type *) = 0;

  static void setCurrentCompilationUnit(CompilationUnit *item);
  static void setCurrentTypeDeclaration(TypeDeclaration *item);
  static void reset();
  static Semantic::SemanticErrorType resolveAllBodyType(Semantic::SemanticDB *db);

protected:
	Type() = default;
};

} //namespace AST
