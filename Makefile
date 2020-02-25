# Common configurations

NPROC := 4

ifneq ($(OS),Windows_NT)
UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		NPROC := $(shell grep -c ^processor /proc/cpuinfo)
	endif
endif

CXXFLAGS := -fno-rtti -D__USE_MINGW_ANSI_STDIO -MMD -MP -std=c++17
CXXFLAGS_RELEASE := -O3 -flto -s
CXXFLAGS_DEBUG := -g

LDFLAGS := -fno-rtti -pthread
LDFLAGS_RELEASE := -O3 -flto -s
LDFLAGS_DEBUG := -g

ifneq ($(OS),Windows_NT)
CXXFLAGS_DEBUG += -fsanitize=address
LDFLAGS_DEBUG += -lasan -rdynamic
endif

BUILD_DIR_DEBUG := ./build/debug
BUILD_DIR_RELEASE := ./build/release
BUILD_DIR_SHARED := ./build/shared

GLOBAL_WARNINGS := -Wall -Wextra -Wformat=2 -Wcast-align -Wcast-qual -Wdisabled-optimization \
  -Winit-self -Wmissing-include-dirs -Wredundant-decls -Wshadow -Wundef -Wno-variadic-macros \
  -Wwrite-strings -Wfloat-conversion -Wnull-dereference -Wzero-as-null-pointer-constant \
  -Wctor-dtor-privacy -Wnon-virtual-dtor -Woverloaded-virtual -Wno-unused-parameter -Wfatal-errors

GCC_WARNINGS := -Wlogical-op -Wstrict-aliasing=3 -Wsuggest-attribute=pure -Wsuggest-attribute=const \
  -Wsuggest-attribute=noreturn -Wsuggest-attribute=format

CLANG_WARNINGS := -fcolor-diagnostics

CXX := g++-9

ifeq ($(shell echo $$GITLAB_CI),true)
CXX := g++
endif

ifeq ($(OS),Windows_NT)
CXX := clang
LDFLAGS += -lstdc++
endif

ifeq ($(CXX),clang)
WARNINGS := $(GLOBAL_WARNINGS) $(CLANG_WARNINGS)
else
WARNINGS := $(GLOBAL_WARNINGS) $(GCC_WARNINGS)
endif

# Target : JoosC

JOOSC_SRC_DIRS := ./srcJoosC
JOOSC_SRCS := ./srcJoosC/main.cpp ./srcJoosC/semantic/scope.cpp ./srcJoosC/semantic/semantic.cpp \
./srcJoosC/ast/compilationUnit.cpp ./srcJoosC/ast/conditionalStatement.cpp \
./srcJoosC/ast/constructorDeclaration.cpp ./srcJoosC/ast/expression.cpp \
./srcJoosC/ast/fieldDeclaration.cpp ./srcJoosC/ast/importDeclaration.cpp \
./srcJoosC/ast/memberDeclaration.cpp \
./srcJoosC/ast/methodDeclaration.cpp ./srcJoosC/ast/modifier.cpp \
./srcJoosC/ast/name.cpp ./srcJoosC/ast/node.cpp \
./srcJoosC/ast/statement.cpp ./srcJoosC/ast/typeDeclaration.cpp \
./srcJoosC/ast/type.cpp ./srcJoosC/ast/variableDeclaration.cpp \
./srcJoosC/ast/nodeList.cpp

JOOSC_OBJS_DEBUG := $(JOOSC_SRCS:%=$(BUILD_DIR_DEBUG)/%.o)
JOOSC_OBJS_RELEASE := $(JOOSC_SRCS:%=$(BUILD_DIR_RELEASE)/%.o)

JOOSC_DEPS_DEBUG := $(JOOSC_OBJS_DEBUG:.o=.d)
JOOSC_DEPS_RELEASE := $(JOOSC_OBJS_RELEASE:.o=.d)

# Target : PTGen

PTGEN_SRC_DIRS := ./srcPTGen
PTGEN_SRCS := $(shell find $(PTGEN_SRC_DIRS) -name *.cpp)
PTGEN_OBJS := $(PTGEN_SRCS:%=$(BUILD_DIR_DEBUG)/%.o)
PTGEN_DEPS := $(PTGEN_OBJS:.o=.d)

# Target : Shared

