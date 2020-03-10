#pragma once

#include <optional>

namespace AST {

enum class ConstExprType {
	Bool,
	Num,
	Unknown,
};

class ConstExpr {
public:
	ConstExprType type = ConstExprType::Unknown;
	long long int numVal = 0;
	bool boolVal = false;

	bool isKnown();
	bool isFalse();
	bool isTrue();
	std::optional<long long int> getNum();
};
  
	// true == maybe
	// false == no
class StaticAnalysisCtx {
public:
  bool in;
  bool out;
  
  bool hasError;
};

}
