#pragma once

#include "ast/primary.h"
#include <memory>
#include <string>

namespace AST
{

class FieldAccess: public Primary
{
public:
	FieldAccess(std::vector<Parser::ASTToken>& children);

	std::shared_ptr<Primary> object;
	std::string member;
};

} //namespace AST
