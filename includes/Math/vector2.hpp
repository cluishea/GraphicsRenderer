#pragma once
#include <Core/point.hpp>

/* 
    Represents a 2D vector
    Holds the x and y displacement of the vector
*/

namespace gfx{

    struct Vector2f
    {
        float x;
        float y;

        Vector2f(float x_, float y_){
            x = x_;
            y = y_;
        }

        Vector2f(Point2f start, Point2f end){
            x = end.x - start.x;
            y = end.y - start.y;
        }

        Vector2f operator+(Vector2f other) const{
            return {x+other.x, y+other.y};
        }  

        Vector2f operator-(Vector2f other) const{
            return {x-other.x, y-other.y};
        }  

        Vector2f operator*(float scalar) const{
            return {scalar*x,scalar*y};
        }

        Vector2f operator-() const{
            return {-x,-y};
        }

        float Cross(Vector2f other) const{
            return x * other.y - y * other.x;
        }
    };
}