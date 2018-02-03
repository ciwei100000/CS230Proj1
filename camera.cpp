#include "camera.h"
#include <random>
#include <chrono>

Camera::Camera()
    :colors(0),antialiasing(0)
{
}

Camera::~Camera()
{
    delete[] colors;
}

vec2 Rand_Point(vec2& min, vec2 & max);
double fRand(double fMin, double fMax);

void Camera::Position_And_Aim_Camera(const vec3& position_input,
    const vec3& look_at_point,const vec3& pseudo_up_vector)
{
    position=position_input;  //camera postion
    look_vector=(look_at_point-position).normalized();
    horizontal_vector=cross(look_vector,pseudo_up_vector).normalized();
    vertical_vector=cross(horizontal_vector,look_vector).normalized();
}

void Camera::Focus_Camera(double focal_distance,double aspect_ratio,
    double field_of_view)
{
    film_position=position+look_vector*focal_distance;
    double width=2.0*focal_distance*tan(.5*field_of_view);
    double height=width/aspect_ratio;
    image_size=vec2(width,height);
}

void Camera::Set_Resolution(const ivec2& number_pixels_input)
{
    number_pixels=number_pixels_input;
    if(colors) delete[] colors;
    colors=new Pixel[number_pixels[0]*number_pixels[1]];
    min=-0.5*image_size;
    max=0.5*image_size;
    pixel_size = image_size/vec2(number_pixels);
}

// Find the world position of the input pixel
std::vector<vec3> Camera::World_Position(const ivec2& pixel_index)
{
    std::vector<vec3> result;
    vec3 tmp_world_position;
    uint v,h;
    if (antialiasing > 0)
    {   	
    	if (antialiasing % 2)
    	{
    		v = 1<<(antialiasing>>1);
    		h = v<<1;
    	}
    	else
    	{
    		h = 1<<(antialiasing>>1);
    		v = h;
    	}
    	
    	
    	if (debug_pixel == true)
    	{
    		std::cout<<"antialiasing: "<<antialiasing<<" vertical:"<<v<<" honrizon: "<<h<<std::endl;
    	}
    	
    	vec2 rendered_pixel_size = pixel_size/vec2(h,v); 
    	for (unsigned int j = 0; j < v; j += 1)
    	{
    		for (unsigned int i = 0; i < h; i += 1)
    		{
    			vec2 rendered_pixel_min(i,j);
    			vec2 rendered_pixel_max(i+1,j+1);
    			vec2 position_on_film = Rand_Point(rendered_pixel_min, rendered_pixel_max)*
    								  rendered_pixel_size + min + 
    								  vec2(pixel_index)*pixel_size;
    			    
    			result.push_back(position_on_film[0] * horizontal_vector + position_on_film[1] * vertical_vector + film_position);
    		}    		
    	}
    	return result;	  	
    }
    // TODO
    vec2 position_on_film = Cell_Center(pixel_index);
    result.push_back(position_on_film[0] * horizontal_vector + position_on_film[1] * vertical_vector + film_position);
    return result;
}

vec2 Rand_Point(vec2& min, vec2 & max)
{
	vec2 result;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::uniform_real_distribution<double>::param_type v(min[0],max[0]);
	std::uniform_real_distribution<double>::param_type h(min[1],max[1]);
	std::default_random_engine generator (seed);
	std::uniform_real_distribution<double> distribution (v);
	result[0] = distribution(generator);
	distribution.param(h);
	result[1] = distribution(generator);
	if (debug_pixel == true)
    {
    	std::cout<<"random generator: "<<result<<std::endl;
    }
	return result;
}

