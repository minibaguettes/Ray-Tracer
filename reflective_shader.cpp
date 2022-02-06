#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
TODO;
    vec3 color;

    vec3 c = shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);
    color = (1 - reflectivity) * c;

    if (recursion_depth < world.recursion_depth_limit) {

        // r = -2(dot(n, u) * n) + u	r = reflected direction, u = incoming ray direction
        vec3 r = (-2 * dot(normal, ray.direction) * normal) + ray.direction;
        Ray refl(intersection_point, r);

        // color = (1 - k) * color + k * cast_ray(reflected ray)	where k = reflectivity 
        vec3 cr = world.Cast_Ray(refl, recursion_depth + 1);
	color += reflectivity * cr;
    }
    return color;
}
