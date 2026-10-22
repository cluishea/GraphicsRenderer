#pragma once
#include <Math/vector3.hpp>
#include <array>
#include <math.h>

namespace gfx{

// Struct for 3x3 matrix and some transforms implementation
struct Matrix3x3 {

    std::array<float,9> a;

    // Zero initialization
    Matrix3x3(){
        a = std::array<float,9>{};
    }

    Matrix3x3(const std::array<float,9>& arr):a(arr){

    }

    Matrix3x3(const std::array<float,3>& r1, const std::array<float,3>& r2, const std::array<float,3>& r3){
        a[0] = r1[0];
        a[1] = r1[1];
        a[2] = r1[2];
        a[3] = r2[0];
        a[4] = r2[1];
        a[5] = r2[2];
        a[6] = r3[0];
        a[7] = r3[1];
        a[8] = r3[2];
    }

    Matrix3x3 operator*(Matrix3x3 other){
        std::array<float,9> result;
        for(int i = 0; i<3; i++){
            for(int j = 0; j<3; j++){
                for(int k = 0; k<3; k++){
                    result[3*i + j] += a[3*i+k] * other.a[3*k + j];
                }
            }
        }
        return Matrix3x3{result};
    }
    
    // Translation functions implemented as homogenous coordinates

    // Translate function
    static Matrix3x3 Translate(float tx, float ty){
        return Matrix3x3{
            {
                1, 0, 0,
                0, 1, 0,
                tx, ty, 1
            }
        };
    }

    // Scaling function
    static Matrix3x3 Scale(float sx, float sy){
        return Matrix3x3{
            {
                sx, 0, 0,
                0, sy, 0,
                0, 0, 1
            }
        };
    }

    // Rotation function (Anticlockwise)
    static Matrix3x3 Rotate(float angle){
        float radianAngle = M_PI * angle / 180.0;
        float sine = std::sinf(radianAngle);
        float cosine = std::cosf(radianAngle);

        return Matrix3x3{
            {
                cosine, sine, 0, 
                -sine, cosine, 0,
                0, 0, 1
            }
        };
    }


};

inline Vector3f operator*(Vector3f vec, Matrix3x3 mat){
    return Vector3f{
        vec.a[0]*mat.a[0] + vec.a[1]*mat.a[3] + vec.a[2]*mat.a[6],
        vec.a[0]*mat.a[1] + vec.a[1]*mat.a[4] + vec.a[2]*mat.a[7],
        vec.a[0]*mat.a[2] + vec.a[1]*mat.a[5] + vec.a[2]*mat.a[8]
    };
}



}