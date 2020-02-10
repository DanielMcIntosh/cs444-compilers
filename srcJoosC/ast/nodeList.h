#pragma once

#include "ast/node.h"
#include "parse/parseTreeBase.h"
#include <memory>
#include <vector>

namespace AST
{

static inline bool isListType(const Parse::Tree *ptNode)
{
	switch (ptNode->type)
	{
		case Parse::NonTerminalType::ImportDeclarations:
		case Parse::NonTerminalType::Modifiers:
		case Parse::NonTerminalType::InterfaceTypeList:
		case Parse::NonTerminalType::ClassMemberDeclarations:
		case Parse::NonTerminalType::FormalParameterList:
		case Parse::NonTerminalType::ExtendsInterfaces:
		case Parse::NonTerminalType::InterfaceMemberDeclarations:
		case Parse::NonTerminalType::BlockStatements:
		case Parse::NonTerminalType::ArgumentList:
			return true;
		default:
			return false;
	}
}

template<class NodeType>
class NodeList: public Node
{
public:
	static std::unique_ptr<NodeList> create(const Parse::Tree *ptNode);
	NodeList(const Parse::Tree *ptNode);

	std::vector<std::unique_ptr<NodeType>> list;

	std::string toCode() override { return "[NodeList]"; }
};


} //namespace AST
