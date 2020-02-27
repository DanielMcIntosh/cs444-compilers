#include "ast/typeDeclaration.h"
#include "ast/methodDeclaration.h"
#include "ast/variableDeclaration.h"
#include "ast/statement.h"
#include "ast/type.h"
#include "ast/modifier.h"
#include "ast/nodeList.h"
#include "ast/typeBody.h"
#include "ast/name.h"
#include "ast/methodDeclaration.h"
#include "parse/parseTree.h"
#include "semantic/semantic.h"
#include "semantic/scope.h"
#include <memory>
#include <vector>
#include <string>
#include <unordered_set>

using Semantic::SemanticErrorType;

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
  :	isInterface(false)
{
	nodeType = NodeType::TypeDeclaration;
}

TypeDeclaration::TypeDeclaration(const Parse::TClassDeclaration *ptNode)
  :	isInterface(false), // depends only on which constructor is called
	// modifiers is a list of Modifier, use NodeList<Modifier> to extract it as a vector
	modifiers(std::move(NodeList<Modifier>(ptNode->modifiers).list)),
	// TIdentifier isn't actually a non-terminal, so there is no PseudoAST class for it
	name(ptNode->identifier->value),
	// Simple case - we need a unique_ptr<NameType>, so call NameType::create
	// Also note that we don't need to call std::move because the return is an r-value
	superClass(ptNode->classType ? NameType::create(ptNode->classType) : nullptr),
	// similar to modifiers
	interfaces(std::move(NodeList<NameType>(ptNode->interfaceTypeList).list)),
	// Since nothing sub-classes TypeBody, and none of the rules for TypeBody are oneNT rules,
	// we can directly call the constructor, giving us a little bit more type safety.
	// Also note, since TypeBody is only a PseudoAST class, we won't store the
	// TypeBody itself. Instead we need to extract the relevant contents.
	members(std::move(TypeBody(ptNode->classBody).members))
{
	nodeType = NodeType::TypeDeclaration;
	// assume there are no duplicates for now
	// TODO: clarify what to do with duplicates
	for (const auto &mod : modifiers) {
		modifierSet[static_cast<size_t>(mod->type)] = true;
	}
}

