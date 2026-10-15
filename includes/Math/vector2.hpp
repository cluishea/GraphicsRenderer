#pragma once
#include <Core/point.hpp>

/* 
    Represents a 2D vector
    Holds the x and y displacement of the vector
*/

namespace gfx{

    struct Vector2i
    {
        float x;
        float y;

        Vector2i(float x_, float y_){
            x = x_;
            y = y_;
        }

        Vector2i(Point2i start, Point2i end){
            x = end.x - start.x;
            x = end.y - start.y;
        }

        Vector2i operator+(Vector2i other) const{
            return {x+other.x, y+other.y};
        }  

        Vector2i operator-(Vector2i other) const{
            return {x-other.x, y-other.y};
        }  

        Vector2i operator*(float scalar) const{
            return {scalar*x,scalar*y};
        }

        float Cross(Vector2i other) const{
            return x * other.y - y * other.x;
        }

    };
}