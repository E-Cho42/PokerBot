# COMMENTS BEGIN WITH A HASH

# THE NAME OF YOUR EXECUTABLE
TARGET = Final_Project
# ALL CPP COMPILABLE IMPLEMENTATION FILES THAT MAKE UP THE PROJECT
SRC_FILES = main.cpp hand.cpp

# NO EDITS NEEDED BELOW THIS LINE

CXX = g++
CPPVERSION = -std=c++17

OBJECTS = $(SRC_FILES:.cpp=.o)

ifeq ($(shell echo "Windows"), "Windows")
	TARGET := $(TARGET).exe
	DEL = del
else
	DEL = rm -f
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^

.cpp.o:
	$(CXX) $(CPPVERSION) -o $@ -c $<

clean:
	$(DEL) $(TARGET) $(OBJECTS)

.PHONY: all clean

main.o: main.cpp hand.h
hand.o: hand.cpp hand.h List.hpp Array.hpp 
