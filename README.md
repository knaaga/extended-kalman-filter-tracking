# Extended Kalman Filter for State Estimation
## Overview
The goal of this project is to utilize a Kalman filter to estimate the state of a moving vehicle with noisy lidar and radar measurements. The measurement data is provided by a [simulator](https://github.com/udacity/self-driving-car-sim/releases). The key metrics used to evaluate the filter are RMSE values for both position and velocity of the tracked vehicle. 

## Linear Kalman Filters and Extended Kalman Filters
The Kalman filter is a recursive Bayesian filtering technique that uses a series of measurements over time, including statistical noise and produces estimates of unknown quantities. The linear Kalman filter is applicable only to linear Gaussian systems. When a set of linear measurement mapping functions are applied to the Gaussian estimate, the result is a Gaussian as well. However, when non-linear mapping functions such as radar equations are applied to the Gaussian, the result is no longer a Gaussian. Therefore linear Kalman filter equations do not apply anymore.

The solution here is to linearize the mapping function using Taylor series approximation. This involves calculating the derivative (Jacobian in the multivariate case) of the non-linear function. These linearized equations can then be used to map the radar measurements such as range, bearing and range rate to position and velocity. This variation of Kalman filter that accounts for non-linearities is called an extended Kalman filter. 

## Dependencies

* cmake >= 3.5
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make` 
4. Run it: `./ExtendedKF `

## Simulation Results

![](https://github.com/knaaga/extended-kalman-filter-tracking/blob/main/assets/EKF_Simulator.JPG)


