#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Eigen>
#include <Eigen/Dense>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
    Eigen::Vector3d c = std::get<0>(this->corners); 
    Eigen::Vector3d t1 = std::get<1>(this->corners) - c;
    Eigen::Vector3d t2 = std::get<2>(this->corners) - c;
    Eigen::Matrix3d M;
    M << t1, t2, ray.direction * -1;
    if (M.determinant() == 0) {
        return false;
    }        
    Eigen::Vector3d values = M.inverse() * (ray.origin - c);    
    if (values[0] < 0 || values[1] < 0 || values[0] + values[1] > 1 || values[2] < min_t){
        return false;
    }
    else {
        t = values[2];
        n = t1.cross(t2).normalized();
        return true;
    }
    
}


