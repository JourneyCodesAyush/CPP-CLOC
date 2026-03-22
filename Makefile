# Compiler and flags
CC = g++ 
CFLAGS = -Wall -g -std=c++17
RELEASE_FLAGS = -O3

# Default build = debug
BUILD_FLAGS = $(CFLAGS)

# If RELEASE=1 → use optimized flags
ifeq ($(RELEASE),1)
    BUILD_FLAGS = -Wall -std=c++17 $(RELEASE_FLAGS)
endif

# Source and header directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = makeBuild

# Source and header files
SRC = $(wildcard $(SRC_DIR)/*.cpp)
HDR = $(wildcard $(INC_DIR)/*.hpp)

# Object files in build directory
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))

# Executable
ifeq ($(OS),Windows_NT)
    TARGET = cloc_cpp.exe
	RUNTESTS = run_tests.exe
else
    TARGET = cloc_cpp
	RUNTESTS = ./run_tests
endif

# Ensure build directory exists
$(shell mkdir -p $(BUILD_DIR) 2> NUL)

# Build the executable
$(TARGET): $(OBJ)
	$(CC) $(BUILD_FLAGS) -I$(INC_DIR) -o $(TARGET) $(OBJ)

# Compile .cpp to .o and track headers
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HDR)
	$(CC) $(BUILD_FLAGS) -I$(INC_DIR) -c $< -o $@
	
# Precompiled Catch2 object
CATCH_OBJ = $(BUILD_DIR)/catch2.o

$(CATCH_OBJ): tests/catch_main.cpp $(INC_DIR)/catch2/catch.hpp
	$(CC) $(BUILD_FLAGS) -I$(INC_DIR) -c tests/catch_main.cpp -o $(CATCH_OBJ)

# Test sources
TEST_SRC = src/analyzer.cpp src/string_operation_strip.cpp
TESTS = $(filter-out tests/catch_main.cpp, $(wildcard tests/*.cpp))

test: $(CATCH_OBJ)
	$(CC) $(BUILD_FLAGS) -I$(INC_DIR) $(TEST_SRC) $(TESTS) $(CATCH_OBJ) -o run_tests
	$(RUNTESTS)

# Clean build files
clean:
ifeq ($(OS),Windows_NT)
	del /Q $(BUILD_DIR)\*.o 2> NUL || true
	del /Q $(TARGET) 2> NUL || true
	del /Q $(RUNTESTS) 2> NUL || true
else
	rm -f $(BUILD_DIR)/*.o
	rm -f $(TARGET)
	rm -f $(RUNTESTS)
endif
