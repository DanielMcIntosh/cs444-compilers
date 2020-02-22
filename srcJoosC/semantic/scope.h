#pragma once

namespace Semantic {

// e.g. Scope<TypeDeclaration>, Scope<VariableDeclaration>, or Scope<MethodDeclaration>
template<class Decl>
class Scope {
public:
	Scope() = default;
	Scope(Scope &parent);
	Scope &_parent = *this;
	std::vector<Decl> declarations;
};

} // namespace Semantic

