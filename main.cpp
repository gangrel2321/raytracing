#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

bool hit_sphere(const point3& center, double radius, const ray& r) {
    // returns closest t value of hit if it hits or -1 if not
    vec3 trans_start = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(trans_start, r.direction());
    auto c = dot(trans_start, trans_start) - radius*radius; 
    auto discrim = b*b - 4*a*c;
    if (discrim < 0) {
        return -1.0;
    }
    else {
        return (-b - sqrt(discrim)) / (2.0*a);
    }
}

color ray_color(const ray& r) {
    point3 center{0,0,-1};
    auto t = hit_sphere(center, 0.5, r);
    if (t > 0.0) {
        vec3 normal = unit_vector(r.at(t) - center);
        return 0.5*color(normal.x()+1, normal.y()+1, normal.z()+1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}


int main() {

    // Define image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Define camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical =vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    // Render rays
    
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j = image_height-1; j>=0; j--) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for(int i = 0; i < image_width; i++) {
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";
}