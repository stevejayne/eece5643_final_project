#include <stdint.h>
#include <stdbool.h>

#ifndef SIMULATION_DATA_STRUCTURES_H

enum stream_type { PRODUCER, CONSUMER };           // What the role of the computer is in streaming
enum codec_type { h264, h265 };                    // Which codec is being used
enum processing_method { HARDWARE, SOFTWARE };     // Is the codec processed on software or hardware
enum video_quality { HALF_HD, HD, FULL_HD, UHD };  // Quality of video being streamed

// A computer being used to produce or consume streamed video
// It is connected to a network
typedef struct computer {
   enum stream_type type;
   enum codec_type codec;
   enum processing_method method;
   struct network_connection *connection;
   bool checked;
} computer;


// A network connection element that simulates the netowrk being streamed on
typedef struct network_connection {
    uint64_t bandwidth;
    uint64_t usage;
    uint16_t num_connected_elements;
    struct computer *connected_elements;
} network_connection;

// Represents which consumers are watching which content
typedef struct stream {
    struct computer *producer;
    struct computer *consumers;
    enum video_quality quality;
    bool active;
} stream;

// A video format
typedef struct video {
    enum video_quality quality;
    uint64_t size;
} video;


// Performance metrics data structure
typedef struct metrics {
    uint64_t max_processing_power;
    uint64_t max_network_usage;
    uint64_t total_processing_power;
    uint64_t total_network_usage;
} metrics;

#define SIMULATION_DATA_STRUCTURES_H
#endif