#include "sphere.h"
#include "ray.h"


// Determine if the ray intersects with the sphere
bool Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    vec3 v = ray.endpoint - center;
    vec3 w = ray.direction;
    Hit hit1,hit2;
    double D = dot(w,v)*dot(w,v)-dot(w,w)*(dot(v,v)-radius*radius);
    if (D > 0)
    {
        double t0 = -dot(w,v) - sqrt(D);
        double t1 = -dot(w,v) + sqrt(D);
        if (t1 >= 0)
        {
            hit1.object = this;
            hit1.ray_exiting = false;
            if (t0 < 0)
            {                
                hit1.t = 0;
            }
            else{
                hit1.t = t0;
            }
            hit2.object = this;
            hit2.ray_exiting = false;
            hit2.t = t1;
            hit2.ray_exiting = true;
            
            hits.push_back(hit1);
            hits.push_back(hit2);

            return true;
        }
    }
    return false;
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    // TODO: set the normal
    normal = (point - center).normalized();
    return normal;
}
