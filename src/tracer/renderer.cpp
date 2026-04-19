// std libs:
#include <iostream>

// custom libs:
#include "vec3.h"
#include "ray.h"
#include "color.h"

color ray_color(const ray& r) {
	// Testing with gradient from blue to white:
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {
    // Fixed aspect ratio and width:
	auto aspect_ratio = 16.0/9.0; // width/height
	int image_width   = 400;

    // Height is calculated based on the other 2:
    int image_height = int(image_width/aspect_ratio);
	// Height must be at least 1:
	image_height = (image_height < 1) ? 1 : image_height;
	// This is the conditional operator (usually called ternary, but that's misleading):
	// (condition) ? [result if true]:[result if false]

	/* Coordinate system:
	 * x-> left-to-right (+ = right)
	 * y-> Vertical axis (+ = up)
	 * z-> front-to-back (- = in front, weirdly)
	*/  
	// Camera and viewport:
	double focal_length  = 2.0;
	point3 camera_center = point3(0, 0, 0);

	// Viewport is a virtual rectangle containing the grid of pixel positions
	double viewport_height = 2.0;
	auto viewport_width    = viewport_height * (double(image_width)/image_height);

	// The following vectors indicate horizontal and vertical direction in the viewport:
	vec3 viewport_horiz = vec3(viewport_width, 0, 0);
	vec3 viewport_vert  = vec3(0, -viewport_height, 0);

	// Horizontal and vertical spacings between pixels:
	vec3 pixel_delta_horiz = viewport_horiz/image_width;
	vec3 pixel_delta_vert = viewport_vert/image_height;

	// Position of viewport's top left corner:
	point3 viewport_topleft = camera_center - vec3(0,0,focal_length) - 
							  viewport_horiz/2 - viewport_vert/2;

	// Pixel positions are centered:
	point3 pixel00_loc = viewport_topleft + 0.5*(pixel_delta_horiz+pixel_delta_vert);

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
	    
	    point3 pixel_center = pixel00_loc + (i * pixel_delta_horiz) + (j * pixel_delta_vert);
	    vec3 ray_direction = pixel_center - camera_center; // Not a unit vector
		ray r(camera_center, ray_direction); // creating an instance of ray

		color pixel_color = ray_color(r);

	    // Write actual color:
	    write_color(std::cout, pixel_color);
        }
    }
}
