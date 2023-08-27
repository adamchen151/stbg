# Define the compiler
CXX = g++

# Define the compiler flags
CXXFLAGS = -Wall -std=c++11

# Define the object files
OBJS = main.o move.o functions.o ai.o

# Define the executable name
EXEC = chess.exe

# The default target
all: $(EXEC)

# Linking the object files to produce the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

# Compiling main.cpp
main.o: main.cpp move.h functions.h ai.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compiling move.cpp
move.o: move.cpp move.h functions.h ai.h
	$(CXX) $(CXXFLAGS) -c move.cpp

# Compiling functions.cpp
functions.o: functions.cpp move.h functions.h ai.h
	$(CXX) $(CXXFLAGS) -c functions.cpp

# Compiling ai.cpp
ai.o: ai.cpp move.h functions.h ai.h
	$(CXX) $(CXXFLAGS) -c ai.cpp

# Clean target to remove object files and the executable
clean:
	rm -f $(OBJS) $(EXEC)
