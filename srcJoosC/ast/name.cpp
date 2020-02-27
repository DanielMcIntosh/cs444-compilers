#include "ast/name.h"
#include "ast/expression.h"
#include "ast/type.h"
#include "ast/typeDeclaration.h"
#include "parse/parseTree.h"
#include "semantic/semantic.h"
#include "semantic/scope.h"

#include <memory>
#include <vector>

using Semantic::SemanticErrorType;

namespace AST
{

// static
std::unique_ptr<Name> Name::create(const Parse::Tree *ptNode)
{
	if (ptNode == nullptr) {
		return nullptr;
	}
	if (isSingleton(ptNode))
	{
		return Name::create(ptNode->children[0]);
	}
	switch(ptNode->type) {
	case Parse::NonTerminalType::Name:
		return std::make_unique<Name>(static_cast<const Parse::TName*>(ptNode));
	default:
		FAILED("inappropriate PT type for Name: " + std::to_string((int)ptNode->type));
	}
}

Name::Name(const Parse::TName *ptNode)
{
	nodeType = NodeType::Name;
	if (ptNode->name)
	{
		Name pre = Name(ptNode->name);
		ids = std::move(pre.ids);
	}
	ids.push_back(ptNode->identifier->value);
}

Name::Name(std::vector<std::string> idList)
  :	ids(std::move(idList))
{
	assert(!ids.empty());
	nodeType = NodeType::Name;
}

std::string Name::flatten() const
{
	std::string str;
	for (auto &id : ids)
	{
		str += id + ".";
	}
	// pop off the trailing "."
	str.pop_back();
	return str;
}

std::string Name::toCode() const
{
	return flatten();
}

std::string Name::getId() const
{
	return ids.back();
}

bool Name::operator==(const Name &other) {
	return ids == other.ids;
}

// pre-compute typePrefix in case expression-resolution reaches rule 3 and has to resolve a_1.a_2. ... a_k to a Type
SemanticErrorType Name::resolveTypes(Semantic::SemanticDB const& semantic, TypeDeclaration *enclosingClass)
{
	std::vector<std::string> curPrefix;
	for (unsigned int i = 0; i < ids.size(); ++i)
	{
		curPrefix.push_back(ids[i]);
		// leverage NameType's type resolution
		auto temp = std::make_unique<NameType>(Name(curPrefix));
		if (temp->resolve(semantic, enclosingClass) == SemanticErrorType::None)
		{
			buildConverted(std::move(temp), i+1);
			return SemanticErrorType::None;
		}
	}

	// even if we fail to resolve a type prefix, we can't return an error, because we might still be a valid expression
	return SemanticErrorType::None;
}

SemanticErrorType Name::disambiguate(Semantic::Scope const& scope)
{
	// resolve to local variable
	{
		auto local = std::make_unique<LocalVariableExpression>(ids[0]);
		if (local->resolve(scope) == SemanticErrorType::None)
		{
			buildConverted(std::move(local), 1);
			return SemanticErrorType::None;
		}
	}

	// resolve to field access
	// in the process, we're going to make any implicit "this" or TypeName explicit
	{
		// if we're in a non-static method, resolve(this) will succeed.
		if (auto thisExpr = std::make_unique<LocalVariableExpression>("this");
			thisExpr->resolve(scope) == SemanticErrorType::None)
		{
			// attempt construct a FieldAccess using the implicit "this"
			auto field = std::make_unique<FieldAccess>(std::move(thisExpr), ids[0]);
			if (field->resolve(scope) == SemanticErrorType::None)
			{
				buildConverted(std::move(field), 1);
				return SemanticErrorType::None;
			}
		}
		else
		{
			// attempt to construct a field access using the implicit TypeName
			auto field = std::make_unique<FieldAccess>(scope._enclosingClass->asType(), ids[0]);
			if (field->resolve(scope) == SemanticErrorType::None)
			{
				buildConverted(std::move(field), 1);
				return SemanticErrorType::None;
			}
		}
	}

	// since we pre-computed during type resolution the result of rule3 of namespace disambiguation,
	// converted should already be non-null. If it is null, that means rule3 failed.
	return std::visit([](auto &expr){ return expr == nullptr; }, converted) ? SemanticErrorType::ExprResolution : SemanticErrorType::None;
}

void Name::buildConverted(std::unique_ptr<Expression> expr, unsigned int idStart)
{
	for (unsigned int i = idStart; i < ids.size(); ++i)
	{
		expr = std::make_unique<FieldAccess>(std::move(expr), ids[i]);
	}
	converted = std::move(expr);
}
void Name::buildConverted(std::unique_ptr<NameType> type, unsigned int idStart)
{
	if (idStart >= ids.size())
	{
		converted = std::move(type);
	} else
	{
		buildConverted(std::make_unique<FieldAccess>(std::move(type), ids[idStart]), idStart+1);
	}
}


} //namespace AST
