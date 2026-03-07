# Makefile for Incidence Graph project
# Matches: g++ main.cpp incidence_lists.cpp adjacency_matrix.cpp -o main

# Compiler
CXX = g++

# Compiler flags (add -std=c++17 since you're using modern C++)
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Source files
SOURCES = main.cpp incidence_lists.cpp adjacency_matrix.cpp

# Output executable
TARGET = main

# Default target
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

# generated files
GENERATED = \
    testGraph.txt testGraph2.txt \
    testMatrix.txt testMatrix2.txt \
    copytest1.txt copytest2.txt copytest3.txt \
    moved.txt moved2.txt movedempty.txt movedempty2.txt \


# Files that should NEVER be deleted (your input/test data)
PROTECTED = test.txt

# Clean up
clean:
	rm -f $(TARGET) $(GENERATED)
	@echo "✅ Removed executable and generated files"
	@echo "🔒 Protected files kept: $(PROTECTED)"

# Run the program
run: $(TARGET)
	./$(TARGET)

# Run with valgrind to check for memory leaks
memcheck: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

# Rebuild everything
rebuild: clean $(TARGET)

.PHONY: clean run memcheck rebuild