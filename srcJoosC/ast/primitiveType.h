#pragma once

#include "ast/type.h"

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
    explicit PrimitiveType(std::nullptr_t null);

    Semantic::SemanticErrorType resolve(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass) override;

    virtual bool equals(PrimitiveType *) override;
    virtual bool equals(NameType *) override;
    virtual bool equals(Type *) override;
	std::string toCode() const override;
};

std::string operator+(std::string str, PrimitiveType::Variant type);
std::string operator+=(std::string& str, PrimitiveType::Variant type);
std::ostream& operator<<(std::ostream& os, PrimitiveType::Variant type);

} //namespace AST
