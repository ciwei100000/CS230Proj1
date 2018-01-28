#include "sphere.h"
#include "ray.h"


// Determine if the ray intersects with the sphere
bool Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    vec3 v = ray.endpoint - center;
    vec3 w = ray.direction;
    Hit hit;
    double D = dot(w,v)^2-dot(w,w)*(dot(v,v)-radius^2);
    if (D > 0)
    {
        double t0 = -dot(w,v) - sqrt(D);
        double t1 = -dot(w,v) + sqrt(D);
        if (t1 < 0)
        {
            return false;
        }
        else if (t0 < 0)
        {
            hit.object = *this;
            hit.t = 0;
            hit.ray_exiting = false;
            hits.push_back(hit);
            hit.t = t1;
            hit.ray_exiting = true;
            hits.push_back(hit);
        }
        else{
            hit.object = *this;
            hit.t = t0;
            hit.ray_exiting = false;
            hits.push_back(hit);
            hit.t = t1;
            hit.ray_exiting = true;
            hits.push_back(hit);
        }
    }
    return false;
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    // TODO: set the normal
    normal = (point - center).normalized;
    return normal;
}
