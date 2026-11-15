#pragma once
#include <Core/point.hpp>

namespace gfx{

struct Vector4f{

    float a[4];
    Vector4f(float a0, float a1, float a2, float a3){
        a[0] = a0;
        a[1] = a1;
        a[2] = a2;
        a[3] = a3;
    }

    /*
        @brief Wraps the 3D point into a Vector3f
        @param[in] 3D point
        @param[in] weight Temporary value for homogenous transform (Default = 1)
        @return Vector4f containing the 3D point and homogenous factor
    */
    static Vector4f Wrap3DPoint(Point3f point, float weight = 1.0f){
        return Vector4f{
            point.x * weight, point.y * weight, point.z * weight, weight
        };
    }

    /*
        @brief Unwraps the Vector3f into a 3D point
        @return 3D point adjusted after homogenous division
    */
    Point3f Unwrap3DPoint(){
        return Point3f{
            a[0] / a[3],
            a[1] / a[3],
            a[2] / a[3]           
        };
    }

};

}