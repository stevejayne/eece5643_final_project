#include "simulation_data_structures.h"

// Streaming parameters
#define NUM_PRODUCERS 1 // Options: 1-30
#define NUM_CONSUMERS 5 // Options: 1-30

#define NUMBER_OF_STREAMS (NUM_PRODUCERS * NUM_CONSUMERS)

#define CODEC_TYPE h265    // Options: h264 or h265
#define STREAM_QUALITY FULL_HD  // Options: HALF_HD, HD, FULL_HD, UHD

#define PRODUCER_METHOD HARDWARE
#define CONSUMER_METHOD SOFTWARE

// Network Parameterss
#define NETWORK_BANDWITDH 1000 // Options: 1000-1000000 in Mb
#define NETWORK_SPEED 1000       // Options: 1-10000 in Mbps


// Codec Processing parameters


// Simulation parameters
#define SIMULATION_CUTOFF_TIME 10 // Number of simulated seconds to run the simulation for
#define RUN_UNTIL_END 0            // Set to 1 for true, otherwise set 0 for false


