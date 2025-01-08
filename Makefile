#Compiler and flags
CXX=g++
CXXFLAGS= -Wall -Wextra -std=c++17

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Target executable
TARGET = program

# Default target
all: $(TARGET)

# Link object files to create the final executable
$(TARGET): $(OBJS)
	@echo "Linking and producing the final application"
	$(CXX) $(OBJS) -o $@

# Compile each .cpp file into a .o file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
