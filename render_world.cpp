#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"
#include <map>

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find the closest object of intersection and return the object that was
// intersected.  Record the Hit structure in hit.  If no intersection occurred,
// return NULL.  Note that in the case of a Boolean, the object returned will be
// the Boolean, but the object stored in hit will be the underlying primitive.
// Any intersection with t<=small_t should be ignored.
Object* Render_World::Closest_Intersection(const Ray& ray, Hit& hit)
{
    // TODO
    std::vector<Hit> hits;
    std::map<double, Object*> objects_intersected;
    if (objects.empty())
    {
        return 0;
    }
    
    int size = 0;
    
    for (std::vector<Object*>::const_iterator ob = objects.begin(); ob != objects.end() ; ++ob)
    {   
        if((*ob)->Intersection(ray, hits)){
            for (unsigned int i = 0; i < hits.size()-size; i += 1)
            {
            	if ((hits.end()-1-i)->t > small_t)
            	{
            		objects_intersected[(hits.end()-1-i)->t] = *ob;
            	}                
            }
            size = hits.size();
        }
    }
    
    if (!objects_intersected.empty())
    {
    	std::cout<<objects_intersected.begin()->first<<" "<<objects_intersected.begin()->second<<std::endl;
		return objects_intersected.begin()->second;
    }
    return 0;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    vec3 world_postition_pixel = camera.World_Position(pixel_index);
    vec3 direction_input = world_postition_pixel - camera.position;
    Ray ray(camera.position, direction_input); // TODO: set up the initial view ray here
    
    vec3 color=Cast_Ray(ray,recursion_depth_limit);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    // TODO
    Hit hit;
    Object* closest_object = Closest_Intersection(ray, hit);
    
    vec3 color;
    // determine the color here
    
    if (closest_object == 0)
    {
        if (background_shader != 0)
        {
            color = background_shader->Shade_Surface(ray,vec3(0,0,0),vec3(0,0,0),recursion_depth);
        }       
    }
    else
    {
       vec3 intersection_point = ray.Point(hit.t);
       vec3 normal = closest_object->Normal(intersection_point);
       vec3 same_side_normal = hit.ray_exiting?-normal:normal;
       color = closest_object->material_shader->Shade_Surface(ray,intersection_point,same_side_normal,recursion_depth);
    }   
    return color;
    
}
