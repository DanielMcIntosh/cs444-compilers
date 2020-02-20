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

void Type::resolve(TypeDeclaration *decl)
{
	assert(declaration == nullptr);
	declaration = decl;
}

} //namespace AST
