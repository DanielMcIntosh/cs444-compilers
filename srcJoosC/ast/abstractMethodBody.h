#pragma once

#include "ast/statement.h"
#include <memory>

namespace AST
{

// mostly a dummy class
class AbstractMethodBody: public Statement
{
public:
	static std::unique_ptr<AbstractMethodBody> create(const Parse::Tree *ptNode);
	explicit AbstractMethodBody(const Parse::TAbstractMethodBody *ptNode);

	std::string toCode() override;
};

} //namespace AST
