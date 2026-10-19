#pragma once
#include <Math/vector4.hpp>
#include <array>

namespace gfx{
    
// Struct for 4x4 matrix and some transforms implementation
struct Matrix4x4 {

    std::array<float,16> a;

    Matrix4x4 operator*(Matrix4x4 other){
        std::array<float,16> result;
        for(int i = 0; i<4; i++){
            for(int j = 0; j<4; j++){
                for(int k = 0; k<4; k++){
                    result[4*i + j] += a[4*i+k] * other.a[4*k + j];
                }
            }
        }
    }

};






}
