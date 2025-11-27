MAKEFLAGS += --no-print-directory

TARGET = Vulkan

CXX = clang++

CXX_FLAGS = -g -std=c++20 -O2 -Wall -Wextra -Wpedantic -DDEBUG -MMD -MP

BUILD_DIR = ./build/
INCLUDE = -I./headers

OBJ_DIR = $(BUILD_DIR)obj/
SRC_DIR = ./src/

SRC = $(shell find $(SRC_DIR) -name '*.cpp')
OBJ = $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRC))

BIN = $(BUILD_DIR)$(TARGET)
CCJSON = $(BUILD_DIR)compile_commands.json

LIBS = -lvulkan -lSDL3 -lfmt

$(BUILD_DIR):
	@mkdir -p $@

$(OBJ_DIR) :
	@mkdir -p $@

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp $(OBJ_DIR)
	@echo "CC: $@"
	@mkdir -p $(dir $@)
	@$(CXX) $(CXX_FLAGS) -c $< -o $@ $(INCLUDE)

-include $(OBJ:.o=.d)

$(TARGET) : $(BUILD_DIR)
	@bear --output $(CCJSON) -- $(MAKE) $(BIN)

$(BIN) : $(OBJ)
	@echo "LD: $@"
	@$(CXX) $(CXX_FLAGS) $(OBJ) -o $@ $(LIBS) 
	
clean : 
	@rm -rf $(BUILD_DIR)

cleanLogs :
	@rm -rf $(BUILD_DIR)logs
