#include <stdio.h>
#include <stdlib.h>
#include "simulation_parameters.h"
#include "simulation_data_structures.h"

int main(int argc, char *argv[])
{
    int i;
    computer *producers, *consumers;
    network_connection *network;
    
    printf("Beginning Simulation\n");


    network = (network_connection *) malloc(sizeof( network_connection ));


    // Create producers
    producers = (computer *) malloc(NUM_PRODUCERS * sizeof( computer ));
    for (i = 0; i < NUM_PRODUCERS; i++) {
        producers[i].type = PRODUCER;
        producers[i].codec = CODEC_TYPE;
        producers[i].connection = network;
    }

    // Create consumers
    consumers = (computer *) malloc(NUM_CONSUMERS * sizeof( computer ));
    for (i = 0; i < NUM_CONSUMERS; i++) {
        consumers[i].type = CONSUMER;
        consumers[i].codec = CODEC_TYPE;
        consumers[i].connection = network;
    }

    printf("Ending Simulation\n");

    free(producers);
    free(consumers);
    free(network);
}