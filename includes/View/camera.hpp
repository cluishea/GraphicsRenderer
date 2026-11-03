#pragma once
#include <Core/point.hpp>

namespace gfx{

class Camera{
    // Later have all fov and stuff here when needs the whole movement thing too
private:
    Point3f position;

public:
    Camera(Point3f pos = Point3f{0,0,0}):position(pos){}

    Point3f GetPosition(){
        return position;
    }

};



}