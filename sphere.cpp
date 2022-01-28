#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
    //ray: r(t) = e + tu
    //ray-sphere intersection: a = t^2,		b = 2u dot (e - x_c)t,		c = (e - x_c) dot (e - x_c) - r^2
    
    Hit hitobj {this, 0, part};
    vec3 e_xc = ray.endpoint - center;
    vec3 u = ray.direction;
    double a = dot(u, u);
    double b = 2 * dot(u, e_xc);
    double c = dot(e_xc, e_xc) - (radius * radius);

    // b^2 - 4ac = 0 -> one solution,		b^2 - 4ac > 0 -> two solutions, return smallest t > 0    
    double check = (b * b) - (4 * a * c);
    if (check == 0) {
	double t = ((-1 * b) + sqrt(check)) / (2 * a);
        if (t > small_t) {
	    hitobj.dist = t;
	}
    }
    else if (check > 0) {
	double t0 = ((-1 * b) + sqrt(check)) / (2 * a);
	double t1 = ((-1 * b) - sqrt(check)) / (2 * a);
	if (t0 > small_t && t1 > small_t) {
	    hitobj.dist = t0;
	    if (t1 < t0) {
		hitobj.dist = t1;
	    }
	}
    }

    return hitobj;
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    //TODO; // compute the normal direction
    normal = (point - center).normalized();
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
