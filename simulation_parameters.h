#include "simulation_data_structures.h"

// Streaming parameters
#define NUM_PRODUCERS 1 // Options: 1-30
#define NUM_CONSUMERS 125 // Options: 1-30

#define NUMBER_OF_STREAMS (NUM_PRODUCERS * NUM_CONSUMERS)

#define CODEC_TYPE h265    // Options: h264 or h265
#define STREAM_QUALITY UHD  // Options: HALF_HD, HD, FULL_HD, UHD

#define PRODUCER_METHOD HARDWARE // Options: HARDWARE, SOFTWARE
#define CONSUMER_METHOD SOFTWARE // Options: HARDWARE, SOFTWARE

// Network Parameterss
#define NETWORK_BANDWITDH 1000 // Options: 1000-1000000 in Mb
#define NETWORK_SPEED 1000     // Options: 1-10000 in Mbps


// Codec Processing parameters
// MODIFY THESE TO FIT VALUES TO MATCH DATA FROM PAPERS
#define PACKET_SIZE_RATIO 1.754 // Options(double): the ratio of the final output size of h.264 vs h.265
                                // in example, h.264 is 10x the size of h.265


// Ratios of the performance of Codecs on given devices
// MODIFY THESE TO FIT VALUES TO MATCH DATA FROM PAPERS
#define PERFORMANCE_H264_HW_PROD 2
#define PERFORMANCE_H264_SW_PROD 10
#define PERFORMANCE_H265_HW_PROD 3
#define PERFORMANCE_H265_SW_PROD 4

#define PERFORMANCE_H264_HW_CONS 1
#define PERFORMANCE_H264_SW_CONS 5
#define PERFORMANCE_H265_HW_CONS 2
#define PERFORMANCE_H265_SW_CONS 8


// Simulation parameters
#define SIMULATION_CUTOFF_TIME 10 // Number of simulated seconds to run the simulation for
#define RUN_UNTIL_END 0            // Set to 1 for true, otherwise set 0 for false


