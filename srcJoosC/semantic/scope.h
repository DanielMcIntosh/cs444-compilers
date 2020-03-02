#pragma once

#include <memory>
#include <vector>
#include <string>
#include <ast/methodDeclaration.h>

namespace AST
{
	class VariableDeclaration;
	class TypeDeclaration;
}

namespace Semantic {

class Scope {
public:
	explicit Scope(AST::TypeDeclaration *enclosingClass);
	Scope(Scope &parent);
	Scope(Scope &parent, AST::MethodDeclaration *enclosingMethod);

	bool add(std::unique_ptr<AST::VariableDeclaration> const&);
	bool add(const AST::VariableDeclaration *);
	[[gnu::pure]]
	bool isRoot();
	const AST::VariableDeclaration *findDecl(std::string id) const;

	AST::TypeDeclaration * const _enclosingClass;
	// nullable
	AST::MethodDeclaration * const _enclosingMethod;
protected:
	Scope &_parent = *this;
	std::vector<const AST::VariableDeclaration *> _declarations;
private:
	[[gnu::pure]]
	bool doesConflict(const AST::VariableDeclaration *) const;
};

} // namespace Semantic

