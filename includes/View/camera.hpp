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
        UpdateTarget();
    }

    Vector3f GetLookAtDirection(){
        return Vector3f{position, GetTarget()};
    }

    void SetYaw(float y){

        if(y > 2 * M_PI){
            y -= 2*M_PI;
        }
        if(y < - 2 * M_PI){
            y += 2*M_PI;
        }
        yaw = y;

        UpdateTarget();
        
    }
    
    void SetPitch(float p){


        if(p > M_PI / 2){
            p = M_PI/2 - 0.001;
        }
        if(p < - M_PI / 2){
            p = - M_PI/2 + 0.001; 
        }        
        
        pitch = p;

        UpdateTarget();

    }

    float GetYawDegree(){
        return yaw * 180.0 / M_PI;
    }

    float GetPitchDegree(){
        return pitch * 180.0 / M_PI;
    }

    float GetYaw(){
        return yaw;
    }

    float GetPitch(){
        return pitch;
    }

};



}