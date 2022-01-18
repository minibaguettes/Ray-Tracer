#include "plane.h"
#include "ray.h"
#include <cfloat>
#include <limits>

// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
Hit Plane::Intersection(const Ray& ray, int part) const
{
    //TODO;
    // ray: r(t) = e + tu
    // ray-plane intersection: (u dot n)t = (p - e) dot n

    Hit hitobj {this, 0, part};
    vec3 e = ray.endpoint;
    vec3 u = ray.direction;
    
    // u dot n != 0, then t = ((p-e) dot n) / u dot n, if t > small_t
    if (dot(u, normal) != 0) {
	double t = dot((x1 - e), normal) / dot(u, normal);
	if (t > small_t) {
	    hitobj.dist = t;
	}
    } 

    return hitobj;
}

vec3 Plane::Normal(const vec3& point, int part) const
{
    return normal;
}

// There is not a good answer for the bounding box of an infinite object.
// The safe thing to do is to return a box that contains everything.
Box Plane::Bounding_Box(int part) const
{
    Box b;
    b.hi.fill(std::numeric_limits<double>::max());
    b.lo=-b.hi;
    return b;
}
