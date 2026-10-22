#pragma once
#include <Core/point.hpp>

namespace gfx{

struct Vector3f{

    float a[3];
    Vector3f(float a0, float a1, float a2){
        a[0] = a0;
        a[1] = a1;
        a[2] = a2;
    }

    static Vector3f Wrap2DPoint(Point2f point){
        return Vector3f{
            point.x, point.y, 1.0f
        };
    }

    Point2f Unwrap2DPoint() const{
        return Point2f{
            a[0], a[1]
        };
    }

};

}