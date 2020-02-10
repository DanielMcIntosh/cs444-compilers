#include "ast/nodeList.h"
#include "ast/importDeclaration.h"
#include "ast/modifier.h"
#include "ast/type.h"
#include "ast/memberDeclaration.h"
#include "ast/variableDeclaration.h"
#include "ast/statement.h"
#include "ast/expression.h"
#include "parse/parseTreeBase.h"

namespace AST
{



// static
template<class NodeType>
std::unique_ptr<NodeList<NodeType>> NodeList<NodeType>::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	return std::make_unique<NodeList<NodeType>>(ptNode);
}

template<class NodeType>
NodeList<NodeType>::NodeList(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr)
	{
		return;
	}
	int numChildren = ptNode->numChildren;
	if (numChildren > 1)
	{
		list = std::move(NodeList<NodeType>(ptNode->children[0]).list);
	}
	list.push_back(NodeType::create(ptNode->children[numChildren-1]));
	assert(list.back());
}

template class NodeList<ImportDeclaration>;
template class NodeList<Modifier>;
template class NodeList<Type>;
template class NodeList<MemberDeclaration>;
template class NodeList<VariableDeclaration>;
template class NodeList<Statement>;
template class NodeList<Expression>;

} //namespace AST
