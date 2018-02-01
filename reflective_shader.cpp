#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth) const
{
    vec3 color;
    // TODO: determine the color
    vec3 n = same_side_normal;
    color = (1-reflectivity)* shader->Shade_Surface(ray,intersection_point,same_side_normal,recursion_depth);
    
    if (recursion_depth > 1)
    {
    	vec3 incoming_ray_direction = -ray.direction;
    
    	vec3 reflected_ray_direction = 2 * dot(incoming_ray_direction, n) * n- incoming_ray_direction;
    	
    	Ray reflected_ray(intersection_point, reflected_ray_direction);
    	
    	recursion_depth--;
    	
    	color += reflectivity * world.Cast_Ray(reflected_ray, recursion_depth);
    }         
    
    return color;
}
