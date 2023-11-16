# A line starting with a has is a comment, we'll build up
# the below example

TARGET = fp
SRC_FILES = main.cpp Board.cpp

# NO EDITS NEEDED BELOW THIS LINE

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic-errors
CXXFLAGS_DEBUG = -g
CXXVERSION = -std=c++17

OBJECTS = $(SRC_FILES:.cpp=.o)

ifeq ($(shell echo "Windows"), "Windows")
	TARGET := $(TARGET).exe
	DEL = del
else
	DEL = rm
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^

.cpp.o:
	$(CXX) $(CXXFLAGS) $(CXXVERSION) $(CXXFLAGS_DEBUG) -o $@ -c $<

clean:
	$(DEL) -f $(TARGET) $(OBJECTS) Makefile.bak

depend:
	@sed -i.bak '/^# DEPENDENCIES/,$$d' Makefile
	@$(DEL) -f sed*
	@echo "# DEPENDENCIES" >> Makefile
	@$(CXX) -MM $(SRC_FILES) >> Makefile

.PHONY: all clean depend

# DEPENDENCIES
main.o: main.cpp
