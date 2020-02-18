#include "ast/name.h"
#include "ast/expression.h"
#include "ast/type.h"
#include "parse/parseTree.h"

#include <memory>
#include <vector>
#include <algorithm>

namespace AST
{

// static
std::unique_ptr<Name> Name::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (isSingleton(ptNode))
	{
		return Name::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::Name:
		return std::make_unique<Name>(static_cast<const Parse::TName*>(ptNode));
	default:
		throw std::runtime_error("inappropriate PT type for Name: " + std::to_string((int)ptNode->type));
	}
}

Name::Name(const Parse::TName *ptNode)
  : id(ptNode->identifier->value)
{
	if (ptNode->name)
	{
		Name pre = Name(ptNode->name);
		prefix = std::move(pre.prefix);
		prefix.push_back(std::move(pre.id));
	}
}

std::string Name::toCode()
{
	std::string str;
	for (auto &pre : prefix)
	{
		str += pre + ".";
	}
	str += id;
	return str;
}

bool Name::operator==(const Name &other) {
	return prefix == other.prefix && id == other.id;
}

std::string NameType::flatten() {
	return toCode();
}

NameType::NameType(Name &&other)
  : prefix(std::move(other.prefix)),
	id(std::move(other.id))
{
}

Semantic::SemanticErrorType NameType::resolve(Semantic::SemanticDB *db,
																							const CompilationUnit *cpu,
																							TypeDeclaration *typeDecl) {
	return Semantic::semanticResolveType(db, this, flatten(), cpu, typeDecl);
}

std::string NameType::toCode()
{
	std::string str;
	for (auto &pre : prefix)
	{
		str += pre + ".";
	}
	str += id;
	return str;
}

bool NameType::equals(PrimitiveType *other) {
  return false;
}

bool NameType::equals(NameType *other) {
  return decl == other->decl;
}

bool NameType::equals(Type *other) {
  return false;
}

NameExpression::NameExpression(Name &&other)
  : prefix(std::move(other.prefix)),
	id(std::move(other.id))
{
}

std::string NameExpression::toCode()
{
	std::string str;
	for (auto &pre : prefix)
	{
		str += pre + ".";
	}
	str += id;
	return str;
}

} //namespace AST
