# EECE 5643 Course Poject: Simulating h.264 vs h.265 Video Codecs on Hardware and Software Systems

## Description
This repo contains a simulator for video streaming over a network. It is created to compare the performance of different video codecs and different implementations of them (namely hardware and software). The metrics collected are max and average performance cost and max and average network utilizaiton. From these metrics, the total number of users on the network or the quality of video available on the network can be computed. These parameters are stored in [simulation_parameters.h](./simulation_parameters.h).

## Building
To build the simulator, simply run the following command:
```
make 
```

## Usage
Configure parameters in [simulation_parameters.h](./simulation_parameters.h), then run the following command to execute the simulation:
```
make run_simulation
```

The simulation must be recompiled before every run.