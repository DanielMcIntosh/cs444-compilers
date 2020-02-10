#include "ast/ast.h"
#include "ast/node.h"
#include "frontend.h"
#include <fstream>

namespace AST {

void astDumpDebugInfo(ASTResult const& result, const char *baseOutputPath)
{
	if (!result.ast)
	{
		return;
	}
	std::string astOutputPath(baseOutputPath);
	astOutputPath += ".ast.txt";
	std::ofstream ostrm(astOutputPath);
	ostrm << result.ast->toCode();
}

ASTResult buildAST(const Parse::Tree *root)
{
	if (root == nullptr)
	{
		return ASTResult{nullptr};
	}
	auto ast = std::shared_ptr<Node>(Node::create(root));
	assert(ast);
	return {ast};
}

} // namespace AST
