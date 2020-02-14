#include "ast/literal.h"
#include "parse/parseTree.h"

namespace AST
{

// static
std::unique_ptr<Literal> Literal::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (ptNode->oneNt)
	{
		return Literal::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::Literal:
		return std::make_unique<Literal>(static_cast<const Parse::TLiteral*>(ptNode));
	default:
		throw std::runtime_error("inappropriate PT type for Literal: " + std::to_string((int)ptNode->type));
	}
}
Literal::Literal(const Parse::TLiteral *ptNode)
{
    switch (ptNode->v) {
        case Parse::TLiteralV::IntegerLiteral:
            value = static_cast<unsigned int>(ptNode->integerLiteral->value);
            break;
        case Parse::TLiteralV::BooleanLiteral:
            value = static_cast<bool>(ptNode->booleanLiteral->value);
            break;
        case Parse::TLiteralV::CharacterLiteral:
            value = static_cast<char>(ptNode->characterLiteral->value);
            break;
        case Parse::TLiteralV::StringLiteral:
            value = ptNode->stringLiteral->value;
            break;
        case Parse::TLiteralV::NullLiteral:
            value = null{};
            break;
        default:
            ASSERT(false);
    }
}
std::string Literal::toCode() {
    return std::visit(visitor {
        [](unsigned int x) { return std::to_string(x); },
        [](bool x) -> std::string { return x ? "true" : "false"; },
        [](char x) { return std::string(1, x); },
        [](std::string x) { return x; },
        [](null) -> std::string { return "null"; }
    }, value);
}

} //namespace AST
