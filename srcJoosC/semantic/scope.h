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
	class Block;
	class ConditionalStatement;
}

namespace Semantic {

class Scope {
public:
	bool add(std::unique_ptr<AST::VariableDeclaration> const&);
	bool add(AST::VariableDeclaration *);
	const AST::VariableDeclaration *findDecl(std::string id) const;

	AST::TypeDeclaration * _enclosingClass;
	// nullable
	std::variant<AST::MethodDeclaration *, AST::ConstructorDeclaration *> _enclosingMethod;
	const AST::VariableDeclaration *_currentDeclaration = nullptr;
	std::vector<const AST::VariableDeclaration *> _declarations;

	friend class AST::FieldDeclaration;
	friend class AST::MethodDeclaration;
	friend class AST::ConstructorDeclaration;
	friend class AST::Block;
	friend class AST::ConditionalStatement;
private:
	[[gnu::pure]]
	bool doesConflict(const AST::VariableDeclaration *) const;

	explicit Scope(AST::TypeDeclaration *enclosingClass);
	explicit Scope(AST::TypeDeclaration *enclosingClass, AST::MethodDeclaration *enclosingMethod);
	explicit Scope(AST::TypeDeclaration *enclosingClass, AST::ConstructorDeclaration *enclosingMethod);
	explicit Scope(Scope &parent);
};

} // namespace Semantic

