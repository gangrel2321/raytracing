#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    public: 
        sphere() {}
        sphere (point3 cen, double r, shared_ptr<material> mat) : center(cen), radius(r), mat_ptr(mat) {};

        virtual bool hit(
            const ray& r, double t_min, double t_max, \
                hit_record& rec) const override;
        
    public: 
        point3 center;
        double radius;
        shared_ptr<material> mat_ptr;
};


bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    // t^2 b.b - 2t b.(A-C) + (A-C).(A-C) - r^2 = 0
    // x = -b +/ sqrt(b^2 - 4ac) / 2a
    // a = b.b, b = -b.(A-C), c = (A-C).(A-C) - r^2 
    
    // quad formula stuff
    vec3 og = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(og, r.direction());
    auto c = og.length_squared() - radius*radius;

    auto discrim = half_b*half_b - a*c;
    if(discrim < 0) return false;
    auto sqrtd = sqrt(discrim);

    // Find the nearest root
    auto root = (-half_b - sqrtd) / a;
    if(root < t_min || root > t_max) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || root > t_max) 
            return false;    // no roots in acceptable range
    }

    // record hit to hit record
    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 normal = (rec.p - center) / radius; //outward normal
    rec.set_face_normal(r, normal);
    rec.mat_ptr = mat_ptr;
    return true;
}


#endif 