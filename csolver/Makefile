OBJS = 	json.o \
		block_allocator.o \
		Timer.o \
		solver_stats.o \
		utils.o \
		csp_reader.o \
		backtrack_solver.o \
		mc_backtrack_solver.o \
		ac_backtrack_solver.o \
		bb_solver.o \
		ac_bb_solver.o

TARGET=main

CC=g++

CFLAGS+=-I./include

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) main.cpp -o $(TARGET)

clean:
	rm *.o
	rm main
