CXX      = g++
CXXFLAGS = -O2 -march=rv64gv
NAME     = microbench
SRCS     = main.cpp

all: build run

build:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)

run: 
	./$(NAME)

clean:
	rm -f $(NAME)