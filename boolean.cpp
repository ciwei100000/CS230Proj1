#include "boolean.h"
#include <queue>
#include <map>

using namespace std;

struct comparator
{
	bool operator()(pair<Hit, Object*> const& a, pair<Hit, Object*> const& b) const
	{return a.first > b.first;}
};

void Booleanhit(const Ray& ray, Object* const object, 
				priority_queue<pair<Hit, Object*>, vector<pair<Hit,
				 Object*>>,comparator>& hit_queue);

// Determine if the ray intersects with the boolean of A and B.
bool Boolean::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    priority_queue<pair<Hit, Object*>, vector<pair<Hit, Object*>>,comparator > hit_queue;
    std::map<bool, bool> hit_position;
    bool if_hit = false;

    Booleanhit(ray, A, hit_queue);
    Booleanhit(ray, B, hit_queue);

    if(hit_queue.empty())
    {
    	return false;
    }

    hit_position[0] = 0; //Postion in A, 0:outside; 1: inside
    hit_position[1] = 0; //Postion in B, 0:outside; 1: inside

    while (!hit_queue.empty())
    {
    	auto hit_queue_i = hit_queue.top();
    	hit_queue.pop();
    	Hit hit = hit_queue_i.first;
    	Object* hitted_object = hit_queue_i.second; 
    	
    	
    	
    	if(false)
        {
        	std::cout<<this<<" queue hit: "<<hit.t<<" "<<hit.object<<" Bool Obj "<<hitted_object<<" queue size: "<<hit_queue.size()<<std::endl;
        }
    	
    	if(type == type_union)
    	{
    		if(!hit.t)
    		{
    			if(debug_pixel == true)
        		{
        			std::cout<<this<<" type_union O Hit"<<hit.t<<" "<<hit.object<<" A: "<<A<<" "<<hit_position[0]<<" B: "<<B<<" "<<hit_position[1]<<std::endl;
        		}
        		
    			hit_position[hitted_object == B] = 1;
    			hits.push_back(hit);
    			if_hit = true;
    			continue;
    		}
    		if(!hit_position[0]&&!hit_position[1])
    		{
    			if(debug_pixel == true)
        		{
        			std::cout<<this<<" type_union I Hit"<<hit.t<<" "<<hit.object<<" A: "<<A<<" "<<hit_position[0]<<" B: "<<B<<" "<<hit_position[1]<<std::endl;
        		}
    			hit_position[hitted_object == B] = 1;
    			hits.push_back(hit);
    			if_hit = true;
    			continue;
    		}

    		if(hit_position[hitted_object == B] && !hit_position[hitted_object == A])
    		{
    			if(debug_pixel == true)
        		{
        			std::cout<<this<<" type_union II Hit"<<hit.t<<" "<<hit.object<<" A: "<<A<<" "<<hit_position[0]<<" B: "<<B<<" "<<hit_position[1]<<std::endl;
        		}
    			hit_position[hitted_object == B] = 0;
    			hits.push_back(hit);
    			if_hit = true;
    			continue;
    		}
    	}

    	if (type == type_intersection)
    	{
    		if(!hit.t)
    		{
    			if(debug_pixel == true)
        		{
        			std::cout<<this<<" intercept case O Hit"<<hit.t<<" "<<hit.object<<" A: "<<A<<" "<<hit_position[0]<<" B: "<<B<<" "<<hit_position[1]<<std::endl;
        		}
        		
    			hit_position[hitted_object == B] = 1;
    			if (hit_position[hitted_object == A])
    			{
    				hits.push_back(hit);
    				if_hit = true;
    			}
    			continue;
    		}
    		
    		if(hit_position[0]&&hit_position[1])
    		{
    			if(debug_pixel == true)
        		{
        			std::cout<<this<<" intercept case I Hit"<<hit.t<<" "<<hit.object<<" A: "<<A<<" "<<hit_position[0]<<" B: "<<B<<" "<<hit_position[1]<<std::endl;
        		}
    			hit_position[hitted_object == B] = 0;
    			hits.push_back(hit);
    			if_hit = true;
    			continue;
    		}
    		if (!hit_position[hitted_object == B] && hit_position[hitted_object == A])
    		{
    			if(debug_pixel == true)
        		{
        			std::cout<<this<<" intercept case II Hit"<<hit.t<<" "<<hit.object<<" A: "<<A<<" "<<hit_position[0]<<" B: "<<B<<" "<<hit_position[1]<<std::endl;
        		}
    			hit_position[hitted_object == B] = !hit_position[hitted_object == B];
    			hits.push_back(hit);
    			if_hit = true;
    			continue;
    		}
    	}

    	if (type == type_difference)
    	{
    		if(!hit.t )
    		{
    			if(debug_pixel == true)
       			{
       				std::cout<<this<<" diff case O Hit"<<hit.t<<" "<<hit.object<<" A: "<<A<<" "<<hit_position[0]<<" B: "<<B<<" "<<hit_position[1]<<std::endl;
       			}
    			hit_position[hitted_object == B] = 1;
    			if (hit_position[0]&&!hit_position[1])
    			{
    				hits.push_back(hit);
    				if_hit = true;
    			}
    			continue;
    		}

    		if(hit_position[hitted_object == A] == (hitted_object == B))
    		{
   				if(debug_pixel == true)
       			{
       				std::cout<<this<<" diff case I Hit"<<hit.t<<" "<<hit.object<<" A: "<<A<<" "<<hit_position[0]<<" B: "<<B<<" "<<hit_position[1]<<std::endl;
       			}
   				hit_position[hitted_object == B] = !hit_position[hitted_object == B];
   				hits.push_back(hit);
   				if_hit = true;
   				continue;
   			}
   		}
   		
   		if(debug_pixel == true)
        {
        	std::cout<<this<<" Pass: "<<hit.t<<" "<<hit.object<<" A: "<<A<<" "<<hit_position[0]<<" B: "<<B<<" "<<hit_position[1]<<std::endl;
        }
        
   		hit_position[hitted_object == B] = !hit_position[hitted_object == B];
   		
   	}	


    return if_hit;  
}

// This should never be called.
vec3 Boolean::Normal(const vec3& point) const
{
    assert(false);
    return vec3();
}

//The pointer only used to pass address of Boolean::A or Boolean::B
void Booleanhit(const Ray& ray, Object* const object, 
				priority_queue<pair<Hit, Object*>,vector<pair<Hit,
				 Object*>>,comparator>& hit_queue) 

{
	std::vector<Hit> hit_tmp;
    std::vector<Hit>::iterator hit_tmp_iter;
    if(object->Intersection(ray,hit_tmp))
    {
    
    	if(false)
    	{
        	std::cout<<" hitcheck: "<<hit_tmp.size()<<std::endl;
    	}
    	
    	hit_tmp_iter = hit_tmp.begin();
    	
    	while(hit_tmp_iter != hit_tmp.end())
    	{
   			hit_queue.push(std::make_pair(*hit_tmp_iter, object));
    		++hit_tmp_iter;
    	}
    }
    return;
}
