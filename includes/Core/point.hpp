#pragma once

namespace gfx{

    /*
        2D points represented as integer values
    */
    struct Point2i{
        int x;
        int y;
    };

    /*
        2D points represented as floating point values
    */
    struct Point2f{
        float x;
        float y;

        float inv_z_depth = 0;

        Point2f(float x, float y):x(x), y(y){}

        Point2f(float x, float y, float z):x(x), y(y), inv_z_depth(z){}


        /*
            @brief Denormalizes the screen coordinates (-1 to 1) to screen pixel coordinates
        */
        void Denormalize(int screenWidth, int screenHeight){
            x = x * screenWidth / 2.0;
            y = y * screenHeight / 2.0;
        }

    };

    /*
        3D points represented as floating point values
    */
    struct Point3f{
        float x;
        float y;
        float z;

        operator Point2f(){
            return Point2f{x,y,1/z};
        }

        Point3f operator +(Point3f other){
            return Point3f{x+other.x, y+other.y, z+other.z};
        }

        Point3f operator/ (float a){
            return Point3f{x/a, y/a, z/a};
        }

    };

}