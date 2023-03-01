CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11
SRC = xkcdpwgen.cpp
OBJ = $(SRC:.cpp=.o)
EXECUTABLE = xkcdpwgen

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CXX) $(OBJ) -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)