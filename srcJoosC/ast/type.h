#pragma once

#include "ast/node.h"
#include "semantic/semantic.h"

#include <string>

namespace AST
{

class TypeDeclaration;
class CompilationUnit;

class Type: public Node
{
public:
	static std::unique_ptr<Type> create(const Parse::Tree *ptNode);

	bool isArray = false;

  TypeDeclaration *decl;

	virtual Semantic::SemanticErrorType resolve(Semantic::SemanticDB *db, 
																							const CompilationUnit *cpu,
																							TypeDeclaration *typeDecl);
protected:
	Type() = default;
};

} //namespace AST
