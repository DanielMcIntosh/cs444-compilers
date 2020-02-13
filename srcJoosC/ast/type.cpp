#include "ast/type.h"
#include "ast/primitiveType.h"
#include "ast/name.h"
#include "parse/parseTreeBase.h"
#include <memory>

namespace AST
{

// static
std::unique_ptr<Type> Type::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (ptNode->oneNt)
	{
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
			return std::make_unique<NameType>(std::move(*Name::create(ptNode)));
		default:
			throw std::runtime_error("inappropriate PT type for Type: " + std::to_string((int)ptNode->type));
	}
}

} //namespace AST
