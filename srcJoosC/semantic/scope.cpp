#include "semantic/scope.h"
#include "ast/variableDeclaration.h"

namespace Semantic {

Scope::Scope(AST::TypeDeclaration *enclosingClass)
		: _enclosingClass(enclosingClass), _enclosingMethod(nullptr)
{
}
Scope::Scope(Scope &parent)
		: _enclosingClass(parent._enclosingClass), _enclosingMethod(parent._enclosingMethod),
		  _parent(parent), _declarations(parent._declarations)
{
}
Scope::Scope(Scope &parent, AST::MethodDeclaration *enclosingMethod)
		: _enclosingClass(parent._enclosingClass), _enclosingMethod(enclosingMethod),
		  _parent(parent), _declarations(parent._declarations)
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

bool Scope::isRoot()
{
	return &_parent == this;
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
