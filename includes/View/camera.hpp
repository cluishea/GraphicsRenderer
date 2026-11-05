#pragma once
#include <Core/point.hpp>

namespace gfx{

class Camera{
    // Later have all fov and stuff here when needs the whole movement thing too
private:
    Point3f position;

    // Stored as radian values
    float yaw, pitch;

    Point3f target;

    Vector3f upDirection;

    void UpdateTarget(){
        target.x = std::sinf(yaw) * std::cosf(pitch) + position.x;
        target.y = std::sinf(pitch) + position.y;
        target.z = std::cosf(yaw) * std::cosf(pitch) + position.z;
    }

public:
    Camera(Point3f pos = Point3f{0,0,0}, float y = 0.0, float p = 0.0, Vector3f upDir = {0,1,0}):position(pos), upDirection(upDir){

        yaw = M_PI * y / 180.0;
        pitch = M_PI * p / 180.0;

        UpdateTarget();
    }

    Point3f GetTarget(){
        return target;
    }

    Vector3f GetUpDirection(){
        return upDirection;
    }

    Point3f GetPosition(){
        return position;
    }

    void SetPosition(Point3f newPos){
        position = newPos;
    }

    void SetYaw(float y){
        yaw = y * M_PI / 180.0;
    }
    
    void SetPitch(float p){
        pitch = p * M_PI / 180.0;
    }

};



}