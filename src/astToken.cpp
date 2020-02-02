#include "astToken.h"

namespace Parser {

ASTToken::ASTToken(Symbol s, std::vector<ASTToken>& children): sym(s)
{
	if (children.size() == 1)
	{
		//astNode = std::move(children[0].astNode);
		return;
	}
	//TODO
}

ASTToken::ASTToken(TermSymbol s, std::string lexeme)
{

}

} //namespace Parser
