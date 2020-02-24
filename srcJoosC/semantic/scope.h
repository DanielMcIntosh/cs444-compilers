#pragma once

#include <memory>
#include <vector>

namespace AST
{
	class VariableDeclaration;
}

namespace Semantic {

class Scope {
public:
	Scope() = default;
	explicit Scope(Scope &parent);

	bool add(std::unique_ptr<AST::VariableDeclaration> const&);
	bool add(const AST::VariableDeclaration *);
	bool addField(std::unique_ptr<AST::VariableDeclaration> const&);
	bool addField(const AST::VariableDeclaration *);
	bool isRoot();

	Scope &_parent = *this;
	std::vector<const AST::VariableDeclaration *> _declarations;
	std::vector<const AST::VariableDeclaration *> _fields;
private:
	bool doesConflict(const AST::VariableDeclaration *) const;
};

} // namespace Semantic

