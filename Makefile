CXX = g++
LFLAGS = 
CXXFLAGS = -std=c++11 -Wall

INCLUDES = -I./includes

SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build
APP_NAME = hyperborea

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

TARGET = $(BUILD_DIR)/$(APP_NAME)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(LFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR)/* $(BUILD_DIR)/*

.PHONY: clean