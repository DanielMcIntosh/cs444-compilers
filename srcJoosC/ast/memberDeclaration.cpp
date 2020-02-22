#include "ast/memberDeclaration.h"
#include "ast/fieldDeclaration.h"
#include "ast/constructorDeclaration.h"
#include "ast/methodDeclaration.h"
#include "ast/nodeList.h"
#include "parse/parseTreeBase.h"

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

} //namespace AST
