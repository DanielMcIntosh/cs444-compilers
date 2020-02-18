#include "ast/methodDeclaration.h"
#include "ast/memberDeclaration.h"
#include "ast/methodHeader.h"
#include "parse/parseTree.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<MethodDeclaration> MethodDeclaration::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (isSingleton(ptNode))
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

MethodDeclaration::MethodDeclaration(MethodHeader&& header, std::unique_ptr<Block> block)
  : MemberDeclaration(std::move(header.modifiers), std::move(header.id)),
    returnType(std::move(header.returnType)),
    parameters(std::move(header.parameterList)),
    body(std::move(block))
{
}
MethodDeclaration::MethodDeclaration(const Parse::TAbstractMethodDeclaration *ptNode)
  : MethodDeclaration(MethodHeader(ptNode->methodHeader), nullptr)
{
}
MethodDeclaration::MethodDeclaration(const Parse::TMethodDeclaration *ptNode)
  : MethodDeclaration(MethodHeader(ptNode->methodHeader), Block::create(ptNode->methodBody->block))
{
}
std::string MethodDeclaration::toCode() {
    std::string s = returnType->toCode() + " " + identifier + "(";
    for (const auto& p : parameters)
    {
    	s += p->toCode() + ", ";
    }
    if (!parameters.empty()) {
		s.pop_back();
		s.pop_back();
	}
    s += ") ";
    if (body)
    {
    	s += body->toCode();
    }
    return s;
}

bool MethodDeclaration::equals(FieldDeclaration *other) {
  return false;
}

bool MethodDeclaration::equals(MemberDeclaration *other) {
  return false;
}

bool MethodDeclaration::equals(ConstructorDeclaration *other) {
  return false;
}

bool MethodDeclaration::equals(MethodDeclaration *other) {
  if (parameters.size() != other->parameters.size())
    return false;
  for (size_t i = 0; i < parameters.size(); ++i) {
    if (!parameters[i]->equals(other->parameters[i].get()))
      return false;
  }

  return identifier == other->identifier;
}

} //namespace AST
