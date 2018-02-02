#include "boolean.h"
#include <map>


void Booleanhit(const Ray& ray, Object* const object, std::map<Hit,Object*>& hit_map);
// Determine if the ray intersects with the boolean of A and B.
bool Boolean::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    std::map<Hit,Object*> hit_map;
    std::map<Hit,Object*>::iterator hit_map_i;
    std::map<bool, bool> hit_position;
    bool if_hit = false;

    Booleanhit(ray, A, hit_map);
    Booleanhit(ray, B, hit_map);

    if(hit_map.empty())
    {
    	return false;
    }


    hit_position[0] = 0; //Postion in A, 0:outside; 1: inside
    hit_position[1] = 0; //Postion in B, 0:outside; 1: inside

    for (hit_map_i = hit_map.begin();hit_map_i != hit_map.end();++hit_map_i)
    {
    	if(type == type_union)
    	{
    		if(!hit_position[0]&&!hit_position[1])
    		{
    			hit_position[hit_map_i->second == B] = 1;
    			hits.push_back(hit_map_i->first);
    			if_hit = true;
    			if(debug_pixel == true)
        		{
        			std::cout<<this<<" type_union I Hit"<<hit_map_i->first.t<<" "<<hit_map_i->first.object<<std::endl;
        		}
    			continue;
    		}

    		if(hit_position[hit_map_i->second == B] && !hit_position[hit_map_i->second == A])
    		{
    			hit_position[hit_map_i->second == B] = 0;
    			hits.push_back(hit_map_i->first);
    			if_hit = true;
    			if(debug_pixel == true)
        		{
        			std::cout<<this<<" type_union II Hit"<<hit_map_i->first.t<<" "<<hit_map_i->first.object<<std::endl;
        		}
    			continue;
    		}
    	}

    	if (type == type_intersection)
    	{
    		if(hit_position[0]&&hit_position[1])
    		{
    			hit_position[hit_map_i->second == B] = 0;
    			hits.push_back(hit_map_i->first);
    			if_hit = true;
    			if(debug_pixel == true)
        		{
        			std::cout<<"intercept case I Hit"<<hit_map_i->first.t<<" "<<hit_map_i->first.object<<std::endl;
        		}
    			continue;
    		}
    		if (!hit_position[hit_map_i->second == B] && hit_position[hit_map_i->second == A])
    		{
    			hit_position[hit_map_i->second == B] = 0;
    			hits.push_back(hit_map_i->first);
    			if_hit = true;
    			if(debug_pixel == true)
        		{
        			std::cout<<"intercept case II Hit"<<hit_map_i->first.t<<" "<<hit_map_i->first.object<<std::endl;
        		}
    			continue;
    		}
    	}

    	if (type == type_difference)
    	{

    		if(hit_position[hit_map_i->second == A] == (hit_map_i->second == B))
    		{

   				if(debug_pixel == true)
       			{
       				std::cout<<this<<" diff case I Hit"<<hit_map_i->first.t<<" "<<hit_map_i->first.object<<" A: "<<A<<" "<<hit_position[0]<<" B: "<<B<<" "<<hit_position[1]<<std::endl;
       			}
   				hit_position[hit_map_i->second == B] = !hit_position[hit_map_i->second == B];
   				hits.push_back(hit_map_i->first);
   				if_hit = true;
   				continue;
   			}
   		}
   		hit_position[hit_map_i->second == B] = !hit_position[hit_map_i->second == B];
   	}	


    return if_hit;  
}

// This should never be called.
vec3 Boolean::Normal(const vec3& point) const
{
    assert(false);
    return vec3();
}

void Booleanhit(const Ray& ray, Object* const object, std::map<Hit,Object*>& hit_map) //The pointer only used to pass address of Boolean::A or Boolean::B
{
	std::vector<Hit> hit_tmp;
    std::vector<Hit>::iterator hit_tmp_iter;

    if(object->Intersection(ray,hit_tmp))
    {
    	hit_tmp_iter = hit_tmp.begin();
    	while(hit_tmp_iter != hit_tmp.end())
    	{
   			hit_map[*hit_tmp_iter] = object;
    		++hit_tmp_iter;
    	}
    }
    return;
}
