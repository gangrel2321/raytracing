#ifndef HITTABLE_H
#define HITTABLE_H

#include "utilities.h"

class material;

struct hit_record { 
    point3 p;
    vec3 normal;
    double t;
    bool front_face;
    shared_ptr<material> mat_ptr;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        // check if same direction or not 
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }

};

class hittable {
    public: 
        virtual bool hit(const ray& r, double t_min, \
            double t_max, hit_record& rec) const = 0;
};

#endif