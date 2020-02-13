#include "ast/typeBody.h"
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
		throw std::runtime_error("inappropriate PT type for TypeBody: " + std::to_string((int)ptNode->type));
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

std::string TypeBody::toCode() {
    std::string s;
    for (const auto& m : members) s += m->toCode() + " ";
    return s;
}

} //namespace AST
