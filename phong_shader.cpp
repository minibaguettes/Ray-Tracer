#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray, const vec3& intersection_point, const vec3& normal, int recursion_depth) const
{
    // ambient = Ra * La
    vec3 color = world.ambient_color * world.ambient_intensity * color_ambient;
    
    for (unsigned int i = 0; i < world.lights.size(); i++) {	// iterate thru each existing light
        vec3 currlight = world.lights[i]->position - intersection_point;
	
	if (world.enable_shadows) {	// check for shadow
	    Ray currshadowray(intersection_point, currlight.normalized());	// endpoint = intersection point
	    Hit shadowhit = world.Closest_Intersection(currshadowray);	// see if object is blocking light source
 	    if (shadowhit.object != NULL) {	// if object detected
	        double lightdist = currlight.magnitude();
		if (shadowhit.dist < lightdist) {	// if object blocking, skip diffuse and spectral
		    continue;
		}
	    }
	}
	vec3 L = (world.lights[i]->Emitted_Light(ray.direction)) / currlight.magnitude_squared();
	vec3 n = normal;
	vec3 l = currlight.normalized();

	// diffuse = Rd * Ld * max( dot(n, l), 0)
	double dotnl = dot(n, l);
	vec3 diffcolor = color_diffuse * L * std::max(dotnl, 0.0);

	// specular = Rs * Ls * max( dot(v, r), 0)^a
	vec3 v = -ray.direction.normalized();	// v = negative of view ray 
	vec3 r = ((2 * dot(n, l) * n) - l),normalized();	// r = reflection of l about n
	double dotvr = dot(v, r);
	vec3 specolor = color_specular * L * pow(std::max(dotvr, 0.0), specular_power);

	color += diffcolor + specolor;
    }

    return color;
}
