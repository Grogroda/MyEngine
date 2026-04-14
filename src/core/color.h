#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

// We will use a new alias to vec3 (color)
// Each color will be an instance of vec3
using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) {
    // pixel color should be a double from 0 to 1:
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // std::cout << "Color: (" << rbyte << ", " << gbyte << ", " << bbyte << ")" << std::endl;

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif
