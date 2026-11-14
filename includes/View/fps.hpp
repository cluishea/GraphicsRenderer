#pragma once

#include <View/camera.hpp>
#include <Utilities/input.hpp>

namespace gfx{

// Class for FPS implementation
class FPS{

private:
    Camera camera;
    Input& input;

    float FOV = 90;
    float z_near = 0.1, z_far = 100;

    float movementSpeed = 3.0f;
    float yawRotationSpeed = 30.0f * M_PI / 180.0;
    float pitchRotationSpeed = 25.0f * M_PI / 180.0;

public:
    FPS(Camera cam, Input& in) : camera(cam), input(in){

    }

    
    void Update(float dt){
      
       Vector3f displacement{0,0,0};
       Vector3f lookAtDirection = camera.GetLookAtDirection();
       lookAtDirection.a[1] = 0;
       lookAtDirection.Normalize();


       // Left direction calculation
       Matrix3x3 rotateleft = Matrix3x3::Rotate(90);
       Point2f temp = Point2f{lookAtDirection.a[0], lookAtDirection.a[2]};
       Vector3f leftDirection = Vector3f::Wrap2DPoint(temp) * rotateleft;
       leftDirection = Vector3f{leftDirection.a[0], 0, leftDirection.a[1]};
      
       // Translation
       if(input.IsKeyDown(sf::Keyboard::Key::W)){
           displacement = displacement + lookAtDirection;
       }
       if(input.IsKeyDown(sf::Keyboard::Key::S)){
           displacement = displacement - lookAtDirection;
       }


       if(input.IsKeyDown(sf::Keyboard::Key::A)){
           displacement = displacement + leftDirection;
       }
       if(input.IsKeyDown(sf::Keyboard::Key::D)){
           displacement = displacement - leftDirection;
       }
      
       if(input.IsKeyDown(sf::Keyboard::Key::Space)){
           displacement.a[1] += 1.f;
       }
       if(input.IsKeyDown(sf::Keyboard::Key::LShift)){
           displacement.a[1] -= 1.f;
       }


       // Yaw
       if(input.IsKeyDown(sf::Keyboard::Key::Left)){
           camera.yaw -= yawRotationSpeed * dt;
       }
       if(input.IsKeyDown(sf::Keyboard::Key::Right)){
           camera.yaw += yawRotationSpeed * dt;
       }


       // Pitch
       if(input.IsKeyDown(sf::Keyboard::Key::Up)){
           camera.pitch += pitchRotationSpeed * dt;
       }
       if(input.IsKeyDown(sf::Keyboard::Key::Down)){
           camera.pitch -= pitchRotationSpeed * dt;
       }


       displacement.Normalize();
       displacement = displacement * movementSpeed * dt;


       camera.SetPosition(camera.GetPosition() + displacement);
       camera.UpdateTarget();
   }


    
    
    float GetFOV(){
        return FOV;
    }
    float GetZNear(){
        return z_near;
    }
    float GetZFar(){
        return z_far;
    }

    Camera GetCamera(){
        return camera;
    }


};


}

// Implement the movement logic properly based on where looking and also make functions for right up etc to make everything a little easier