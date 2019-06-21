CXX       := g++
CXXFLAGS  := -pedantic-errors -Wall -Wextra -Werror -std=c++14 -fopenmp -pthread
LDFLAGS   := -L/usr/local/lib/ -lrtaudio -lmidifile 
# Target directories
BUILD_DIR := build
OBJ_DIR   := $(BUILD_DIR)/.objects
TEST_DIR  := $(BUILD_DIR)/tests
LIB_DIR   := $(BUILD_DIR)/lib
LIB_NAME  := libtsal
# Source directories
SRC       := src
TEST      := tests
INCLUDE   := -Iinclude/ -Iexternal/rtaudio/ -Iexternal/midifile/include/


# Generated variables
SRC_FILES  := $(notdir $(wildcard $(SRC)/*.cpp))
TEST_FILES := $(notdir $(wildcard $(TEST)/*.cpp))

TESTS	     := $(TEST_FILES:%.cpp=$(TEST_DIR)/%)
OBJECTS    := $(SRC_FILES:%.cpp=$(OBJ_DIR)/%.o)


all: test tsal

$(OBJ_DIR)/%.o: $(SRC)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -fPIC -o $@ -c $< $(INCLUDE)

.PHONY: all clean debug release docs test

test: $(OBJECTS) $(TESTS)

tsal: $(OBJECTS)
	@mkdir -p $(LIB_DIR)
	$(CXX) -shared -o $(LIB_DIR)/$(LIB_NAME).so $?
	@ar -r $(LIB_DIR)/$(LIB_NAME).a $?

$(TEST_DIR)/%: $(TEST)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ $< $(OBJECTS) $(INCLUDE) $(LDFLAGS)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(TEST_DIR)/*

docs:
	@doxygen Doxyfile
