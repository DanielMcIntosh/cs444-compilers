#include "semantic/scope.h"
#include "ast/variableDeclaration.h"

namespace Semantic {

Scope::Scope(Scope &parent)
  : _parent(parent), _declarations(parent._declarations), _fields(parent._fields)
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
bool Scope::addField(std::unique_ptr<AST::VariableDeclaration> const& decl)
{
	return addField(decl.get());
}
bool Scope::addField(const AST::VariableDeclaration *newDecl)
{
	assert(isRoot());
	for (auto *decl : _fields)
	{
		if (newDecl->idEqual(decl))
		{
			return false;
		}
	}
	_fields.push_back(newDecl);
	return true;
}

bool Scope::isRoot()
{
	return &_parent == this;
}

bool Scope::doesConflict(const AST::VariableDeclaration *newDecl) const
{
	for (auto *decl : _declarations)
	{
		if (newDecl->idEqual(decl))
		{
			return true;
		}
	}
	return false;
}

} // namespace Semantic
