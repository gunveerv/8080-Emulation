CXX = g++
CXXFLAGS = -std=c++11
SRC = src/main.cpp src/disassembler.cpp
OBJ = $(SRC:.cpp=.o)  
OUT = 8080.out

all: $(OUT) cleanObj

$(OUT): $(OBJ)
	$(CXX) $^ -o $@

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -f $(OBJ) $(OUT)

cleanObj:
	rm -f $(OBJ)

