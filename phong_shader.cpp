#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"


vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth) const
{
    vec3 color, I, i, I_itensity;
    // TODO: determine the color
    double distance = 0;
    double costheta = 0;
    Object* shadowray_hit_object = 0;
    vec3 n = same_side_normal;
    std::vector<Light*> lights = world.lights;
    Light* light;
    
    color = world.ambient_intensity * world.ambient_color * color_ambient; // ambient
    
    for(std::vector<Light*>::iterator light_iter = lights.begin();light_iter != lights.end(); ++light_iter)
    {
        light = *light_iter;
        I = light->position - intersection_point; // Incoming Light Vector
        i = I.normalized();
        distance = I.magnitude();
        
        if (world.enable_shadows == true)
        {
        	Ray shadowray(intersection_point, i);
        	Hit shadowhit;     	
        	
        	
        	shadowray_hit_object = world.Closest_Intersection(shadowray,shadowhit);
        	
        	if(debug_pixel == true)
        	{
        		std::cout<<"shadow "<<shadowray_hit_object<<" "<<shadowhit.t<<" " <<shadowhit.object<<std::endl;
        	}
        	
        	if (shadowhit > distance)
        	{
        		shadowray_hit_object = 0;
        	}
        }
        
        I_itensity = light->Emitted_Light(ray)/(distance * distance);
        if (dot(i,n)>0)
        {
        	costheta = dot((2 * dot(i,n) * n - i), -ray.direction);
        }
        
        if (!shadowray_hit_object)
        {
        	if(debug_pixel == true)
        	{
        		std::cout<<shadowray_hit_object<<std::endl;
        	}
        	color += I_itensity * (color_diffuse * std::max(0.0, dot(n,i)) + 
        		 color_specular * pow(std::max(0.0, costheta),specular_power));
        }     
        
    }
    return color;
}
