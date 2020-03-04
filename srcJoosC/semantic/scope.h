#pragma once

#include <memory>
#include <vector>
#include <string>
#include <variant>

namespace AST
{
	class VariableDeclaration;
	class TypeDeclaration;
	class MethodDeclaration;
	class ConstructorDeclaration;
	class FieldDeclaration;
}

namespace Semantic {

class Scope {
public:
	explicit Scope(AST::TypeDeclaration *enclosingClass);
	explicit Scope(AST::TypeDeclaration *enclosingClass, AST::MethodDeclaration *enclosingMethod);
	explicit Scope(AST::TypeDeclaration *enclosingClass, AST::ConstructorDeclaration *enclosingMethod);
	Scope(Scope &parent);

	bool add(std::unique_ptr<AST::VariableDeclaration> const&);
	bool add(const AST::VariableDeclaration *);
	const AST::VariableDeclaration *findDecl(std::string id) const;

	AST::TypeDeclaration * const _enclosingClass;
	// nullable
	std::variant<AST::MethodDeclaration *, AST::ConstructorDeclaration *> const _enclosingMethod;
	const AST::VariableDeclaration *_currentDeclaration = nullptr;
protected:
	std::vector<const AST::VariableDeclaration *> _declarations;
private:
	[[gnu::pure]]
	bool doesConflict(const AST::VariableDeclaration *) const;
};

} // namespace Semantic

