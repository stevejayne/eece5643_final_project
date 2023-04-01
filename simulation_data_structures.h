#include <stdint.h>

#ifndef SIMULATION_DATA_STRUCTURES_H

enum stream_type { PRODUCER, CONSUMER };       // What the role of the computer is in streaming
enum codec_type { h264, h265 };                // Which codec is being used
enum processing_method { HARDWARE, SOFTWARE }; // Is the codec processed on software or hardware

// A computer being used to produce or consume streamed video
// It is connected to a network
typedef struct computer {
   enum stream_type type;
   enum codec_type codec;
   enum processing_method method;
   struct network_connection *connection;
} computer;


// A network connection element that simulates the netowrk being streamed on
typedef struct network_connection {
    uint64_t bandwitdh;
    uint64_t usage;
    uint16_t num_connected_elements;
    struct computer *connected_elements;
} network_connection;

#define SIMULATION_DATA_STRUCTURES_H
#endif