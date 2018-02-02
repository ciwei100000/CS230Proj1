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
        if(t1 > 0)
        {
        	hit1.object = this;
        	hit1.ray_exiting = false;
        	hit1.t = std::max(0.0, t0);
        	hit2.object = this;
        	hit2.t = t1;
        	hit2.ray_exiting = true;
        	
        	hits.push_back(hit1);
        	hits.push_back(hit2);
        	
        	if(debug_pixel == true)
        	{
        		std::cout<<"Sphere: "<<"center: "<<center<<"radius "<<radius<<"Hit: "<<t0<<" "<<t1<<" Address:"<<this<<std::endl;
        	}

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
