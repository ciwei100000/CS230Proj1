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
    Hit hit1,hit2,hit3;
    if (dot(v,normal) < 0)
    {
    	hit1.object = this;
    	hit1.ray_exiting = false;
    	hit1.t = 0;
    	
    	hits.push_back(hit1);
    	
        if(dot(w,normal)>0)
        {
        	hit2.object = this;
        	hit2.ray_exiting = true;
    		hit2.t = -dot(v,normal)/dot(w,normal);
    		hits.push_back(hit2);
        }
        if(debug_pixel == true)
        {
        	std::cout<<"Plane: inside "<<"normal: "<<normal<<" x1 "<<x1<<"Hit: "<<hit2.t<<"  Address:"<<this<<std::endl;
        }
		return true;
	}
     
	if (dot(w,normal) < 0)
    {
    	hit3.object = this;
    	hit3.t = -dot(v,normal)/dot(w,normal);
     	hit3.ray_exiting = false;
     	hits.push_back(hit3);
     	
     	if(debug_pixel == true)
        {
        	std::cout<<"Plane: outside "<<"normal: "<<normal<<" x1 "<<x1<<"Hit: "<<hit3.t<<"  Address:"<<this<<std::endl;
        }
        return true;
    }
	return false;
}

vec3 Plane::
Normal(const vec3& point) const
{
    return normal;
}
