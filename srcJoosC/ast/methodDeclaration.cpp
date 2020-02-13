#include "ast/methodDeclaration.h"
#include "ast/memberDeclaration.h"
#include "ast/methodHeader.h"
#include "ast/statement.h"
#include "ast/nodeList.h"
#include "parse/parseTree.h"
#include "primitiveType.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<MethodDeclaration> MethodDeclaration::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (ptNode->oneNt)
	{
		return MethodDeclaration::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::AbstractMethodDeclaration:
		return std::make_unique<MethodDeclaration>(static_cast<const Parse::TAbstractMethodDeclaration*>(ptNode));
	case Parse::NonTerminalType::MethodDeclaration:
		return std::make_unique<MethodDeclaration>(static_cast<const Parse::TMethodDeclaration*>(ptNode));
	default:
		throw std::runtime_error("inappropriate PT type for MethodDeclaration: " + std::to_string((int)ptNode->type));
	}
}
MethodDeclaration::MethodDeclaration(const Parse::TAbstractMethodDeclaration *ptNode)
  : MemberDeclaration(ptNode->methodHeader->modifiers, ptNode->methodHeader->methodDeclarator->identifier->value),
    returnType(Type::create(ptNode->methodHeader->type->v == Parse::TTypeV::PrimitiveType
                            ? static_cast<Parse::Tree *>(ptNode->methodHeader->type->primitiveType)
                            : static_cast<Parse::Tree *>(ptNode->methodHeader->type->referenceType))),
    parameters(std::move(NodeList<VariableDeclaration>(ptNode->methodHeader->methodDeclarator->formalParameterList).list))
{
}
MethodDeclaration::MethodDeclaration(const Parse::TMethodDeclaration *ptNode)
  : MemberDeclaration(ptNode->methodHeader->modifiers, ptNode->methodHeader->methodDeclarator->identifier->value),
    returnType(Type::create(ptNode->methodHeader->type->v == Parse::TTypeV::PrimitiveType
                            ? static_cast<Parse::Tree *>(ptNode->methodHeader->type->primitiveType)
                            : static_cast<Parse::Tree *>(ptNode->methodHeader->type->referenceType))),
    parameters(std::move(NodeList<VariableDeclaration>(ptNode->methodHeader->methodDeclarator->formalParameterList).list)),
    body(Block::create(ptNode->methodBody->block))
{
}
std::string MethodDeclaration::toCode() {
    std::string s = returnType->toCode() + " " + identifier + "(";
    for (const auto& p : parameters) s += p->type->toCode() + " " + p->identifier + ", ";
    if (s.back() != '(') {
		s.pop_back();
		s.pop_back();
	}
    s += ") ";
    if (body) s += body->toCode();
    return s;
}

} //namespace AST
