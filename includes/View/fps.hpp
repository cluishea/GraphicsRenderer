#pragma once'

#include <View/camera.hpp>
#include <Utilities/input.hpp>

namespace gfx{

// Class for FPS implementation
class FPS{

private:
    Camera camera;
    Input& input;


public:
    FPS(Camera cam, Input& in) : camera(cam), input(in){

    }

    void Update(float dt){
        
    }


};


}