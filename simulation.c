#include <stdio.h>
#include <stdlib.h>
#include "simulation_parameters.h"
#include "simulation_data_structures.h"

void display_metrics(metrics *simulation_metrics, uint64_t simulation_time)
{
    // Print simulation runtime
    printf("Ran the simulation for %llu seconds\n\n", simulation_time);

    // Print system config

    // Print network usage metrics
    printf("Total network usage: %lf\n", simulation_metrics->total_network_usage);
    printf("Max network usage: %lf\n", simulation_metrics->max_network_usage);
    printf("Average network usage: %f\n", simulation_metrics->total_network_usage / simulation_time);
    printf("Average network usage(%%): %f\n\n", simulation_metrics->total_network_usage / simulation_time / NETWORK_BANDWITDH);


    // Print power usage metrics
    printf("Total processing power used: %lf\n", simulation_metrics->total_processing_power);
    printf("Max processing power used: %lf\n", simulation_metrics->max_processing_power);
    printf("Average processing power used: %f\n", simulation_metrics->total_processing_power / simulation_time);

}

double account_for_quality(double givenValue, enum video_quality quality)
{

    // Account for the quality of the video
    if (quality == HALF_HD) {
        return givenValue;
    } else if (quality == HD) {
        return givenValue * 2;
    } else if (quality == FULL_HD) {
        return givenValue * 4;
    } else if (quality == UHD) {
        return givenValue * 8;
    } else {
        printf("Error decoding the video quality in get_packet_size\n");
        return -1;
    }
}

double get_packet_size(stream *video_stream)
{
    // Start with initial packet size
    double packet_size = 1.0; 

    // Account for codec used
    if (video_stream->producer->codec == h264) {
        packet_size = packet_size * PACKET_SIZE_RATIO;
    } else if (video_stream->producer->codec == h265) {
         packet_size = packet_size;
    } else {
        printf("Error decoding the codec type in get_packet_size\n");
    }

    // Account for the quality of the video
    packet_size = account_for_quality(packet_size, video_stream->quality);

    return packet_size;
}

double get_processing_used_prod(stream *video_stream)
{
    // Start with initial processing used
    double processing_used = 1;

    // Account for codec used and method of decoding
    if (video_stream->producer->codec == h264) {
        if (video_stream->producer->method == HARDWARE) {
            processing_used = processing_used * PERFORMANCE_H264_HW_PROD;
        } else if (video_stream->producer->method == SOFTWARE) {
            processing_used = processing_used * PERFORMANCE_H264_HW_CONS;
        } else {
            printf("Error decoding the encoding method in get_processing_used_prod\n");
        }
    } else if (video_stream->producer->codec == h265) {
        if (video_stream->producer->method == HARDWARE) {
            processing_used = processing_used * PERFORMANCE_H265_HW_PROD;
        } else if (video_stream->producer->method == SOFTWARE) {
            processing_used = processing_used * PERFORMANCE_H265_SW_PROD;
        } else {
            printf("Error decoding the encoding method in get_processing_used_prod\n");
        }
    } else {
        printf("Error decoding the codec type in get_processing_used_prod\n");
    }

    // Account for the quality of the video
    processing_used = account_for_quality(processing_used, video_stream->quality);

    return processing_used;
}

double get_processing_power_cons(stream *video_stream)
{
    // Start with initial processing used
    double processing_used = 1;

    // Account for codec used and method of decoding
    if (video_stream->consumers->codec == h264) {
        if (video_stream->consumers->method == HARDWARE) {
            processing_used = processing_used * PERFORMANCE_H264_HW_CONS;
        } else if (video_stream->consumers->method == SOFTWARE) {
            processing_used = processing_used * PERFORMANCE_H264_SW_CONS;
        } else {
            printf("Error decoding the encoding method in get_processing_power_cons\n");
        }
    } else if (video_stream->consumers->codec == h265) {
        if (video_stream->consumers->method == HARDWARE) {
            processing_used = processing_used * PERFORMANCE_H265_HW_CONS;
        } else if (video_stream->consumers->method == SOFTWARE) {
            processing_used = processing_used * PERFORMANCE_H265_SW_CONS;
        } else {
            printf("Error decoding the encoding method in get_processing_power_cons\n");
        }
    } else {
        printf("Error decoding the codec type in get_processing_power_cons\n");
    }

    // Account for the quality of the video
    processing_used = account_for_quality(processing_used, video_stream->quality);

    return processing_used;
}

