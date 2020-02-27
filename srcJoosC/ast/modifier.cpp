#include "ast/modifier.h"
#include "ast/node.h"
#include "parse/parseTree.h"
#include <ostream>

namespace AST
{

// static
std::unique_ptr<Modifier> Modifier::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::Modifier:
		return std::make_unique<Modifier>(static_cast<const Parse::TModifier*>(ptNode));
	default:
		FAILED("inappropriate PT type for Modifier: " + std::to_string((int)ptNode->type));
	}
}

std::unique_ptr<Modifier> Modifier::create(Variant mod) {
	return std::make_unique<Modifier>(mod);
}

static_assert( (int)Parse::TModifierV::Public   	== (int)Modifier::Variant::Public);
static_assert( (int)Parse::TModifierV::Protected	== (int)Modifier::Variant::Protected);
static_assert( (int)Parse::TModifierV::Static   	== (int)Modifier::Variant::Static);
static_assert( (int)Parse::TModifierV::abstract 	== (int)Modifier::Variant::Abstract);
static_assert( (int)Parse::TModifierV::final    	== (int)Modifier::Variant::Final);
static_assert( (int)Parse::TModifierV::native   	== (int)Modifier::Variant::Native);

Modifier::Modifier(const Parse::TModifier *ptNode)
  : type{(int)ptNode->v}
{
	nodeType = NodeType::Modifier;
	assert(type <= Variant::Max);
}

Modifier::Modifier(Variant mod) : type(mod) {}

std::string Modifier::toCode() const
{
	return "" + type;
}

std::string operator+=(std::string& str, Modifier::Variant type)
{
    switch(type)
    {
		case Modifier::Variant::Public:   	return str += "public";
		case Modifier::Variant::Protected:	return str += "protected";
		case Modifier::Variant::Static:   	return str += "static";
		case Modifier::Variant::Abstract: 	return str += "abstract";
		case Modifier::Variant::Final:    	return str += "final";
		case Modifier::Variant::Native:   	return str += "native";
		case Modifier::Variant::Max:		;// fallthrough
		// no default to trigger compiler warning on missing case
    }
    FAILED("String conversion on invalid modifier type: " + std::to_string((int)type));
}
std::string operator+(std::string str, Modifier::Variant type)
{
	return str += type;
}

std::ostream& operator<<(std::ostream& os, Modifier::Variant type)
{
	if (type >= Modifier::Variant::Max) {
		os.setstate(std::ios_base::failbit);
		return os;
	}
	return os << ("" + type);
}

} //namespace AST
