
#include "ast/modifier.h"
#include "ast/node.h"
#include "parse/parseTree.h"

namespace AST
{

const std::map<std::string, Modifier::Value> Modifier::modTypeLookup{
	{"public", Modifier::Value::Public},
	{"protected", Modifier::Value::Protected},
	{"static", Modifier::Value::Static},
	{"abstract", Modifier::Value::Abstract},
	{"final", Modifier::Value::Final},
	{"native", Modifier::Value::Native}
};

// static
std::unique_ptr<Modifier> Modifier::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (ptNode->oneNt)
	{
		return Modifier::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::Modifier:
		return std::make_unique<Modifier>(static_cast<const Parse::TModifier*>(ptNode));
	default:
		throw std::runtime_error("inapropriate PT type for Modifier: " + std::to_string((int)ptNode->type));
	}
}
Modifier::Modifier(const Parse::TModifier *ptNode)
{
	//modType = modTypeLookup.at(children[0].lexeme);
}


} //namespace AST
