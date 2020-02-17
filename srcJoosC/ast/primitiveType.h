#pragma once

#include "ast/type.h"
#include <map>

namespace AST
{

class PrimitiveType: public Type
{
public:
    enum class Variant
    {
        Boolean,
        Byte,
        Short,
        Int,
        Char,
        Void,
        Max
    } type;

    static std::unique_ptr<PrimitiveType> create(const Parse::Tree *ptNode);
	explicit PrimitiveType(const Parse::TPrimitiveType *ptNode);
    // void type - see note in Type::create
    explicit PrimitiveType(nullptr_t null);

	std::string toCode() override;
};

std::string operator+(std::string str, PrimitiveType::Variant type);
std::string operator+=(std::string& str, PrimitiveType::Variant type);
std::ostream& operator<<(std::ostream& os, PrimitiveType::Variant type);

} //namespace AST
