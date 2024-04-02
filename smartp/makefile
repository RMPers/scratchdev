CXX := g++
# Compiler flags
CXXFLAGS := -std=c++20 -Wall -Wextra

# Source files
SRCS := main.cpp
# Object files
OBJS := $(SRCS:.cpp=.o)
# Executable name
EXEC := smart

# Install directory prefix
PREFIX := /usr/local

.PHONY: all clean install

# Default target
all: $(EXEC)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to link object files into executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to install the executable
install: $(EXEC)
	install -d $(DESTDIR)$(PREFIX)/bin
	install -m 755 $(EXEC) $(DESTDIR)$(PREFIX)/bin/$(EXEC)

# Rule to clean up object files and executable
clean:
	$(RM) $(OBJS) $(EXEC)
