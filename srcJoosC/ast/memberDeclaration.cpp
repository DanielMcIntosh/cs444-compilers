#include "ast/memberDeclaration.h"
#include "ast/fieldDeclaration.h"
#include "ast/constructorDeclaration.h"
#include "ast/variableDeclaration.h"
#include "ast/type.h"
#include "ast/methodDeclaration.h"
#include "ast/modifier.h"
#include "ast/statement.h"
#include "ast/expression.h"
#include "parse/parseTreeBase.h"
#include "semantic/semantic.h"

namespace AST
{

// static
std::unique_ptr<MemberDeclaration> MemberDeclaration::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (isSingleton(ptNode))
	{
		return MemberDeclaration::create(ptNode->children[0]);
	}

	switch(ptNode->type) {
		case Parse::NonTerminalType::FieldDeclaration:
			return FieldDeclaration::create(ptNode);
		case Parse::NonTerminalType::MethodDeclaration:
		case Parse::NonTerminalType::AbstractMethodDeclaration:
			return MethodDeclaration::create(ptNode);
		case Parse::NonTerminalType::ConstructorDeclaration:
			return ConstructorDeclaration::create(ptNode);
		default:
			FAILED("inappropriate PT type for MemberDeclaration: " + std::to_string((int)ptNode->type));
	}
}

MemberDeclaration::MemberDeclaration(std::vector<std::unique_ptr<Modifier>> mods)
  : modifiers(std::move(mods))
{
	// assume there are no duplicates for now
	// TODO: clarify what to do with duplicates
	for (const auto &mod : modifiers) {
		modifierSet[static_cast<size_t>(mod->type)] = true;
	}
}

bool MemberDeclaration::equals(FieldDeclaration *) {
	return false;
}

bool MemberDeclaration::equals(MemberDeclaration *) {
	return false;
}

bool MemberDeclaration::equals(ConstructorDeclaration *) {
	return false;
}

bool MemberDeclaration::equals(MethodDeclaration *) {
	return false;
}

bool MemberDeclaration::hasModifier(Modifier::Variant mod) const {
	return modifierSet[static_cast<size_t>(mod)];
}

} //namespace AST
