#pragma once

#include <memory>
#include <vector>
#include <string>

namespace AST
{
	class VariableDeclaration;
	class TypeDeclaration;
}

namespace Semantic {

class Scope {
public:
	Scope(AST::TypeDeclaration *enclosingClass);
	explicit Scope(Scope &parent);

	bool add(std::unique_ptr<AST::VariableDeclaration> const&);
	bool add(const AST::VariableDeclaration *);
	bool isRoot();
	const AST::VariableDeclaration *findDecl(std::string id) const;

	AST::TypeDeclaration * const _enclosingClass;
protected:
	Scope &_parent = *this;
	std::vector<const AST::VariableDeclaration *> _declarations;
private:
	bool doesConflict(const AST::VariableDeclaration *) const;
};

} // namespace Semantic

