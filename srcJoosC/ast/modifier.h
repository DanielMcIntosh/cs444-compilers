#pragma once

#include "ast/node.h"
#include <map>

namespace AST
{

class Modifier: public Node
{
public:
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

	static std::unique_ptr<Modifier> create(const Parse::Tree *ptNode);
	static std::unique_ptr<Modifier> create(Variant mod);
	explicit Modifier(const Parse::TModifier *ptNode);
	explicit Modifier(Variant mod);

	std::string toCode() const override;
};

std::string operator+(std::string str, Modifier::Variant type);
std::string operator+=(std::string& str, Modifier::Variant type);
std::ostream& operator<<(std::ostream& os, Modifier::Variant type);

} //namespace AST
