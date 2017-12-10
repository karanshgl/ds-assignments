CC = g++

CPP = $(wildcard *.cpp)
OBJS = $(CPP:.cpp=.o)
HEADER = $(wildcard *.h)

default: output

%.o: %.cpp 
	$(CC) -c -o $@ $< 

output: $(OBJS) $(HEADER)
	$(CC) $^ -o $@

clean:
	-rm -f $(OBJS) output