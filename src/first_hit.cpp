#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
    bool hitFound = false;   
    double closestHit = 0.0;   
    double hit_t;     
    Eigen::Vector3d hit_n;      
    for (int i = 0; i < objects.size(); ++i) {
        bool isHit = objects[i]->intersect(ray, min_t, hit_t, hit_n);
        if (isHit) {
            if (!hitFound || hit_t < closestHit) {
                hit_id = i;
                t = hit_t;
                n = hit_n;
                closestHit = hit_t;
            }
            hitFound = true;
        }
    }
    return hitFound;
}

