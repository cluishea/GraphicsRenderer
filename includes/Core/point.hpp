#pragma once
#include <iostream>

namespace gfx{

    struct Point2i{
        int x;
        int y;
    };

    struct Point2f{
        float x;
        float y;

        void Denormalize(int screenWidth, int screenHeight){
            std::cout << screenWidth << " " << screenHeight << x << " " << y << " ";
            x = x * screenWidth / 2.0;
            y = y * screenHeight / 2.0;
            std::cout << " " << x << " " << y << std::endl;
        }

    };

    struct Point3f{
        float x;
        float y;
        float z;

        operator Point2f(){
            return Point2f{x,y};
        }

    };

}