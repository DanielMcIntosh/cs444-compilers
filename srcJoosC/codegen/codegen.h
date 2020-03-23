#pragma once

#include <string>
#include <variant>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "middleend.h"
#include "semantic/scope.h"

BackendResult doBackend(const MiddleendResult& middleend);

namespace AST {
class MemberDeclaration;
}

namespace CodeGen {

//////////////////////////////////////////////////////////////
//
// object layout.
// these are multiple of 4 bytes
//
/////////////////////////////////////////////////////////////
#define OBJECT_CLASS 0 // pointer to type info (a.k.a class)
#define OBJECT_ISARRAY 1
#define OBJECT_FIELD 2 // beginning of list of fields

//////////////////////////////////////////////////////////////
//
// array layout.
// array itself is an object, with length being the first field
// followed by variable length array after it
//
/////////////////////////////////////////////////////////////
#define ARRAY_LENGTH_OFFSET 2
#define ARRAY_DATA_OFFSET 3

//////////////////////////////////////////////////////////////
//
// Class (a.k.a type info) layout
//
/////////////////////////////////////////////////////////////
#define CLASS_TAG 0 // arbitrary number
// A table of size M (number of all methods (interface, abstract class, concrete, etc..)
// with implementation filled in at some positions
// (basically all methods that a method is overriding or implementing
// (need to follow the chain))
// Handles both interface and virtual method dispatch in O(1)
// not optimized at all but is very easy to get going
// not used by static methods
#define CLASS_SELECTOR 1

// A table of size C (number of all interfaces and classes) right after selector table
// To perform O(1) subclass testing that is used for instanceOf and assignment, etc..
//#define CLASS_SUBCLASS 1+M

class SConstant {
public:
	std::string name;
	std::variant<std::string, int> constant;
};

class SText {
public:
	std::string toString();

	void add(const std::string& str);
	[[gnu::format(printf, 2, 3)]] void addf(const char *fmt, ...);
	[[gnu::format(printf, 2, 3)]] void call(const char *fmt, ...);

	void addExternSymbol(const std::string& str);
	void addExternSymbol(const std::vector<std::string> &symbol);
	void declGlobalAndBegin(const std::string &name);
	void addConstant(const std::string &name, const std::string &constant);
	void addConstant(const std::string &name, unsigned int constant);

private:
	std::vector<std::string> lines;
	std::unordered_set<std::string> externalLabels;
	std::unordered_set<std::string> declaredGlobals;
	std::vector<SConstant> constants;
};

struct MethodInfo {
	int tableIndex;
	AST::MethodDeclaration *declaration;

	MethodInfo(int index, AST::MethodDeclaration *decl);
};

class SContext {
public:
	std::vector<std::unique_ptr<MethodInfo>> methodTable;
	std::unordered_map<std::string, MethodInfo*> methodSelector;

	bool lastExprLValue = false;
	SText text;
	std::string typeName;
	Semantic::Scope *scope = nullptr;
	int counter = 0;

	void pushScope(Semantic::Scope *newScope);
	void popScope();

private:
	std::vector<Semantic::Scope *> scopeStack;
};

std::string getProcedureName(const AST::MemberDeclaration *theMember);
}  // namespace CodeGen
