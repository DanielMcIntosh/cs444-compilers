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

SRC_DIRS := ./src
SRCS := $(shell find $(SRC_DIRS) -name *.cpp)

OBJS_DEBUG := $(SRCS:%=$(BUILD_DIR_DEBUG)/%.o)
OBJS_RELEASE := $(SRCS:%=$(BUILD_DIR_RELEASE)/%.o)

DEPS_DEBUG := $(OBJS_DEBUG:.o=.d)
DEPS_RELEASE := $(OBJS_RELEASE:.o=.d)

CXX := g++-9

ifeq ($(shell echo $$GITLAB_CI),true)
CXX := g++
endif

ifeq ($(OS),Windows_NT)
CXX := g++
endif

WARNINGS = -Wall -Wextra -Wformat=2 -Wcast-align -Wcast-qual -Wdisabled-optimization \
  -Winit-self -Wlogical-op -Wmissing-include-dirs -Wredundant-decls \
	-Wshadow -Wundef -Wno-variadic-macros -Wstrict-aliasing=3 -Wwrite-strings \
  -Wfloat-conversion -Wsuggest-attribute=pure -Wsuggest-attribute=const \
  -Wsuggest-attribute=noreturn -Wsuggest-attribute=format -Wnull-dereference \
  -Wzero-as-null-pointer-constant -Wctor-dtor-privacy -Wnon-virtual-dtor \
  -Woverloaded-virtual -Wno-unused-parameter -Wfatal-errors

EXTRA_CXXFLAGS += $(WARNINGS) -D__USE_MINGW_ANSI_STDIO -MMD -MP -std=c++17 -I$(SRC_DIRS)

joosc: $(OBJS_RELEASE)
	$(CXX) $(OBJS_RELEASE) -o $@ $(LDFLAGS) $(LDFLAGS_RELEASE) $(WARNINGS)

fast:
	$(MAKE) joosc -j12

joosc_debug: $(OBJS_DEBUG)
	$(CXX) $(OBJS_DEBUG) -o $@ $(LDFLAGS) $(LDFLAGS_DEBUG) $(WARNINGS)

$(BUILD_DIR_RELEASE)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CXXFLAGS_RELEASE) $(EXTRA_CXXFLAGS)  -c $< -o $@

$(BUILD_DIR_DEBUG)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CXXFLAGS_DEBUG) $(EXTRA_CXXFLAGS)  -c $< -o $@

.PHONY: clean header a1 a1Direct marmoset

clean:
	$(RM) -r $(BUILD_DIR_RELEASE)
	$(RM) -r $(BUILD_DIR_DEBUG)
	$(RM) joosc
	$(RM) joosc_debug

header: joosc_debug
	export JOOSC_PARSER=1; ./joosc_debug  

a1:
	$(MAKE) a1Direct -j12

a1Direct: joosc_debug
	export JOOSC_TEST=TEST; export JOOSC_TEST_ASSN=1; ./joosc_debug

marmoset:
	/u/cs_build/bin/marmoset_submit --username=-ddmcinto-q5an-whkuan- \
	--zipargs=-r cs444 A1Code ./src ./Makefile ./joos.lr1 ./joos.txt 

-include $(DEPS_DEBUG)
-include $(DEPS_RELEASE)

MKDIR_P ?= mkdir -p
