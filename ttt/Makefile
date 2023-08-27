# Define the compiler
CXX = g++

# Define the compiler flags
CXXFLAGS = -Wall -std=c++11

# Define the object files
OBJS = tic_tac_toe.o functions.o

# Define the executable name
EXEC = ttt.exe

# The default target
all: $(EXEC)

# Linking the object files to produce the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

# Compiling main.cpp
tic_tac_toe.o: tic_tac_toe.cpp functions.h
	$(CXX) $(CXXFLAGS) -c tic_tac_toe.cpp

# Compiling functions.cpp
functions.o: functions.cpp functions.h
	$(CXX) $(CXXFLAGS) -c functions.cpp

# Clean target to remove object files and the executable
clean:
	rm -f $(OBJS) $(EXEC)