void update_metrics(metrics *simulation_metrics, network_connection *network, uint32_t processing_in_iteration)
{
    // Update processing used in that iteration
    if (processing_in_iteration > simulation_metrics->max_processing_power) {
        simulation_metrics->max_processing_power = processing_in_iteration;
    }
    simulation_metrics->total_processing_power += processing_in_iteration;

    // Update network utilization used in that iteration
    if (network->usage > simulation_metrics->max_network_usage) {
        simulation_metrics->max_network_usage = network->usage;
    }
    simulation_metrics->total_network_usage += network->usage;
}

int main(int argc, char *argv[])
{
    int i, j;
    uint64_t simulation_time = 0;
    double temp_packet_size, temp_processing_power, aggregate_processing_power;
    bool exitFlag = false;

    computer *producers, *consumers;
    network_connection *network;
    stream *video_streams;

    // Create performance metrics structures
    metrics simulation_performance_metrics;
    simulation_performance_metrics.max_processing_power = 0;
    simulation_performance_metrics.max_network_usage = 0;
    simulation_performance_metrics.total_processing_power = 0;
    simulation_performance_metrics.total_network_usage = 0;


    // Create network
    network = (network_connection *) malloc(sizeof( network_connection ));
    network->bandwidth = NETWORK_BANDWITDH;
    network->usage = 0;


    // Create producers
    producers = (computer *) malloc(NUM_PRODUCERS * sizeof( computer ));
    for (i = 0; i < NUM_PRODUCERS; i++) {
        producers[i].type = PRODUCER;
        producers[i].codec = CODEC_TYPE;
        producers[i].method = PRODUCER_METHOD;
        producers[i].connection = network;
    }

    // Create consumers
    consumers = (computer *) malloc(NUM_CONSUMERS * sizeof( computer ));
    for (i = 0; i < NUM_CONSUMERS; i++) {
        consumers[i].type = CONSUMER;
        consumers[i].codec = CODEC_TYPE;
        consumers[i].method = CONSUMER_METHOD;
        consumers[i].connection = network;
    }

    // Create the actual streams
    video_streams = (stream *) malloc(sizeof( stream ) * NUMBER_OF_STREAMS);
    for (i = 0; i < NUM_PRODUCERS; i++){
        for (j = 0; j < NUM_CONSUMERS; j++) {
            video_streams[i * NUM_CONSUMERS + j].producer = &producers[i];
            video_streams[i * NUM_CONSUMERS + j].consumers = &consumers[j];
            video_streams[i * NUM_CONSUMERS + j].quality = STREAM_QUALITY;
            video_streams[i * NUM_CONSUMERS + j].active = true;
        }
    }

    // This loop represents the actual simulation
    printf("Beginning Simulation\n");
    
    while (simulation_time < SIMULATION_CUTOFF_TIME) {
        // Evaluate each stream
        network->usage = 0;
        aggregate_processing_power = 0;

        // Reset producer power flag
        for (i = 0; i < NUM_PRODUCERS; i++) {
            producers[i].checked = false;
        }

        // Get network and power usage
        for (i = 0; i < NUMBER_OF_STREAMS; i++) {
            temp_processing_power = 0;

            if (!video_streams[i].producer->checked) {
                temp_processing_power += get_processing_used_prod(&video_streams[i]);
                video_streams[i].producer->checked = true;
            }

            temp_processing_power += get_processing_power_cons(&video_streams[i]);

            temp_packet_size = get_packet_size(&video_streams[i]);

            aggregate_processing_power += temp_processing_power;
            network->usage += temp_packet_size;

            // Exit sim if bandwidth exceeds
            if (network->usage > network->bandwidth) {
                exitFlag = true;
                break;
            }
        }

        // Exit sim if bandwidth exceeds
        if (exitFlag)
            break;

        // Update the metrics for this iteration
        update_metrics(&simulation_performance_metrics, network, aggregate_processing_power);

        simulation_time++;
    }

    if (exitFlag)
        printf("Network usage exceeds bandwidth\n");

    printf("Ending Simulation\n");
    
    display_metrics(&simulation_performance_metrics, simulation_time);

    free(producers);
    free(consumers);
    free(network);
    free(video_streams);
}