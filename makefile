CXX = g++
CXXFLAGS = -std=c++23 -Wall -I./include
LDFLAGS = -static-libstdc++ -static-libgcc
TARGET = stock_terminal

# List all source files in src/ directory
SRC = $(wildcard src/*.cpp)
# Convert to object files in src/ directory
OBJ = $(SRC:src/%.cpp=src/%.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $(TARGET)

# Rule for compiling .cpp files in src/ directory
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean