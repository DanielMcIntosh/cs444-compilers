#pragma once

#include "scanParse.h"

namespace Parser
{
struct Grammar;

void parseTokens(std::vector<Scan::LexToken> const& tokens, Grammar const& grammar);

} //namespace Parser
