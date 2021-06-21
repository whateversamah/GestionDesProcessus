CXX = g++
DEPS = fifo.h sjf.h RR.h MQ.h
OBJ = main.o
WIN = del
NIX = rm -f

ProcessScheduling: $(OBJ) $(DEPS)
	$(CXX) $(OBJ) -o ProcessScheduling

%.o: %.cpp
	$(CXX) -c $<

.PHONY: clean

clean:
	$(NIX)  $(OBJ)



