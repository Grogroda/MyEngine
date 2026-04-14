// std libs:
#include <iostream>

// custom libs:
#include "vec3.h"
#include "color.h"

int main() {
    // Image

    int image_width = 256;
    int image_height = 256;

    // Render

    // P3 in the beginning of the file indicates colors are coded in ASCII
    // In the nex line we print 'width height' in pixels
    // Last we indicate the maximum color value (255)
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // After this, we can produce the image:
    for (int j = 0; j < image_height; j++) {
	// Progress bar:
	std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush; 
        for (int i = 0; i < image_width; i++) {
	    /* 
	     * For each row, starting from top, we are
	     * printing the pixel values from left to
	     * right, and then each row from top to bottom.
	     */
	    
	    // Fractions of the colors (0 to 1):
	    double r_frac = double(i)/(image_width-1);
	    double g_frac = double(j)/(image_height-1);
	    double b_frac = 0;
	    
	    // Fractional color vector:
	    vec3 pixel_color = color(r_frac, g_frac, b_frac);

	    // Write actual color:
	    write_color(std::cout, pixel_color);
        }
    }
}