TypeDeclaration::TypeDeclaration(const Parse::TInterfaceDeclaration *ptNode)
  :	isInterface(true),
	modifiers(std::move(NodeList<Modifier>(ptNode->modifiers).list)),
	// TIdentifier isn't actually a non-terminal, so there is no PseudoAST class for it
	name(ptNode->identifier->value),
	// this line is optional, but having it here means we have an explicit initialization for all members
	superClass(nullptr),
	interfaces(std::move(NodeList<NameType>(ptNode->extendsInterfaces).list)),
	members(std::move(TypeBody(ptNode->interfaceBody).members))
{
	nodeType = NodeType::TypeDeclaration;
	// assume there are no duplicates for now
	// TODO: clarify what to do with duplicates
	for (const auto &mod : modifiers) {
		modifierSet[static_cast<size_t>(mod->type)] = true;
	}
	// interfaces are implicitly abstract
	modifierSet[static_cast<size_t>(Modifier::Variant::Abstract)] = true;
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

SemanticErrorType TypeDeclaration::resolveSuperTypeNames(Semantic::SemanticDB const& semantic, TypeDeclaration* object)
{
	if (!superClass && !isInterface && fqn != "java.lang.Object") {
		object->children.push_back(this);
	}
	if (superClass)
	{
		if (SemanticErrorType err = superClass->resolve(semantic, this);
			err != SemanticErrorType::None)
		{
			return err;
		}
		superClass->getDeclaration()->children.push_back(this);
	}

	for (auto &intf: interfaces)
	{
		if (SemanticErrorType err = intf->resolve(semantic, this);
			err != SemanticErrorType::None)
		{
			return err;
		}
		intf->getDeclaration()->children.push_back(this);
	}
	return SemanticErrorType::None;
}

SemanticErrorType TypeDeclaration::resolveBodyTypeNames(Semantic::SemanticDB const& semantic)
{
	// TODO: change this?
	/*
	for (auto *decl : methodSets.containSet)
	{
		if (SemanticErrorType err = decl->resolveTypes(semantic, this);
			err != SemanticErrorType::None)
		{
			return err;
		}
	}
	/*/
	for (auto &decl : members)
	{
		if (SemanticErrorType err = decl->resolveTypes(semantic, this);
			err != SemanticErrorType::None)
		{
			return err;
		}
	}
	//*/
	return SemanticErrorType::None;
}

SemanticErrorType TypeDeclaration::resolveMethods()
{
	if (isInterface)
	{
		return SemanticErrorType::None;
	}

	// TODO: actually resolve methods first, THEN add the 'this' parameter
	for (auto *decl : methodSets.declareSet)
	{
		decl->addThisParam(this);
	}
	for (auto *decl : constructorSet)
	{
		decl->addThisParam(this);
	}
	return SemanticErrorType::None;
}

SemanticErrorType TypeDeclaration::resolveBodyExprs()
{
	// TODO: change this?
	Semantic::Scope scope(this);
	/*
	for (auto *decl : fieldSets.containSet)
	{
		if (SemanticErrorType err = decl->resolveExprs(scope);
			err != SemanticErrorType::None)
		{
			return err;
		}
	}
	for (auto *decl : methodSets.containSet)
	{
		if (SemanticErrorType err = decl->resolveExprs(scope);
			err != SemanticErrorType::None)
		{
			return err;
		}
	}
	/*/
	for (auto &decl : members)
	{
		if (SemanticErrorType err = decl->resolveExprs(scope);
			err != SemanticErrorType::None)
		{
			return err;
		}
	}
	//*/
	return SemanticErrorType::None;
}

SemanticErrorType TypeDeclaration::generateHierarchySets(TypeDeclaration *object, TypeDeclaration *iObject)
{
	TypeDeclaration *super = superClass ? superClass->getDeclaration() : nullptr;

	// If this is a class without a superclass, extend java.lang.Object
	if (!isInterface && !superClass && fqn != "java.lang.Object") {
		super = object;
	}
	if (super) {
		// A class must not extend an interface
		if (super->isInterface) {
			return SemanticErrorType::ExtendNonClass;
		}

		// A class must not extend a final class
		for (auto &mod : super->modifiers) {
			if (mod->type == Modifier::Variant::Final) {
				return SemanticErrorType::ExtendFinalClass;
			}
		}
	}

	// build extends set
	std::unordered_set<TypeDeclaration *> extends;
	for (auto &itf : interfaces) {
		assert(itf->getDeclaration());
		// A class must not implement a class
		if (!itf->getDeclaration()->isInterface) {
			return SemanticErrorType::ImplementNonInterface;
		}

		// Hierarchy check 1: A class cannot extend itself
		if (itf->getDeclaration() == super) {
			return SemanticErrorType::ExtendImplementSame;
		}

		// An interface must not be repeated in an implements clause, or in an extends clause of an interface
		auto it = extends.find(itf->getDeclaration());
		if (it != extends.end()) {
			return SemanticErrorType::ImplementSameInterface;
		}

		extends.insert(itf->getDeclaration());
	}

	// build super set (only direct superclasses)
	if (super) {
		superSet.push_back(super);
	}
	for (auto *ext : extends) {
		superSet.push_back(ext);
	}

	// If this is an interface without a superinterface, add IObject methods to declare set
	if (isInterface && !superClass && fqn != "java.lang.IObject") {
		for (auto &member : iObject->members) {
			assert(member->getTypeId() == 1);
			auto m = static_cast<MethodDeclaration*>(member.get());
			methodSets.declareSet.push_back(m);
		}
	}
	// build declare sets
	for (auto &member : members) {
		if (member->getTypeId() == 0) {
			auto f = static_cast<FieldDeclaration*>(member.get());
			for (const auto &g : fieldSets.declareSet) {
				// Hierarchy check 10: cannot declare multiple fields with the same name
				if (f->idEquals(g)) {
					return SemanticErrorType::DuplicateFieldDeclaration;
				}
			}
			fieldSets.declareSet.push_back(f);
		} else if (member->getTypeId() == 1) {
			auto m = static_cast<MethodDeclaration*>(member.get());
			for (const auto &n : methodSets.declareSet) {
				// Hierarchy check 2: No duplicate methods
				if (m->signatureEquals(n)) {
					return SemanticErrorType::DuplicateMethodDeclaration;
				}
				// Hierarchy check 4: classes with abstract methods must be abstract
				if (n->hasModifier(Modifier::Variant::Abstract) && !hasModifier(Modifier::Variant::Abstract)) {
					return SemanticErrorType::AbstractClassNotAbstract;
				}
			}
			methodSets.declareSet.push_back(m);
		} else {
			auto c = static_cast<ConstructorDeclaration*>(member.get());
			for (const auto &d : constructorSet) {
				if (c->signatureEquals(d)) {
					return SemanticErrorType::DuplicateConstructorDeclaration;
				}
			}
			constructorSet.push_back(c);
		}
	}

	// replace set for methods
	std::vector<std::pair<MethodDeclaration *, MethodDeclaration *>> overrides;

	// inheriting methods
	for (const auto &s : superSet) {
		for (const auto &m : s->methodSets.containSet) {
			bool noDecl = true;
			for (const auto &n : methodSets.declareSet) {
				if (m->signatureEquals(n)) {
					noDecl = false;
					break;
				}
			}
			if (m->hasModifier(Modifier::Variant::Abstract)) {
				bool allAbstract = true;
				for (const auto &s : superSet) {
					for (const auto &n : s->methodSets.containSet) {
						if (m->signatureEquals(n) && !n->hasModifier(Modifier::Variant::Abstract)) {
							allAbstract = false;
							// Replacing abstract with concrete method
							overrides.emplace_back(n, m);
						}
					}
					if (!allAbstract)
						break;
				}
				if (noDecl && allAbstract) {
					// Inheriting abstract method
					methodSets.inheritSet.push_back(m);
				}
			} else {
				if (noDecl) {
					// Inheriting non-abstract method
					methodSets.inheritSet.push_back(m);
				}
			}
		}
	}

	// inheriting fields
	for (const auto &s : superSet) {
		for (const auto &f : s->fieldSets.containSet) {
			bool unique = true;
			for (const auto &g : fieldSets.declareSet) {
				if (f->idEquals(g)) {
					unique = false;
					break;
				}
			}
			if (unique) {
				fieldSets.inheritSet.push_back(f);
			}
		}
	}

	// overriding methods in superclasses
	for (const auto &s : superSet) {
		for (const auto &m : methodSets.declareSet) {
			for (const auto &n : s->methodSets.containSet) {
				if (m->signatureEquals(n)) {
					overrides.emplace_back(m, n);
				}
			}
		}
	}

	for (const auto &[m, n] : overrides) {
		// Hierarchy check 5: Static methods can only override and be overriden by static methods
		if ((m->hasModifier(Modifier::Variant::Static) && !n->hasModifier(Modifier::Variant::Static)) ||
			(!m->hasModifier(Modifier::Variant::Static) && n->hasModifier(Modifier::Variant::Static))) {
			return SemanticErrorType::OverrideStatic;
		}
		// Hierarchy check 6: Methods can only override methods with the same return type
		if (!m->returnEquals(n)) {
			return SemanticErrorType::OverrideDifferentReturn;
		}
		// Hierarchy check 7: Only public methods can override public methods
		if (n->hasModifier(Modifier::Variant::Public) && !m->hasModifier(Modifier::Variant::Public)) {
			return SemanticErrorType::OverridePublic;
		}
		// Hierarchy check 9: Cannot override final methods
		if (n->hasModifier(Modifier::Variant::Final)) {
			return SemanticErrorType::OverrideFinal;
		}
	}

	methodSets.containSet.insert(methodSets.containSet.end(), methodSets.declareSet.begin(), methodSets.declareSet.end());
	methodSets.containSet.insert(methodSets.containSet.end(), methodSets.inheritSet.begin(), methodSets.inheritSet.end());
	fieldSets.containSet.insert(fieldSets.containSet.end(), fieldSets.declareSet.begin(), fieldSets.declareSet.end());
	fieldSets.containSet.insert(fieldSets.containSet.end(), fieldSets.inheritSet.begin(), fieldSets.inheritSet.end());

	// Hierarchy check 4: classes with abstract methods must be abstract
	for (const auto &m : methodSets.containSet) {
		if (m->hasModifier(Modifier::Variant::Abstract)) {
			if (!hasModifier(Modifier::Variant::Abstract)) {
				return SemanticErrorType::AbstractClassNotAbstract;
			}
			break;
		}
	}

	// Hierarchy check 3: One return type per unique signature
	for (const auto &m : methodSets.containSet) {
		for (const auto &n : methodSets.containSet) {
			if (m->signatureEquals(n) && !m->returnEquals(n)) {
				return SemanticErrorType::AmbiguousReturnType;
			}
		}
	}

	return SemanticErrorType::None;
}

std::vector<TypeDeclaration *> TypeDeclaration::getChildren()
{
	return children;
}

std::unique_ptr<NameType> TypeDeclaration::asType()
{
	return std::make_unique<NameType>(this, name);
}

bool TypeDeclaration::hasModifier(Modifier::Variant mod) const {
	return modifierSet[static_cast<size_t>(mod)];
}

} //namespace AST
