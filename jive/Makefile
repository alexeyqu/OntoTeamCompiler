SHELL = /bin/sh

# path #
SRC_PATH = src
BUILD_PATH = obj
BIN_PATH = bin
AUTO_PATH = auto

# executable # 
BIN_NAME = jive

# extensions #
SRC_EXT = cpp

# code lists #
# Find all source files in the source directory, sorted by
# most recently modified
SOURCES = $(shell find $(SRC_PATH) -name '*.$(SRC_EXT)' | sort -k 1nr | cut -f2-)
# Set the object file names, with the source directory stripped
# from the path, and the build path prepended in its place
OBJECTS = $(BUILD_PATH)/jive.tab.o $(BUILD_PATH)/jive.yy.o $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)  
# Set the dependency files that will be used to add header dependencies
DEPS = $(OBJECTS:.o=.d)

CC = g++-4.8

# flags #
CFLAGS = --std=c++11 -O -g -fsanitize=address -fno-omit-frame-pointer -MD
INCLUDES = -I $(AUTO_PATH) -I include -I include/AST \
	-I include/AST/TreeNodes -I include/AST/TreeNodes/Expressions -I include/AST/TreeNodes/Statements -I include/AST/TreeNodes/Entities \
	-I include/AST/TreeVisitors -I include/ST \
	-I /usr/local/include
LIBS = -lasan -lfl

.PHONY: default_target
default_target: release

.PHONY: release
release: export CFLAGS := $(CFLAGS) $(COMPILE_FLAGS)
release: dirs
	@$(MAKE) all

.PHONY: dirs
dirs:
	@echo "Creating directories"
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BIN_PATH)
	@mkdir -p $(AUTO_PATH)

.PHONY: clean
clean:
	@echo "Deleting $(BIN_NAME) symlink"
	@$(RM) $(BIN_NAME)
	@echo "Deleting directories"
	@$(RM) -r $(BUILD_PATH)
	@$(RM) -r $(BIN_PATH)
	@$(RM) -r $(AUTO_PATH)
	rm -f include/jive.*.* src/jive.yy. jive jive_asan *.ps

# checks the executable and symlinks to the output
.PHONY: all
all: $(BIN_PATH)/$(BIN_NAME)
	@echo "Making symlink: $(BIN_NAME) -> $<"
	@$(RM) $(BIN_NAME)
	@ln -s $(BIN_PATH)/$(BIN_NAME) $(BIN_NAME)

$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	@echo "Linking: $@"
	$(CC) $^ $(LIBS) -o $@

# Add dependency files, if they exist
-include $(DEPS)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	$(CC) $(CFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@

obj/jive.yy.o: src/jive.lex
	flex --header-file=$(AUTO_PATH)/jive.lex.h -o $(AUTO_PATH)/jive.yy.c src/jive.lex 
	$(CC) $(CFLAGS) $(INCLUDES) -c $(AUTO_PATH)/jive.yy.c -o $(BUILD_PATH)/jive.yy.o

obj/jive.tab.o: src/jive.y
	bison -d -v -o $(AUTO_PATH)/jive.tab.c src/jive.y
	$(CC) $(CFLAGS) $(INCLUDES) -c $(AUTO_PATH)/jive.tab.c -o $(BUILD_PATH)/jive.tab.o
