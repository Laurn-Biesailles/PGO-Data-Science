# Default Compiler
CXX=g++

# Source files to run
SRC=main.cc dataset.cc condition.cc analysis.cc
OBJ=$(SRC:.cc=.o)
TARGET=titanic

# Standard compiler warnings and C++ version
CXXFLAGS=-std=c++17 -Wall

# Normal build
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX)	$(CXXFLAGS) -o $(TARGET)	$(OBJ)

%.o: %.cc
	$(CXX)	$(CXXFLAGS)	-c	$< -o $@

# Build in optimized way
opt:
	$(CXX)	$(SRC) -O3 -o $(TARGET)

# LTO (link-time-optimization)
lto:
	$(CXX)	$(SRC)	-O3 -flto -o $(TARGET)

# GCOV (for code coverage)
gcov:
	$(CXX) $(SRC) -fprofile-arcs -ftest-coverage -o $(TARGET)

#PGO generate
pgo-gen:
	$(CXX)	$(SRC) -fprofile-generate -O3 -o $(TARGET)

#PGO use
pgo-use:
	$(CXX) $(SRC) -fprofile-use -O3 -Wno-coverage-mismatch -o $(TARGET)

#Perfing
perfing:
	$(CXX) $(SRC) -g -O3 -fno-omit-frame-pointer

# Remove executable, object files, and coverage output
clean:
	rm -f $(OBJ) $(TARGET)
	rm -f *.gcda *.gcno *gcov
