#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>
#include <limits>
#include <memory>
#include <random>

// Using statements 

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double INF = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

// Functions

double degrees_to_radians(double degrees) {
    return degrees * PI / 180.0;
}

double clamp(double x, double min, double max) {
    return x < min ? min : x > max ? max : x;
}

double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
double random_double(double min, double max) {
    return random_double()*(max - min) + min;
}

// Headers

#include "ray.h"
#include "vec3.h"


#endif