# Compiler
CXX = g++

CXXFLAGS = -std=c++17 -Wall -lpthread


SRC_FILES = simpleOS.cpp operations.cpp

# Target file (executable file name)
TARGET = simpleOS

# Build rule
all: $(TARGET)


$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC_FILES)

# run the program
run: all
	./$(TARGET)

# Clean up the intermediate files and executable
clean:
	rm -f $(TARGET)
