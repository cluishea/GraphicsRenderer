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

    /*
        @brief Returns the point camera is pointing at
    */
    Point3f GetTarget(){
        return target;
    }

    /*
        @brief Returns the world up direction
    */
    Vector3f GetUpDirection(){
        return upDirection;
    }

    /*
        @brief Returns the position of the camera
    */
    Point3f GetPosition(){
        return position;
    }

    /*
        @brief Set the position of the camera and update the target
        @params[in] newPos New Position of the camera (Point3f)
    */
    void SetPosition(Point3f newPos){
        position = newPos;
        UpdateTarget();
    }

    /*
        @brief Returns the ditection in which camera is pointing at
    */
    Vector3f GetLookAtDirection(){
        return Vector3f{position, GetTarget()};
    }

    /*
        @brief Sets the Yaw of camera
        @param[in] y New yaw (in radians)
    */
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
    
    /*
        @brief Sets the Pitch of camera
        @param[in] p New pitch (in radians)
    */
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

    /*
        @brief Returns the Yaw of camera (in degree)
    */
    float GetYawDegree(){
        return yaw * 180.0 / M_PI;
    }

    /*
        @brief Returns the Pitch of camera (in degree)
    */
    float GetPitchDegree(){
        return pitch * 180.0 / M_PI;
    }

    /*
        @brief Returns the Yaw of camera (in radians)
    */
    float GetYaw(){
        return yaw;
    }

    /*
        @brief Returns the Pitch of camera (in radians)
    */
    float GetPitch(){
        return pitch;
    }

};



}