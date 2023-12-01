CXX         := clang++-17
CXXFLAGS    := -std=c++20 -stdlib=libstdc++ -pedantic -Wall -Wextra -Werror
SRC_DIR     := src
INCLUDE_DIR := include
BUILD_DIR   := build
BIN_DIR     := bin
EXECUTABLES := $(patsubst $(SRC_DIR)/%.cpp,%,$(wildcard $(SRC_DIR)/day*.cpp))
UTILS       := io.hpp
SRC_FILES   := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(INCLUDE_DIR)/*.hpp) $(UTILS)
OBJ_FILES   := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

$(EXECUTABLES): % : $(BIN_DIR)/%
	./$(BIN_DIR)/$@

$(BIN_DIR)/%: $(BUILD_DIR)/%.o
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(wildcard $(BUILD_DIR)/*) $(wildcard $(BIN_DIR)/*)
