#include "ast/typeDeclaration.h"
#include "ast/type.h"
#include "ast/modifier.h"
#include "ast/memberDeclaration.h"
#include "ast/nodeList.h"
#include "ast/typeBody.h"
#include "ast/name.h"
#include "parse/parseTree.h"
#include "semantic/semantic.h"
#include <memory>
#include <vector>
#include <string>

namespace AST
{

// static
std::unique_ptr<TypeDeclaration> TypeDeclaration::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (isSingleton(ptNode))
	{
		return TypeDeclaration::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::ClassDeclaration:
		return std::make_unique<TypeDeclaration>(static_cast<const Parse::TClassDeclaration*>(ptNode));
	case Parse::NonTerminalType::InterfaceDeclaration:
		return std::make_unique<TypeDeclaration>(static_cast<const Parse::TInterfaceDeclaration*>(ptNode));
	case Parse::NonTerminalType::TypeDeclaration:
		return std::make_unique<TypeDeclaration>(static_cast<const Parse::TTypeDeclaration*>(ptNode));
	default:
		FAILED("inappropriate PT type for TypeDeclaration: " + std::to_string((int)ptNode->type));
	}
}

TypeDeclaration::TypeDeclaration(const Parse::TTypeDeclaration *ptNode)
{
}

TypeDeclaration::TypeDeclaration(const Parse::TClassDeclaration *ptNode)
{
	isInterface = false; // depends only on which constructor is called
	// modifiers is a list of Modifier, use NodeList<Modifier> to extract it as a vector
	modifiers = std::move(NodeList<Modifier>(ptNode->modifiers).list);
	// TIdentifier isn't actually a non-terminal, so there is no PseudoAST class for it
	name = ptNode->identifier->value;
	// Simple case - we need a unique_ptr<Type>, so call Type::create
	// Also note that we don't need to call std::move because the return is an r-value
	superClass = ptNode->classType ? Type::create(ptNode->classType) : nullptr;
	// similar to modifiers
	interfaces = std::move(NodeList<Type>(ptNode->interfaceTypeList).list);
	// Since nothing sub-classes TypeBody, and none of the rules for TypeBody are oneNT rules,
	// we can directly call the constructor, giving us a little bit more type safety.
	// Also note, since TypeBody is only a PseudoAST class, we won't store the
	// TypeBody itself. Instead we need to extract the relevant contents.
	members = std::move(TypeBody(ptNode->classBody).members);
}

TypeDeclaration::TypeDeclaration(const Parse::TInterfaceDeclaration *ptNode)
{
	isInterface = true;
	modifiers = std::move(NodeList<Modifier>(ptNode->modifiers).list);
	// TIdentifier isn't actually a non-terminal, so there is no PseudoAST class for it
	name = ptNode->identifier->value;
	// this line is optional, but having it here means we have an explicit initialization for all members
	superClass = nullptr;
	interfaces =std::move(NodeList<Type>(ptNode->extendsInterfaces).list);
	members = std::move(TypeBody(ptNode->interfaceBody).members);
}

std::string TypeDeclaration::toCode() const
{
	if (name.empty())
	{
		return ";\n";
	}

	std::string str;
	for (auto &mod: modifiers)
	{
		str += mod->toCode() + " ";
	}
	str += !isInterface ? "class " : "interface ";
	str += name + " ";
	if (superClass)
	{
		str += "extends " + superClass->toCode() + " ";
	}
	if (!interfaces.empty())
	{
		str += !isInterface ? "implements " : "extends " ;
		for (auto &intf: interfaces)
		{
			str += intf->toCode() + ", ";
		}
		// pop the extra ", "
		str.pop_back();
		str.pop_back();
	}
	str += "\n{\n";
	for (auto &mem : members)
	{
		str += mem->toCode() + "\n";
	}
	str += "}\n";
	return str;
}

Semantic::SemanticErrorType TypeDeclaration::resolveSuperTypeNames(Semantic::SemanticDB const& semantic)
{
	if (superClass)
	{
		if (auto [decl, error] = semantic.resolveType(static_cast<NameType *>(superClass.get()), cpu, nullptr);
			error != Semantic::SemanticErrorType::None)
		{
			return error;
		} else
		{
			superClass->declaration = decl;
			decl->children.push_back(this);
		}
	}

	for (auto &intf: interfaces)
	{
		if (auto [decl, error] = semantic.resolveType(static_cast<NameType *>(intf.get()), cpu, nullptr);
			error != Semantic::SemanticErrorType::None)
		{
			return error;
		} else
		{
			intf->declaration = decl;
			decl->children.push_back(this);
		}
	}
	return Semantic::SemanticErrorType::None;
}

Semantic::SemanticErrorType TypeDeclaration::resolveBodyTypeNames(Semantic::SemanticDB const& semantic)
{
	return Semantic::SemanticErrorType::None;
}

} //namespace AST
