#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"


vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth) const
{
    vec3 color, I, l, I_itensity;
    // TODO: determine the color
    double distance = 0;
    double costheta = 0;
    vec3 n = same_side_normal;
    std::vector<Light*> lights = world.lights;
    Light* light;
    
    color = world.ambient_intensity * world.ambient_color * color_ambient; // ambient
    
    for(std::vector<Light*>::iterator light_iter = lights.begin();light_iter != lights.end(); ++light_iter)
    {
        light = *light_iter;
        I = light->position - intersection_point; // Incoming Light Vector
        l = I.normalized();
        distance = I.magnitude();
        I_itensity = light->Emitted_Light(ray)/(distance * distance);
        costheta = dot((2 * distance * dot(l,n) * n - I).normalized(), n);  
        color += I_itensity * (color_diffuse * std::max(0.0, dot(n,l)) + 
        		 color_specular * std::max(0.0, pow(costheta, specular_power)));
       	//std::cout<<dot(n,l)<<std::endl;
    }
    return color;
}
