#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

void write_color(std::ostream &out , color pixel_color, int samples_per_pixel) {
    // divide by number of samples for averaging
    auto r = pixel_color.x() / samples_per_pixel;
    auto g = pixel_color.y() / samples_per_pixel;
    auto b = pixel_color.z() / samples_per_pixel;

    

    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif