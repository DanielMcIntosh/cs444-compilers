#include "ast/type.h"
#include "ast/name.h"
#include "ast/expression.h"
#include "parse/parseTree.h"
#include "semantic/semantic.h"
#include <memory>
#include <ostream>

namespace AST
{

//////////////////////////////////////////////////////////////////////////////
//
// toCode
//
//////////////////////////////////////////////////////////////////////////////

std::string NameType::toCode() const
{
	return flatten();
}

std::string PrimitiveType::toCode() const
{
	return "" + type;
}

//////////////////////////////////////////////////////////////////////////////
//
// create function
//
//////////////////////////////////////////////////////////////////////////////

// static
std::unique_ptr<NameType> NameType::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (isSingleton(ptNode)) {
		return NameType::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
		case Parse::NonTerminalType::ArrayType:
		{
			std::unique_ptr<NameType> ret = NameType::create(ptNode->children[0]);
			ret->isArray = true;
			return ret;
		}
		case Parse::NonTerminalType::Name:
			return std::make_unique<NameType>(std::move(*Name::create(ptNode)));
		default:
			FAILED("inappropriate PT type for NameType: " + std::to_string((int)ptNode->type));
	}
}

// static
std::unique_ptr<PrimitiveType> PrimitiveType::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		// Type is never nullable, but "void" doesn't show up in the PT, so we use nullptr to indicate type void
		return std::unique_ptr<PrimitiveType>(new PrimitiveType(nullptr));
	}
	switch(ptNode->type) {
		case Parse::NonTerminalType::PrimitiveType:
			return std::make_unique<PrimitiveType>(static_cast<const Parse::TPrimitiveType*>(ptNode));
		default:
			FAILED("inappropriate PT type for PrimitiveType: " + std::to_string((int)ptNode->type));
	}
}

// static
std::unique_ptr<Type> Type::create(const Parse::Tree *ptNode)
{
	// Type is never nullable, but "void" doesn't show up in the PT, so we use nullptr to indicate type void
	if (ptNode == nullptr) {
		return PrimitiveType::create(nullptr);
	}
	if (isSingleton(ptNode)) {
		return Type::create(ptNode->children[0]);
	}

	switch(ptNode->type) {
		case Parse::NonTerminalType::ArrayType:
		{
			std::unique_ptr<Type> ret = Type::create(ptNode->children[0]);
			ret->isArray = true;
			return ret;
		}
		case Parse::NonTerminalType::PrimitiveType:
			return PrimitiveType::create(ptNode);
		case Parse::NonTerminalType::Name:
			return NameType::create(ptNode);
		default:
			FAILED("inappropriate PT type for Type: " + std::to_string((int)ptNode->type));
	}
}

//////////////////////////////////////////////////////////////////////////////
//
// Constructor and others
//
//////////////////////////////////////////////////////////////////////////////

NameType::NameType(Name &&other)
	: ids(std::move(other.ids))
{
	nodeType = NodeType::NameType;
}
NameType::NameType(Name const& other)
	: ids(other.ids)
{
	nodeType = NodeType::NameType;
}
NameType::NameType(TypeDeclaration *decl, std::string name)
  :	ids{std::move(name)},
	declaration(decl)
{
	nodeType = NodeType::NameType;
}
NameType::NameType(std::vector<std::string> identifiers, bool arr, TypeDeclaration *decl)
  :	ids(std::move(identifiers)),
	declaration(decl)
{
	nodeType = NodeType::NameType;
	isArray = arr;
}
NameType* NameType::clone() const
{
	return new NameType(ids, isArray, declaration); //pass ids by value results in copy
}

std::string NameType::flatten() const {
	std::string str;
	for (auto &id : ids)
	{
		str += id + ".";
	}
	// pop off the trailing "."
	str.pop_back();
	return str;
}

TypeDeclaration *NameType::getDeclaration()
{
	return declaration;
}

bool NameType::equals(const TypeResult &other) const
{
	return !other.isPrimitive && (isArray == other.isArray) && (declaration == other.userDefinedType);
}


static_assert( (int)Parse::TPrimitiveTypeV::boolean	== (int)PrimitiveType::Variant::Boolean);
static_assert( (int)Parse::TPrimitiveTypeV::byte   	== (int)PrimitiveType::Variant::Byte);
static_assert( (int)Parse::TPrimitiveTypeV::Short  	== (int)PrimitiveType::Variant::Short);
static_assert( (int)Parse::TPrimitiveTypeV::Int    	== (int)PrimitiveType::Variant::Int);
static_assert( (int)Parse::TPrimitiveTypeV::Char   	== (int)PrimitiveType::Variant::Char);
PrimitiveType::PrimitiveType(const Parse::TPrimitiveType *ptNode)
	: type{(int)ptNode->v}
{
	nodeType = NodeType::PrimitiveType;
	assert(type <= Variant::Max && type != Variant::Void);
}
PrimitiveType::PrimitiveType(std::nullptr_t)
	: type(Variant::Void)
{
	nodeType = NodeType::PrimitiveType;
}
PrimitiveType::PrimitiveType(Variant var, bool arr)
  :	type(var)
{
	nodeType = NodeType::PrimitiveType;
	isArray = arr;
}

PrimitiveType* PrimitiveType::clone() const
{
	return new PrimitiveType(type, isArray);
}

bool PrimitiveType::equals(const TypeResult &other) const
{
	return other.isPrimitive && (isArray == other.isArray) && (type == (PrimitiveType::Variant)other.primitiveType);
}


std::string operator+=(std::string& str, PrimitiveType::Variant type)
{
	switch(type)
	{
		case PrimitiveType::Variant::Boolean:	return str += "boolean";
		case PrimitiveType::Variant::Byte:   	return str += "byte";
		case PrimitiveType::Variant::Short:  	return str += "short";
		case PrimitiveType::Variant::Int:    	return str += "int";
		case PrimitiveType::Variant::Char:   	return str += "char";
		case PrimitiveType::Variant::Void:   	return str += "void";
		case PrimitiveType::Variant::Null:   	return str += "null_t";
		case PrimitiveType::Variant::Max:		;// fallthrough
			// no default to trigger compiler warning on missing case
	}
	FAILED("String conversion on invalid PrimitiveType type: " + std::to_string((int)type));
}
std::string operator+(std::string str, PrimitiveType::Variant type)
{
	return str += type;
}

std::ostream& operator<<(std::ostream& os, PrimitiveType::Variant type)
{
	if (type >= PrimitiveType::Variant::Max) {
		os.setstate(std::ios_base::failbit);
		return os;
	}
	return os << ("" + type);
}

} //namespace AST
