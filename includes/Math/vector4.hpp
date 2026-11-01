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

    static Vector4f Wrap3DPoint(Point3f point, float weight = 1.0f){
        return Vector4f{
            point.x * weight, point.y * weight, point.z * weight, weight
        };
    }

    Point3f Unwrap3DPoint(){
        return Point3f{
            a[0] / a[4],
            a[1] / a[4],
            a[2] / a[4]           
        };
    }

};

}