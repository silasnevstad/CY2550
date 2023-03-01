CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11
SRC = xkcdpwgen.cpp
OBJ = $(SRC:.cpp=.o)
EXECUTABLE = xkcdpwgen

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

xkcdpwgen.o: xkcdpwgen.cpp
# usage: xkcdpwgen.py [-h] [-w WORDS] [-c CAPS] [-n NUMBERS] [-s SYMBOLS]
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)