CXX = g++
LFLAGS =
CXXFLAGS = -std=c++20 -Wall

INCLUDES = -I./include -I./libremidi/include
LIBRARIES = libremidi/build/liblibremidi.a

SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build
APP_NAME = hyperborea

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

TARGET = $(BUILD_DIR)/$(APP_NAME)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBRARIES) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR)/* $(BUILD_DIR)/*

.PHONY: clean