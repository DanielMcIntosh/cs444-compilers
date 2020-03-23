#include "semantic/scope.h"
#include "ast/variableDeclaration.h"

namespace Semantic {

Scope::Scope(AST::TypeDeclaration *enclosingClass)
		: _enclosingClass(enclosingClass)
{
}
Scope::Scope(AST::TypeDeclaration *enclosingClass, AST::MethodDeclaration *enclosingMethod)
		: _enclosingClass(enclosingClass), _enclosingMethod(enclosingMethod)
{
}
Scope::Scope(AST::TypeDeclaration *enclosingClass, AST::ConstructorDeclaration *enclosingMethod)
		: _enclosingClass(enclosingClass), _enclosingMethod(enclosingMethod)
{
}
Scope::Scope(Scope &parent)
		: _enclosingClass(parent._enclosingClass), _enclosingMethod(parent._enclosingMethod),
		  _declarations(parent._declarations), _numParam(parent._numParam)
{
}

bool Scope::add(std::unique_ptr<AST::VariableDeclaration> const& decl)
{
	return add(decl.get());
}
bool Scope::add(const AST::VariableDeclaration *newDecl)
{
	if (doesConflict(newDecl))
	{
		return false;
	}

	_declarations.push_back(newDecl);
	return true;
}

const AST::VariableDeclaration *Scope::findDecl(std::string id) const
{
	for (auto *decl : _declarations)
	{
		if (decl->idEquals(id))
		{
			return decl;
		}
	}
	return nullptr;
}

bool Scope::doesConflict(const AST::VariableDeclaration *newDecl) const
{
	for (auto *decl : _declarations)
	{
		if (newDecl->idEquals(decl))
		{
			return true;
		}
	}
	return false;
}

Scope::Scope() {

}

Scope & Scope::operator=(const Scope& other) {
	if (&other == this)
		return *this;

	_enclosingClass = other._enclosingClass;
	_enclosingMethod = other._enclosingMethod;
	_currentDeclaration = other._currentDeclaration;
	_declarations = other._declarations;
	_numParam = other._numParam;

	return *this;
}

} // namespace Semantic
