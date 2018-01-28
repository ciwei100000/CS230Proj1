#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"


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
    std:vector<Hit> hits;
    
    if (objects.empty)
    {
        return 0;
    }
    
    for (std::vector<Object*>::const_iterator ob = objects.begin(); ob != objects.end ; ++ob)
    {
        *ob->Intersection(ray, hits);
    }
    
    if (!hits.empty)
    {
        vector<Object*>::iterator closest_hit = *std::min_element(hits.begin(),hits.end());
        int closest_hit_position = std:distance(hits.begin(), closest_hit);
        hit = *closest_hit;
        return objects[closest_hit_position];
        
    }
    
    return 0;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    vec3 world_postition_pixel = Camera.World_Position(pixel_index);
    vec3 direction_input = world_postition_pixel - camera.position;
    Ray ray(camera.position, direction_input); // TODO: set up the initial view ray here
    vec3 color=Cast_Ray(ray,1);
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
    vec3 color;

    // determine the color here

    return color;
}
