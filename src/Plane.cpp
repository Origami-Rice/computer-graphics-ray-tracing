#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
    double den = this->normal.dot(ray.direction);   
    if (den == 0) {
        return false;
    }
    double num = this->normal.dot(this->point) - this->normal.dot(ray.origin);    
    t = num / den;
    if (t >= min_t) {
        n = this->normal.normalized();    
        return true;
    }
    else {
        return false;
    }
      
}

