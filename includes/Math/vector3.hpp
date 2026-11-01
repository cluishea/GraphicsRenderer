#pragma once
#include <math.h>
#include <Core/point.hpp>


namespace gfx{

struct Vector3f{

    float a[3];
    Vector3f(float a0, float a1, float a2){
        a[0] = a0;
        a[1] = a1;
        a[2] = a2;
    }

    Vector3f operator+(Vector3f other) const{
        return {a[0]+other.a[0], a[1]+other.a[1], a[2]+other.a[2]};
    }  

    Vector3f operator-(Vector3f other) const{
        return {a[0]-other.a[0], a[1]-other.a[1], a[2]-other.a[2]};
    }   

    Vector3f operator*(float scalar) const{
        return {scalar*a[0],scalar*a[1], scalar*a[2]};
    }

    Vector3f operator/(float scalar) const{
        return {a[0]/scalar, a[1]/scalar, a[2]/scalar};;
    }

    static Vector3f Wrap2DPoint(Point2f point, float weight = 1.0f){
        return Vector3f{
            point.x * weight, 
            point.y * weight,
            weight 
        };
    }

    Point2f Unwrap2DPoint() const{
        return Point2f{
            a[0] / a[2], 
            a[1] / a[2]
        };
    }

    float Magnitude() const{
        return std::powf(std::pow(a[0],2.0f) + std::pow(a[1],2.0f) + std::pow(a[2],2.0f),0.5f);
    }

    void Normalize(){
        float magnitude = Magnitude();
        a[0] /= magnitude;
        a[1] /= magnitude;
        a[2] /= magnitude;
    }

    float Dot(Vector3f& other) const{
        return a[0] * other.a[0] + a[1] * other.a[1] + a[2] * other.a[2];
    }   

    Vector3f Cross(Vector3f& other) const{
        return Vector3f{
            other.a[0],
            0,
            0
        };
    }


};

}

// TODO :
// Normal, Cross, Check dot, Camera class, 