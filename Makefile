EXEC ?= joosc

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

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

CPPFLAGS ?= $(INC_FLAGS) $(WARNINGS) -MMD -MP -g
ifeq ($(OS),Windows_NT)
	LDFLAGS += -g
else
	LDFLAGS += -g -rdynamic
endif

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean a1 a2 a3 a4 a5 scanner

clean:
	$(RM) -r $(BUILD_DIR)

a1: $(EXEC)
	export JOOSC_MODE=test; export JOOSC_ASSN=1; ./$(EXEC)
a2: $(EXEC)
	export JOOSC_MODE=test; export JOOSC_ASSN=2; ./$(EXEC)
a3: $(EXEC)
	export JOOSC_MODE=test; export JOOSC_ASSN=3; ./$(EXEC)
a4: $(EXEC)
	export JOOSC_MODE=test; export JOOSC_ASSN=4; ./$(EXEC)
a5: $(EXEC)
	export JOOSC_MODE=test; export JOOSC_ASSN=5; ./$(EXEC)
scanner: $(EXEC)
	export JOOSC_MODE=scanner; ./$(EXEC)


-include $(DEPS)

MKDIR_P ?= mkdir -p
