CC = g++

CPP = $(wildcard *.cpp)
OBJS = $(CPP:.cpp=.o)

default: output

%.o: %.cpp 
	$(CC) -c -o $@ $< 

output: $(OBJS)
	$(CC) $^ -o $@

.PHONY: clean
clean:
	-rm -f $(OBJS) output