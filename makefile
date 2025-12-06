CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./include
LDFLAGS = -lncurses

SRC = src/main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = stock_terminal

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm $(OBJ) $(TARGET)

.PHONY: all clean