#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>
#include <limits>
#include <memory>

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

// Headers

#include "ray.h"
#include "vec3.h"


#endif