PERF := debug

ifeq ($(PERF), release)
	CXXFLAGS += -O3
	LDFLAGS += -flto -s
  EXEC := joosc
else
  ifneq ($(OS),Windows_NT)
    CXXFLAGS += -g -fsanitize=address
		LDFLAGS += -g -lasan
	endif
	EXEC := joosc_debug
endif

BUILD_DIR := ./build/$(PERF)
SRC_DIRS := ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CXX := g++

WARNINGS = -Wall -Wextra -Wformat=2 -Wcast-align -Wcast-qual -Wdisabled-optimization \
  -Winit-self -Wlogical-op -Wmissing-include-dirs -Wredundant-decls \
	-Wshadow -Wundef -Wno-variadic-macros -Wstrict-aliasing=3 -Wwrite-strings \
  -Wfloat-conversion -Wsuggest-attribute=pure -Wsuggest-attribute=const \
  -Wsuggest-attribute=noreturn -Wsuggest-attribute=format -Wnull-dereference

CXXFLAGS += $(INC_FLAGS) $(WARNINGS) -D__USE_MINGW_ANSI_STDIO -MMD -MP -march=native

ifneq ($(OS),Windows_NT)
	LDFLAGS += -rdynamic
endif

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean a1 a2 a3 a4 a5 scanner scanner_joos

clean:
	$(RM) -r $(BUILD_DIR)

a1: $(EXEC)
	export JOOSC_TEST=test; export JOOSC_TEST_ASSN=1; ./$(EXEC)
a2: $(EXEC)
	export JOOSC_TEST=test; export JOOSC_TEST_ASSN=2; ./$(EXEC)
a3: $(EXEC)
	export JOOSC_TEST=test; export JOOSC_TEST_ASSN=3; ./$(EXEC)
a4: $(EXEC)
	export JOOSC_TEST=test; export JOOSC_TEST_ASSN=4; ./$(EXEC)
a5: $(EXEC)
	export JOOSC_TEST=test; export JOOSC_TEST_ASSN=5; ./$(EXEC)
scanner: $(EXEC)
	export JOOSC_SCANNER=1; ./$(EXEC)
scanner_joos: $(EXEC)
	export JOOSC_SCANNER=1; export JOOSC_SCANNER_FILE=joos.txt; ./$(EXEC)

-include $(DEPS)

MKDIR_P ?= mkdir -p
