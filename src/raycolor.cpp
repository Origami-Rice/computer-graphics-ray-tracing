#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"
#define OFFSET 1e-4
#define DEPTH 10

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
    rgb = Eigen::Vector3d(0, 0, 0); 
    Eigen::Vector3d n;
    bool hit;
    int id;
    double t;
    

    if (first_hit(ray, min_t, objects, id, t, n)) {
        rgb = blinn_phong_shading(ray, id, t, n, objects, lights);  
        if (num_recursive_calls < DEPTH && !objects[id]->material->km.isZero(OFFSET)) {
            Ray reflected_ray;
            Eigen::Vector3d color;
            reflected_ray.origin = ray.origin + t * ray.direction;
            reflected_ray.direction = reflect(ray.direction, n);
            if (raycolor(reflected_ray, OFFSET, objects, lights, num_recursive_calls + 1, color)) {
                rgb += (objects[id]->material->km.array() * color.array()).matrix();
            }
        }
        return true; 
    }
    else {
        return false; 
    }
}
