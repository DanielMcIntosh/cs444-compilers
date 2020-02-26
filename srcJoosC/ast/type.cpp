#include "ast/type.h"
#include "ast/name.h"
#include "parse/parseTree.h"
#include "semantic/semantic.h"
#include <memory>
#include <ostream>

namespace AST
{

//////////////////////////////////////////////////////////////////////////////
//
// resolve
//
//////////////////////////////////////////////////////////////////////////////

Semantic::SemanticErrorType NameType::resolve(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	auto [typeDecl, err] = semantic.resolveType(this, enclosingClass);
	declaration = typeDecl;
	return err;
}

Semantic::SemanticErrorType PrimitiveType::resolve(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	return Semantic::SemanticErrorType::None;
}

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
	: prefix(std::move(other.prefix)),
	  id(std::move(other.id))
{
}
NameType::NameType(Name const& other)
	: prefix(other.prefix),
	  id(other.id)
{
}

std::string NameType::flatten() const {
	std::string str;
	for (auto &pre : prefix)
	{
		str += pre + ".";
	}
	str += id;
	return str;
}

bool NameType::equals(NameType *other) {
	return declaration == other->declaration;
}

TypeDeclaration *NameType::getDeclaration()
{
	return declaration;
}



static_assert( (int)Parse::TPrimitiveTypeV::boolean	== (int)PrimitiveType::Variant::Boolean);
static_assert( (int)Parse::TPrimitiveTypeV::byte   	== (int)PrimitiveType::Variant::Byte);
static_assert( (int)Parse::TPrimitiveTypeV::Short  	== (int)PrimitiveType::Variant::Short);
static_assert( (int)Parse::TPrimitiveTypeV::Int    	== (int)PrimitiveType::Variant::Int);
static_assert( (int)Parse::TPrimitiveTypeV::Char   	== (int)PrimitiveType::Variant::Char);
PrimitiveType::PrimitiveType(const Parse::TPrimitiveType *ptNode)
	: type{(int)ptNode->v}
{
	assert(type <= Variant::Max && type != Variant::Void);
}
PrimitiveType::PrimitiveType(std::nullptr_t null)
	: type(Variant::Void)
{
}

bool PrimitiveType::equals(PrimitiveType *other) {
	return type == other->type;
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

bool Type::equals(PrimitiveType *) {
	return false;
}

bool Type::equals(NameType *) {
	return false;
}

bool Type::equals(Type *) {
	return false;
}

} //namespace AST
