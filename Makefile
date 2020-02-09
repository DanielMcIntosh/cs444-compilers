# Common configurations

CXXFLAGS_RELEASE := -O3 -flto -s 
CXXFLAGS_DEBUG := -g

LDFLAGS_RELEASE := -O3 -flto -s 
LDFLAGS_DEBUG := -g
LDFLAGS := -lstdc++fs

ifneq ($(OS),Windows_NT)
CXXFLAGS_DEBUG += -fsanitize=address
LDFLAGS_DEBUG += -lasan -rdynamic
endif

BUILD_DIR_DEBUG := ./build/debug
BUILD_DIR_RELEASE := ./build/release

WARNINGS = -Wall -Wextra -Wformat=2 -Wcast-align -Wcast-qual -Wdisabled-optimization \
  -Winit-self -Wlogical-op -Wmissing-include-dirs -Wredundant-decls \
	-Wshadow -Wundef -Wno-variadic-macros -Wstrict-aliasing=3 -Wwrite-strings \
  -Wfloat-conversion -Wsuggest-attribute=pure -Wsuggest-attribute=const \
  -Wsuggest-attribute=noreturn -Wsuggest-attribute=format -Wnull-dereference \
  -Wzero-as-null-pointer-constant -Wctor-dtor-privacy -Wnon-virtual-dtor \
  -Woverloaded-virtual -Wno-unused-parameter -Wfatal-errors

EXTRA_CXXFLAGS += $(WARNINGS) -D__USE_MINGW_ANSI_STDIO -MMD -MP -std=c++17 

CXX := g++-9

ifeq ($(shell echo $$GITLAB_CI),true)
CXX := g++
endif

ifeq ($(OS),Windows_NT)
CXX := g++
endif

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
	$(CXX) $(CXXFLAGS_RELEASE) $(EXTRA_CXXFLAGS)  -c $< -o $@

$(BUILD_DIR_DEBUG)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CXXFLAGS_DEBUG) $(EXTRA_CXXFLAGS)  -c $< -o $@

# Pseudo target

.PHONY: clean a1 a1Direct marmoset

clean:
	$(RM) -r $(BUILD_DIR_RELEASE)
	$(RM) -r $(BUILD_DIR_DEBUG)
	$(RM) joosc
	$(RM) joosc_debug
	$(RM) ptgen

a1:
	$(MAKE) a1Direct -j12

a1Direct: joosc_debug
	export JOOSC_TEST=TEST; export JOOSC_TEST_ASSN=1; ./joosc_debug

marmoset:
	/u/cs_build/bin/marmoset_submit --username=-ddmcinto-q5an-whkuan- \
	--zipargs=-r cs444 A1Code ./src ./Makefile ./joos.lr1 ./joos.txt 

-include $(JOOSC_DEPS_DEBUG)
-include $(JOOSC_DEPS_RELEASE)

MKDIR_P ?= mkdir -p
