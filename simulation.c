#include <stdio.h>
#include <stdlib.h>
#include "simulation_parameters.h"
#include "simulation_data_structures.h"

int main(int argc, char *argv[])
{
    int i, j;
    computer *producers, *consumers;
    network_connection *network;
    stream *video_streams;
    
    printf("Beginning Simulation\n");


    // Create network
    network = (network_connection *) malloc(sizeof( network_connection ));
    network->bandwidth = NETWORK_BANDWITDH;
    network->usage = 0;


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

    // Create the actual streams
    video_streams = (stream *) malloc(sizeof( stream ) * NUM_PRODUCERS * NUM_CONSUMERS);
    for (i = 0; i < NUM_PRODUCERS; i++){
        for (j = 0; j < NUM_CONSUMERS; j++) {
            video_streams[i * NUM_CONSUMERS + j].producer = &producers[i];
            video_streams[i * NUM_CONSUMERS + j].consumers = &consumers[j];
        }
    }

    printf("Ending Simulation\n");

    free(producers);
    free(consumers);
    free(network);
}