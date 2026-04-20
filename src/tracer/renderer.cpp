// std libs:
#include <iostream>

// custom libs:
#include "vec3.h"
#include "ray.h"
#include "color.h"

bool hit_sphere(const point3& center, double radius, const ray& r) {
	/*
	 * Checks wether the ray r hits the surface of the sphere of given center and radius
	 *
	 * Note that if the ray's parametric equation is written as 
	 * 
	 * r(t) = O+D*t
	 * 
	 * Then you can check if the point r(t) hits the surface by using the sphere equation:
	 * 
	 * (r(t)-C)^2 = r^2
	 * 
	 * With C being the sphere's center point. If we expand this equation we get a quadratic
	 * equation, so we simply use the quadratic formula to obtain the parameter values t in
	 * which the ray crosses the sphere. a, b and c below are the quadratic terms of the
	 * resulting quadratic equation.
	*/
    vec3 oc = center - r.origin(); // vector from ray origin to sphere center
	
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}

color ray_color(const ray& r) {
	// Gradient from blue to white:
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);

	// Adding a red sphere:
	if (hit_sphere(point3(0,0,-1), 0.5, r))
        return color(1, 0, 0);
	
	// The return basically takes care of the background:
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}
/* What I have just notices in the function above is that for each object 
 * in the scene we can add an if statement checking wether a ray hits their
 * surface or not. Everything outside the if statement composes the background.
*/

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
	double focal_length  = 1.0;
	point3 camera_center = point3(0, 0, 0);

	// Viewport is a virtual rectangle containing the grid of pixel positions
	double viewport_height = 2.0;
	auto viewport_width    = viewport_height * (double(image_width)/image_height);

	// The following vectors indicate horizontal and vertical direction in the viewport:
	vec3 viewport_horiz = vec3(viewport_width, 0, 0);
	vec3 viewport_vert  = vec3(0, -viewport_height, 0);

	// Notice that a higher focal_length means the viewport is further from the camera
	// thus closer to the objects in the scene, making things appear closer/zooming
	// in the image!

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
