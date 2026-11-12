#pragma once

#include <View/camera.hpp>
#include <Utilities/input.hpp>

namespace gfx{

// Class for FPS implementation
class FPS{

private:
    Camera camera;
    Input& input;

    float FOV = 120;
    float z_near = 0.1, z_far = 100;

    float movementSpeed = 3.0f;
    float yawRotationSpeed = 30.0f * M_PI / 180.0;
    float pitchRotationSpeed = 25.0f * M_PI / 180.0;

public:
    FPS(Camera cam, Input& in) : camera(cam), input(in){

    }

    
    void Update(float dt){
        

        // Translation
        if(input.IsKeyDown(sf::Keyboard::Key::A)){
            camera.position.x -= movementSpeed*dt;
        }
        if(input.IsKeyDown(sf::Keyboard::Key::D)){
            camera.position.x += movementSpeed*dt;
        }

        if(input.IsKeyDown(sf::Keyboard::Key::W)){
            camera.position.z += movementSpeed*dt;
        }
        if(input.IsKeyDown(sf::Keyboard::Key::S)){
            camera.position.z -= movementSpeed*dt;
        }
        
        if(input.IsKeyDown(sf::Keyboard::Key::Space)){
            camera.position.y += movementSpeed*dt;
        }
        if(input.IsKeyDown(sf::Keyboard::Key::LShift)){
            camera.position.y -= movementSpeed*dt;
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