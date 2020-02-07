#pragma once

#include <memory>
#include <vector>

namespace Parser
{
	struct ASTToken;
}

namespace AST
{

class Node
{
public:
	virtual ~Node() = default;
};

}
