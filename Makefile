CC = g++
CFLAGS = -Wall -Wextra  -std=c++17

SRCS = $(wildcard *.cpp) $(wildcard blossom/*.cpp) $(wildcard blossom/MinCost/*.cpp)	
OBJS = $(SRCS:.cpp=.o)
EXEC = TSP_algorithms

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)