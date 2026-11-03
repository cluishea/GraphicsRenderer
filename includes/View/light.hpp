#pragma once
#include <Math/vector3.hpp>

namespace gfx
{
    // Light structure for representing light sources in 3D
    struct Light{

        Vector3f direction;  

        // Intensity is set to 0.1 initially for ambient lighting
        float intensity;

        Light(Vector3f dir = Vector3f{0,0,0}, float inten = 0.1f):direction(dir), intensity(inten){
            if(intensity > 1.0 || intensity < 0.0f){
                intensity = 0.1f;
            }
            direction.Normalize();
        }

    };



} 
