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

LDFLAGS := -fno-rtti
LDFLAGS_RELEASE := -O3 -flto -s
LDFLAGS_DEBUG := -g

ifneq ($(OS),Windows_NT)
CXXFLAGS_DEBUG += -fsanitize=address
LDFLAGS_DEBUG += -lasan -rdynamic
endif

BUILD_DIR_DEBUG := ./build/debug
BUILD_DIR_RELEASE := ./build/release

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

EXTRA_CXXFLAGS += $(WARNINGS)

# Target : JoosC

JOOSC_SRC_DIRS := ./srcJoosC
JOOSC_SRCS := $(shell find $(JOOSC_SRC_DIRS) -name *.cpp)

JOOSC_OBJS_DEBUG := $(JOOSC_SRCS:%=$(BUILD_DIR_DEBUG)/%.o)
JOOSC_OBJS_RELEASE := $(JOOSC_SRCS:%=$(BUILD_DIR_RELEASE)/%.o)

JOOSC_DEPS_DEBUG := $(JOOSC_OBJS_DEBUG:.o=.d)
JOOSC_DEPS_RELEASE := $(JOOSC_OBJS_RELEASE:.o=.d)

# Target : PTGen

PTGEN_SRC_DIRS := ./srcPTGen
PTGEN_SRCS := $(shell find $(PTGEN_SRC_DIRS) -name *.cpp)
PTGEN_OBJS := $(PTGEN_SRCS:%=$(BUILD_DIR_DEBUG)/%.o)
PTGEN_DEPS := $(PTGEN_OBJS:.o=.d)

# Target list

## joosc

joosc: $(JOOSC_OBJS_RELEASE)
	$(CXX) $(JOOSC_OBJS_RELEASE) -o $@ $(LDFLAGS) $(LDFLAGS_RELEASE) $(WARNINGS)

joosc_debug: $(JOOSC_OBJS_DEBUG)
	$(CXX) $(JOOSC_OBJS_DEBUG) -o $@ $(LDFLAGS) $(LDFLAGS_DEBUG) $(WARNINGS)

## ptgen

ptgen: $(PTGEN_OBJS)
	$(CXX) $(PTGEN_OBJS) -o $@ $(LDFLAGS) $(LDFLAGS_DEBUG) $(WARNINGS)

# Object files

$(BUILD_DIR_RELEASE)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_RELEASE) $(EXTRA_CXXFLAGS) -I$(JOOSC_SRC_DIRS) -c $< -o $@

$(BUILD_DIR_DEBUG)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_DEBUG) $(EXTRA_CXXFLAGS) -I$(JOOSC_SRC_DIRS) -c $< -o $@

# Pseudo target

.PHONY: clean a1 a1Direct a2 a2Direct marmoset

clean:
	$(RM) -r $(BUILD_DIR_RELEASE)
	$(RM) -r $(BUILD_DIR_DEBUG)
	$(RM) joosc
	$(RM) joosc_debug
	$(RM) ptgen

a1:
	$(MAKE) a1Direct -j$(NPROC)

a1Direct: joosc_debug
	export JOOSC_TEST=TEST; export JOOSC_TEST_ASSN=1; ./joosc_debug

a2:
	$(MAKE) a2Direct -j$(NPROC)

a2Direct: joosc_debug
	export JOOSC_TEST=TEST; export JOOSC_TEST_ASSN=2; ./joosc_debug

a3:
	$(MAKE) a3Direct -j$(NPROC)

a3Direct: joosc_debug
	export JOOSC_TEST=TEST; export JOOSC_TEST_ASSN=3; ./joosc_debug

a6:
	$(MAKE) a6Direct -j$(NPROC)

a6Direct: joosc_debug
	export JOOSC_TEST=TEST; export JOOSC_TEST_ASSN=6; ./joosc_debug

marmoset:
	/u/cs_build/bin/marmoset_submit --username=-ddmcinto-q5an-whkuan- \
	--zipargs=-r cs444 A1Code ./src ./Makefile ./joos.lr1 ./joos.txt

-include $(JOOSC_DEPS_DEBUG)
-include $(JOOSC_DEPS_RELEASE)

MKDIR_P ?= mkdir -p
