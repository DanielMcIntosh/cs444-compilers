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
	if (ptNode->oneNt)
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
			throw std::runtime_error("inapropriate PT type for MemberDeclaration: " + std::to_string((int)ptNode->type));
	}
}

MemberDeclaration::MemberDeclaration(const Parse::TModifiers *ptModifiers, std::string const& id)
  : modifiers(std::move(NodeList<Modifier>((const Parse::Tree *)ptModifiers).list)),
	identifier(id)
{
}

} //namespace AST
