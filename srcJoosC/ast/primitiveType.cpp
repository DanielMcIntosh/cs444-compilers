#include "ast/primitiveType.h"
#include "ast/type.h"
#include "parse/parseTree.h"
#include "semantic/semantic.h"
#include <ostream>

namespace AST
{

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

std::string PrimitiveType::toCode() const
{
	return "" + type;
}

bool PrimitiveType::equals(PrimitiveType *other) {
  return type == other->type;
}

bool PrimitiveType::equals(NameType *other) {
  return false;
}

bool PrimitiveType::equals(Type *other) {
  return false;
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

Semantic::SemanticErrorType PrimitiveType::resolve(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	return Semantic::SemanticErrorType::None;
}

} //namespace AST
