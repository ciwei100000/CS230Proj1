#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"
#include <map>
#include <utility>

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
    std::map<Hit, Object*> objects_intersected;
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
            	if (*(hits.end()-1-i)> small_t)
            	{
            		objects_intersected[*(hits.end()-1-i)] = *ob;
            	}                
            }
            size = hits.size();
        }
    }
    
    if (!objects_intersected.empty())
    {
    	hit = objects_intersected.begin()->first;
		return objects_intersected.begin()->second;
    }
    return 0;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
	vec3 color;
    std::vector<vec3> world_postition_pixels = camera.World_Position(pixel_index);
    if (debug_pixel == true)
    {
    	std::cout<<"world_postition_pixels amount: "<<world_postition_pixels.size()<<std::endl;
    }
    for (std::vector<vec3>::iterator i = world_postition_pixels.begin(); i != world_postition_pixels.end(); ++i)
    {
    	vec3 direction_input = *i - camera.position;
    	Ray ray(camera.position, direction_input);    
    	color+=Cast_Ray(ray,recursion_depth_limit);
    }
    
    color /= world_postition_pixels.size();
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
       
       if(debug_pixel == true)
        	{
        		std::cout<<"orginal "<<closest_object<<" "<<hit.t<<" " <<hit.object<<std::endl;
        	}
       
       vec3 normal = hit.object->Normal(intersection_point);
       vec3 same_side_normal = hit.ray_exiting?(-normal):normal;
       color = closest_object->material_shader->Shade_Surface(ray,intersection_point,same_side_normal,recursion_depth);
    }   
    return color;
    
}
