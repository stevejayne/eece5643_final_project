#include <stdio.h>
#include <stdlib.h>
#include "simulation_parameters.h"
#include "simulation_data_structures.h"

int get_packet_size(stream *video_stream, int producer_num)
{
    // Start with initial packet size
    int packet_size = 1;

    // Account for codec used
    if (video_stream->producer[producer_num].codec == h264) {
        packet_size = packet_size * 10;
    } else if (video_stream->producer[producer_num].codec == h265) {
         packet_size = packet_size * 2;
    } else {
        printf("Error decoding the codec type in get_packet_size\n");
    }

    // Account for the quality of the video
    if (video_stream->quality == HALF_HD) {
        packet_size = packet_size * 1;
    } else if (video_stream->quality == HD) {
        packet_size = packet_size * 2;
    } else if (video_stream->quality == FULL_HD) {
        packet_size = packet_size * 4;
    } else if (video_stream->quality == UHD) {
        packet_size = packet_size * 8;
    } else {
        printf("Error decoding the video quality in get_packet_size\n");
    }

    return packet_size;
}

int get_processing_power_used(stream *video_stream, int producer_num)
{
    // Start with initial processing used
    int processing_used = 1;

    // Account for codec used and method of decoding
    if (video_stream->producer[producer_num].codec == h264) {
        if (video_stream->producer[producer_num].method == HARDWARE) {
            processing_used = processing_used * 1;
        } else if (video_stream->producer[producer_num].method == SOFTWARE) {
            processing_used = processing_used * 5;
        } else {
            printf("Error decoding the encoding method in get_processing_power_used\n");
        }
    } else if (video_stream->producer[producer_num].codec == h265) {
        if (video_stream->producer[producer_num].method == HARDWARE) {
            processing_used = processing_used * 2;
        } else if (video_stream->producer[producer_num].method == SOFTWARE) {
            processing_used = processing_used * 10;
        } else {
            printf("Error decoding the encoding method in get_processing_power_used\n");
        }
    } else {
        printf("Error decoding the codec type in get_processing_power_used\n");
    }

    return processing_used;
}

void update_metrics(metrics *simulation_metrics, network_connection *network, uint32_t processing_in_iteration)
{
    // Update processing used in that iteration
    if (processing_in_iteration > simulation_metrics->max_processing_power) {
        simulation_metrics->max_processing_power = processing_in_iteration;
    }
    simulation_metrics->total_processing_power = processing_in_iteration;

    // Update network utilization used in that iteration
    if (network->usage > simulation_metrics->max_network_usage) {
        simulation_metrics->max_network_usage = network->usage;
    }
    simulation_metrics->total_network_usage = network->usage;
}

int main(int argc, char *argv[])
{
    int i, j;
    uint64_t simulation_time = 0;
    int32_t temp_packet_size, temp_processing_power, total_packet_size;

    computer *producers, *consumers;
    network_connection *network;
    stream *video_streams;

    // Create performance metrics structures
    metrics simulation_performance_metrics;
    simulation_performance_metrics.max_processing_power = 0;
    simulation_performance_metrics.max_network_usage = 0;


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
    video_streams = (stream *) malloc(sizeof( stream ) * NUMBER_OF_STREAMS);
    for (i = 0; i < NUM_PRODUCERS; i++){
        for (j = 0; j < NUM_CONSUMERS; j++) {
            video_streams[i * NUM_CONSUMERS + j].producer = &producers[i];
            video_streams[i * NUM_CONSUMERS + j].consumers = &consumers[j];
            video_streams[i * NUM_CONSUMERS + j].quality = HALF_HD;
        }
    }

    // This loop represents the actual simulation
    printf("Beginning Simulation\n");
    
    while (!RUN_UNTIL_END && simulation_time < SIMULATION_CUTOFF_TIME) {
        // Evaluate each stream
        for (i = 0; i < NUMBER_OF_STREAMS; i++) {
            temp_packet_size = get_packet_size(&video_streams[i], i);
            get_processing_power_used(&video_streams[i], i);

            update_metrics(&simulation_performance_metrics, network, temp_packet_size);
        }

        simulation_time++;
    }

    printf("Ending Simulation\n");
    printf("Ran the simulation for %llu seconds\n", simulation_time);

    free(producers);
    free(consumers);
    free(network);
    free(video_streams);
}