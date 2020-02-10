#include "ast/primitiveType.h"
#include "ast/type.h"
#include "parse/parseTree.h"

namespace AST
{

const std::map<std::string, PrimitiveType::Variant> PrimitiveType::valueLookup {
	{"boolean", Variant::Boolean},
	{"byte", Variant::Byte},
	{"short", Variant::Short},
	{"int", Variant::Int},
	{"char", Variant::Char}
};

// static
std::unique_ptr<PrimitiveType> PrimitiveType::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (ptNode->oneNt)
	{
		return PrimitiveType::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::PrimitiveType:
		return std::make_unique<PrimitiveType>(static_cast<const Parse::TPrimitiveType*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for PrimitiveType: " + std::to_string((int)ptNode->type));
	}
}
PrimitiveType::PrimitiveType(const Parse::TPrimitiveType *ptNode)
{
	ptNode->v;
	//val = valueLookup.at(children[0].lexeme);
}

} //namespace AST
