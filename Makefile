CXX      := -g++
#CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror -std=c++11
CXXFLAGS := -Wall
LDFLAGS  := -L/usr/local/lib/ -lrtaudio -lmidifile 
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
TARGET   := program
INCLUDE  := -Iinclude/ -Iexternal/rtaudio/ -Iexternal/midifile/include/
SRC      :=                      \
   $(wildcard tests/test.cpp)    \
   $(wildcard src/*.cpp)         \

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS) $(INCLUDE) $(LDFLAGS) 

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
