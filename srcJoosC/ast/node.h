#pragma once

#include <memory>
#include <vector>
#include "parse/parserForwardDecl.h"

namespace AST
{

class Node
{
public:
	static std::unique_ptr<Node> create(const Parse::Tree *ptNode);
	virtual ~Node() = default;

	virtual std::string toCode() = 0;
};

}
