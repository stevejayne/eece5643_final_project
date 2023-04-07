CC=gcc
CFLAGS=-std=c17
OPT=-O3

all: simulation

simulation: simulation.c simulation_data_structures.h simulation_parameters.h
	$(CC) $(CFLAGS) $(OPT) simulation.c -o simulation

run_simulation: simulation
	@./simulation

run: simulation
	@./simulation

clean:
	@rm -rf simulation

.PHONY: clean run_simulation run