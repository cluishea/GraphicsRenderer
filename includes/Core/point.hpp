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
            return Point2f{x,y};
        }

    };

}