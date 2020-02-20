#pragma once

#include <memory>
#include <vector>
#include "parse/parseTreeBase.h"

namespace AST
{

class Node
{
public:
	static std::unique_ptr<Node> create(const Parse::Tree *ptNode);
	virtual ~Node() = default;

	[[gnu::pure]]
	static bool isSingleton(const Parse::Tree *ptNode);

	virtual std::string toCode() const = 0;
};

}
