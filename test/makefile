BUILD_DIR=build
SOURCE_DIRS=base formatting std

OS=$(shell uname -s)
ifeq ($(OS),Linux)
	LD_FLAGS += -Wl,--whole-archive
	LD_FLAGS_END += -Wl,--no-whole-archive
endif
ifeq ($(OS),Darwin)
	LD_FLAGS += -all_load
endif

CXX_FLAGS += -std=c++17 -I ../include -I catch -I helpers -Werror -Wall -Wextra -Wpedantic

.PHONY: all clean

all: test

$(BUILD_DIR):
	mkdir $@

define BUILD_RULES
$(1)_OBJECTS=$$(patsubst %.cpp,$(BUILD_DIR)/%.o,$$(wildcard $(1)/*.cpp))

$(BUILD_DIR)/$(1):
	mkdir -p $$@

$(BUILD_DIR)/$(1)/%.o: $(1)/%.cpp $(BUILD_DIR)/$(1)
	$(CXX) $(CXX_FLAGS) -c -o $$@ $$<

$(BUILD_DIR)/$(1).a: $(BUILD_DIR) $$($(1)_OBJECTS)
	ar crs $$@ $$($(1)_OBJECTS)
endef

$(foreach srcdir,$(SOURCE_DIRS),$(eval $(call BUILD_RULES,$(srcdir))))

test: $(patsubst %,$(BUILD_DIR)/%.a,$(SOURCE_DIRS))
	$(CXX) $(LD_FLAGS) -o $@ $^ $(LD_FLAGS_END)

clean:
	rm -rf $(BUILD_DIR)
	rm -f test