SHARED_SRCS := ./srcJoosC/weeder.cpp ./srcJoosC/utility.cpp	./srcJoosC/scanner.cpp \
./srcJoosC/profiler.cpp ./srcJoosC/platform.cpp ./srcJoosC/frontend.cpp \
./srcJoosC/parse/parser.cpp ./srcJoosC/parse/parseTreeBase.cpp \
./srcJoosC/parse/parseTreeImpl.cpp ./srcJoosC/parse/parseTree.cpp \
./srcJoosC/ast/methodDeclarator.cpp ./srcJoosC/ast/methodHeader.cpp \
./srcJoosC/ast/typeBody.cpp ./srcJoosC/ast/variableDeclarator.cpp \
./srcJoosC/ast/ast.cpp ./srcJoosC/semantic/dagSort.cpp

SHARED_OBJS := $(SHARED_SRCS:%=$(BUILD_DIR_SHARED)/%.o)
SHARED_DEPS := $(SHARED_OBJS:.o=.d)

# Target list

## joosc

joosc_release: libjc.so $(JOOSC_OBJS_RELEASE)
	$(CXX) $(JOOSC_OBJS_RELEASE) -o $@ $(LDFLAGS) $(LDFLAGS_RELEASE) -L./ -ljc $(WARNINGS)

joosc_debug: libjc.so $(JOOSC_OBJS_DEBUG)
	$(CXX) $(JOOSC_OBJS_DEBUG) -o $@ $(LDFLAGS) $(LDFLAGS_DEBUG) -L./ -ljc $(WARNINGS)

## ptgen

ptgen: $(PTGEN_OBJS)
	$(CXX) $(PTGEN_OBJS) -o $@ $(LDFLAGS) $(LDFLAGS_DEBUG) $(WARNINGS)

# shared

libjc.so: $(SHARED_OBJS)
	$(CXX) $(SHARED_OBJS) -shared -fvisibility=hidden -fno-exceptions -s -fPIC -O3 -flto -o $@

# Object files

$(BUILD_DIR_SHARED)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CXXFLAGS) -O3 -fPIC -fvisibility=hidden -fno-exceptions $(WARNINGS) -I$(JOOSC_SRC_DIRS) -c $< -o $@

$(BUILD_DIR_RELEASE)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_RELEASE) $(WARNINGS) -I$(JOOSC_SRC_DIRS) -c $< -o $@

$(BUILD_DIR_DEBUG)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_DEBUG) $(WARNINGS) -I$(JOOSC_SRC_DIRS) -c $< -o $@

# Pseudo target

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR_RELEASE)
	$(RM) -r $(BUILD_DIR_DEBUG)
	$(RM) -r $(BUILD_DIR_SHARED)
	$(RM) joosc_release
	$(RM) joosc_debug
	$(RM) libjc.so
	$(RM) ptgen

a1: joosc_debug
	export LD_LIBRARY_PATH=./:$LD_LIBRARY_PATH;	export JOOSC_TEST=TEST; export JOOSC_TEST_ASSN=1; ./joosc_debug

a2:
	$(MAKE) a2Direct -j$(NPROC)

a2Direct: joosc_debug
	export LD_LIBRARY_PATH=./:$LD_LIBRARY_PATH;	export JOOSC_TEST=TEST; export JOOSC_TEST_ASSN=2; ./joosc_debug

a3:
	$(MAKE) a3Direct -j$(NPROC)

a3Direct: joosc_debug
	export LD_LIBRARY_PATH=./:$LD_LIBRARY_PATH;	export JOOSC_TEST=TEST; export JOOSC_TEST_ASSN=3; ./joosc_debug

a6:
	$(MAKE) a6Direct -j$(NPROC)

a6Direct: joosc_debug
	export LD_LIBRARY_PATH=./:$LD_LIBRARY_PATH;	export JOOSC_TEST=TEST; export JOOSC_TEST_ASSN=6; ./joosc_debug

marmoset:
	/u/cs_build/bin/marmoset_submit --username=-ddmcinto-q5an-whkuan- \
	--zipargs=-r cs444 A2Code ./srcJoosC ./srcPTGen ./Makefile ./joos.lr1 ./joos.txt ./joosc

-include $(JOOSC_DEPS_DEBUG)
-include $(JOOSC_DEPS_RELEASE)
-include $(SHARED_DEPS)

MKDIR_P ?= mkdir -p
