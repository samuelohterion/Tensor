CXX      := g++
CXXFLAGS := -std=c++20 -O2 -Wall -Wextra
TARGET   := main

SOURCES  := main.cpp src/idx.cpp
OBJECTS  := $(SOURCES:.cpp=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)