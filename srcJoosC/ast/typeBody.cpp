#include "ast/typeBody.h"
#include "ast/memberDeclaration.h"
#include "ast/modifier.h"
#include "ast/nodeList.h"
#include "parse/parseTree.h"

namespace AST
{

// static
std::unique_ptr<TypeBody> TypeBody::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::ClassBody:
		return std::make_unique<TypeBody>(static_cast<const Parse::TClassBody*>(ptNode));
	case Parse::NonTerminalType::InterfaceBody:
		return std::make_unique<TypeBody>(static_cast<const Parse::TInterfaceBody*>(ptNode));
	default:
		FAILED("inappropriate PT type for TypeBody: " + std::to_string((int)ptNode->type));
	}
}
TypeBody::TypeBody(const Parse::TClassBody *ptNode)
  : members(std::move(NodeList<MemberDeclaration>(ptNode->classMemberDeclarations).list))
{
}
TypeBody::TypeBody(const Parse::TInterfaceBody *ptNode)
  : members(std::move(NodeList<MemberDeclaration>(ptNode->interfaceMemberDeclarations).list))
{
}

std::string TypeBody::toCode() const {
    std::string s = "[TypeBody: members={";
    for (const auto& m : members) s += m->toCode() + ", ";
    s += "}]";
    return s;
}

} //namespace AST
