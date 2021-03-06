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
		  _declarations(parent._declarations)
{
}

bool Scope::add(std::unique_ptr<AST::VariableDeclaration> const& decl)
{
	return add(decl.get());
}
bool Scope::add(AST::VariableDeclaration *newDecl)
{
	if (doesConflict(newDecl))
	{
		return false;
	}

	newDecl->index = _declarations.size();
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

} // namespace Semantic
