#include "plane.h"
#include "ray.h"
#include <cfloat>


// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
bool Plane::
Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    vec3 w = ray.direction;
    vec3 v = ray.endpoint - x1;
    Hit hit;
    if (dot(w,normal) != 0)
    {
        double t_tmp = -dot(v,normal)/dot(w,normal);
        hit.object = this;
        hit.ray_exiting = false;
        if (t_tmp < 0)
        {
            hit.t = 0;         
        }
        else
        {
            hit.t = t_tmp;
        }
        hits.push_back(hit);
        return true;
    }
    return false;
}

vec3 Plane::
Normal(const vec3& point) const
{
    return normal;
}
