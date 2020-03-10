#include "staticAnalysis.h"

#include "ast/expression.h"
#include "ast/conditionalStatement.h"

namespace AST {

//////////////////////////////////////////////////////////////////////////////
//
// tryEval
//
//////////////////////////////////////////////////////////////////////////////

	bool ConstExpr::isKnown() {
		return type != ConstExprType::Unknown;
	}


	bool ConstExpr::isFalse() {
		return isKnown() && !boolVal;
	}


	bool ConstExpr::isTrue() {
		return isKnown() && boolVal;
	}

	std::optional<long long int> ConstExpr::getNum() {
		if (type != ConstExprType::Num)
			return std::nullopt;
		return numVal;
	}

	ConstExpr Expression::tryEval() {
		return ConstExpr();
	}

ConstExpr BinaryExpression::tryEval() {
	if (op == Variant::InstanceOf)
		return ConstExpr();

	auto left = lhs->tryEval();
	auto right = std::get<0>(rhs)->tryEval();

	if (left.type != right.type || left.type == ConstExprType::Unknown)
		return ConstExpr();

	if (left.type == ConstExprType::Bool) {
		if (op == Variant::Eq) {
			return ConstExpr{ConstExprType::Bool, 0, left.boolVal == right.boolVal};
		}
		if (op == Variant::NEq) {
			return ConstExpr{ConstExprType::Bool, 0, left.boolVal != right.boolVal};
		}
		if (op == Variant::LazyOr) {
			return ConstExpr{ConstExprType::Bool, 0, left.boolVal || right.boolVal};
		}
		if (op == Variant::LazyAnd) {
			return ConstExpr{ConstExprType::Bool, 0, left.boolVal && right.boolVal};
		}
		return ConstExpr();
	}

	if (left.type == ConstExprType::Num) {
		switch (op) {
			case Variant::Add:
				return ConstExpr{ConstExprType::Num, left.numVal + right.numVal};
			case Variant::Mult:
				return ConstExpr{ConstExprType::Num, left.numVal * right.numVal};
		case Variant::Eq:
			return ConstExpr{ConstExprType::Bool, 0, left.numVal == right.numVal};
		case Variant::NEq:
			return ConstExpr{ConstExprType::Bool, 0, left.numVal != right.numVal};
    default:
      return ConstExpr();
		}
	}

	return ConstExpr();
}

ConstExpr Literal::tryEval() {
	return std::visit(visitor{
					[&](unsigned int val) { return ConstExpr{ConstExprType::Num, val, false}; },
					[&](bool val) { return ConstExpr{ConstExprType::Bool, 0, val}; },
					[&](char val) { return ConstExpr{ConstExprType::Num, val, false}; },
					[&](std::string &val) { return ConstExpr{ConstExprType::Unknown, 0, false}; },
					[&](std::nullptr_t val) { return ConstExpr{ConstExprType::Unknown, 0, false}; },
	}, value);
}


//////////////////////////////////////////////////////////////////////////////
//
// staticAnalysis
//
//////////////////////////////////////////////////////////////////////////////

	void Statement::staticAnalysis(StaticAnalysisCtx *ctx) {
		if (!ctx->in)
			ctx->hasError = true;
		ctx->out = ctx->in;
	}

	void Block::staticAnalysis(StaticAnalysisCtx *ctx) {
		if (!ctx->in) {
			ctx->hasError = true;
			return;
		}
		for (auto &stmt : statements) {
			if (!ctx->in) {
				ctx->hasError = true;
				return;
			}
			stmt->staticAnalysis(ctx);
			ctx->in = ctx->out;
		}
		ctx->out = ctx->in;
	}

	void ReturnStatement::staticAnalysis(StaticAnalysisCtx *ctx) {
		if (!ctx->in)
			ctx->hasError = true;
		ctx->out = false;
	}


//////////////////////////////////////////////////////////////////////////////
//
// staticAnalysis
//
//////////////////////////////////////////////////////////////////////////////

	void ConditionalStatement::staticAnalysis(StaticAnalysisCtx *ctx) {
		if (!ctx->in) {
			ctx->hasError = true;
		}
		switch (condType) {
		case ConditionType::If: {
			if (!elseBody) {
				bool inL = ctx->in;
				body->staticAnalysis(ctx);
				ctx->out = ctx->out || inL;
			} else {
				auto nCtx1 = *ctx;
				body->staticAnalysis(&nCtx1);
				auto nCtx2 = *ctx;
				elseBody->staticAnalysis(&nCtx2);
				ctx->out = nCtx1.out || nCtx2.out;
				ctx->hasError |= nCtx1.hasError || nCtx2.hasError;
			}
			break;
		}
		case ConditionType::While: {
			auto expr = condition->tryEval();
			if (expr.isTrue()) {
				body->staticAnalysis(ctx);
				ctx->out = false;
				break;
			}

			if (expr.isFalse()) {
				auto nCtx = *ctx;
				nCtx.in = false;
				body->staticAnalysis(&nCtx);
				ctx->out = ctx->in;
				ctx->hasError |= nCtx.hasError;
				break;
			}

			bool inL = ctx->in;
			body->staticAnalysis(ctx);
			ctx->out = inL;
			break;
		}
		case ConditionType::For: {
			if (!condition) {
				body->staticAnalysis(ctx);
				ctx->out = false;
				break;
			}

			auto expr = condition->tryEval();
			if (expr.isFalse()) {
				auto nCtx = *ctx;
				nCtx.in = false;
				body->staticAnalysis(&nCtx);
				ctx->out = ctx->in;
				ctx->hasError |= nCtx.hasError;
				break;
			}

			if (expr.isTrue()) {
				body->staticAnalysis(ctx);
				ctx->out = false;
				break;
			}

			bool inL = ctx->in;
			body->staticAnalysis(ctx);
			ctx->out = inL;
			break;
		}
		default:
			ASSERT(false);
			break;
		}
	}  

} // namespace AST
