#include "codegen.h"

#include <variant>

using namespace std;

namespace CodeGen {

class CodeGen {
};

class SConstant {
public:
	string name;
	variant<string, int> constant;
};

class SText {
public:
	SText();

	string toString();

	void addRaw(const string& str);

	void section(const string &name);
	void addExternSymbol(const vector<string> &symbol);
	void declGlobalAndBegin(const string &name);
	void addConstant(const string &name, const string &constant);
	void addConstant(const string &name, int constant);

private:

	int curIndent;
	vector<string> lines;
	vector<string> declaredGlobals;
	vector<SConstant> constants;

	void addStr(const string &str);

	string indent();
};

string SText::indent() {
	string res;
	for (int i = 0; i < curIndent; ++i) {
		res += ' ';
	}
	return res;
}

void SText::addExternSymbol(const vector <string> &symbol) {
	int oldIndent = curIndent;
	curIndent = 0;
	for (const auto &sym : symbol) {
		strdecl512(text, "extern %s", sym.c_str());
		addStr(text);
	}
	curIndent = oldIndent;
}

void SText::declGlobalAndBegin(const string &name) {
	curIndent = 4;
	strdecl512(text, "global %s", name.c_str());
	addStr(text);
	curIndent = 0;
	snprintf(text, ARRAY_SIZE(text), "%s:", name.c_str());
	addStr(text);
	curIndent = 4;
}

SText::SText() : curIndent(0) {
}

void SText::addStr(const string &str) {
	lines.push_back(indent() + str);
}

void SText::section(const string &name) {
	int oldIndent = curIndent;
	curIndent = 0;
	strdecl512(text, "section .%s", name.c_str());
	addStr(text);
	curIndent = oldIndent;
}

string SText::toString() {
	section("data");
	for (const auto& constant : constants) {
		visit(visitor{
			[&] (const string& str) {
				int oldIndent = curIndent;
				curIndent = 4;
				strdecl512(text , "%s: dd '%s'", constant.name.c_str(), str.c_str());
				addStr(text);
				snprintf(text, ARRAY_SIZE(text), "%sLen equ $ - %s - 1",
								 constant.name.c_str(), constant.name.c_str());
				addStr(text);
				curIndent = oldIndent;
			},
			[&] (int num) {

			}
			}, constant.constant);
	}

	string res;
	for (const auto &line : lines) {
		res.append(line);
		res.append("\n");
	}

	return res;
}

void SText::addConstant(const string &name, const string &constant) {
	constants.push_back(SConstant{name, constant});
}

void SText::addConstant(const string &name, int constant) {
	constants.push_back(SConstant{name, constant});
}

void SText::addRaw(const string &str) {
	lines.push_back(str);
}

}  // namespace CodeGen

using namespace CodeGen;

BackendResult doBackend(const MiddleendResult &middleend) {

	vector<string> runtimeSymbols;
	runtimeSymbols.push_back("__malloc");
	runtimeSymbols.push_back("__debexit");
	runtimeSymbols.push_back("__exception");
	runtimeSymbols.push_back("NATIVEjava.io.OutputStream.nativeWrite");

	SText s;
	s.addExternSymbol(runtimeSymbols);
	s.addConstant("hello", "Hello from ASM!");

	s.section("text");
	s.declGlobalAndBegin("_start");

	s.addRaw( R"(
mov ebx, 0
mov ecx, helloLen
loop:
cmp ebx, ecx
je loopOut
mov edx, hello
mov eax, [edx + ebx]
push ebx
push ecx
call NATIVEjava.io.OutputStream.nativeWrite
pop ecx
pop ebx
add ebx, 1
jmp loop
loopOut:
mov eax, 123
call __debexit
	 )");

	BackendResult result;
	result.sFiles.push_back(SFile{"stub.s", s.toString()});
	return result;
}
