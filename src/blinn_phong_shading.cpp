#include "blinn_phong_shading.h"
#include "first_hit.h"
#include <iostream>
#include <algorithm>
#define IA 0.1
#define EPSILON 1e-6

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
    Ray light_ray; 
    light_ray.origin = ray.origin + t * ray.direction;
    double max_t;
    int new_id;
    double new_t;
    Eigen::Vector3d new_n;
    Eigen::Vector3d rgb = Eigen::Vector3d(0, 0, 0);
    rgb += IA * objects[id]->material->ka;
    for (int i = 0; i < lights.size(); ++i) {
        lights[i]->direction(light_ray.origin, light_ray.direction, max_t); 
        if (first_hit(light_ray, EPSILON, objects, new_id, new_t, new_n) && new_t < max_t) {
            continue;
        }
        Eigen::Vector3d lambertian = (std::max(0.0, n.dot(light_ray.direction)) * objects[id]->material->kd);
        Eigen::Vector3d h = ((-1 * ray.direction) + light_ray.direction).normalized();
        Eigen::Vector3d specular = pow(std::max(0.0, n.dot(h)), objects[id]->material->phong_exponent) * objects[id]->material->ks;
        rgb += ((lambertian + specular).array() * lights[i]->I.array()).matrix();
    }
    return rgb.cwiseMin(1.0);
}
