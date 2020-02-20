#include "ast/methodHeader.h"
#include "ast/node.h"
#include "ast/nodeList.h"
#include "ast/modifier.h"
#include "ast/type.h"
#include "ast/methodDeclarator.h"
#include "parse/parseTree.h"
#include "primitiveType.h"

#include <vector>
#include <memory>

namespace AST
{

// static
std::unique_ptr<MethodHeader> MethodHeader::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::MethodHeader:
		return std::make_unique<MethodHeader>(static_cast<const Parse::TMethodHeader*>(ptNode));
	default:
		FAILED("inappropriate PT type for MethodHeader: " + std::to_string((int)ptNode->type));
	}
}

MethodHeader::MethodHeader(std::vector<std::unique_ptr<Modifier>> mods, std::unique_ptr<Type> ret, MethodDeclarator&& declarator)
  : modifiers(std::move(mods)),
	returnType(std::move(ret)),
	id(std::move(declarator.id)),
	parameterList(std::move(declarator.parameterList))
{
	assert(returnType);
}
MethodHeader::MethodHeader(const Parse::TMethodHeader *ptNode)
  : MethodHeader(std::move(NodeList<Modifier>(ptNode->modifiers).list), Type::create(ptNode->type), MethodDeclarator(ptNode->methodDeclarator))
{
}

std::string MethodHeader::toCode() const
{
	// we're a PseudoAST node, so this shouldn't be called
	// therefore, we'll print something which is useful for debugging, but doesn't look like actual code
	std::string str = "[MethodHeader: modifiers={";
	for (auto &mod : modifiers)
	{
		str += mod->toCode();
		str += ",";
	}
	str += "}";
	str += " returnType=" + returnType->toCode();
	str += " id=" + id;
	str += " params={";
	for (auto &param : parameterList)
	{
		str += param->toCode();
		str += ",";
	}
	str += "}]";
	return str;
}

} //namespace AST
