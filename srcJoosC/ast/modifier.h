#pragma once

#include "ast/node.h"
#include <map>

namespace AST
{

class Modifier: public Node
{
public:
	static std::unique_ptr<Modifier> create(const Parse::Tree *ptNode);
	explicit Modifier(const Parse::TModifier *ptNode);

	enum class Variant
	{
		Public,
		Protected,
		Static,
		Abstract,
		Final,
		Native,
		Max
	} type;

	std::string toCode() const override;
};

std::string operator+(std::string str, Modifier::Variant type);
std::string operator+=(std::string& str, Modifier::Variant type);
std::ostream& operator<<(std::ostream& os, Modifier::Variant type);

} //namespace AST
