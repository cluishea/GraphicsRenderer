#pragma once
#include <Math/vector4.hpp>
#include <array>
#include <math.h>

namespace gfx{
    
// Struct for 4x4 matrix and some transforms implementation
struct Matrix4x4 {

    std::array<float,16> a{};

    // Zero initialization
    Matrix4x4(){
        a = std::array<float,16>{};
    }

    Matrix4x4(const std::array<float,16>& arr):a(arr){

    }

    Matrix4x4(const std::array<float,4>& r1, const std::array<float,4>& r2, const std::array<float,4>& r3, const std::array<float,4>& r4){
        a[0] = r1[0];
        a[1] = r1[1];
        a[2] = r1[2];
        a[3] = r1[3];
        a[4] = r2[0];
        a[5] = r2[1];
        a[6] = r2[2];
        a[7] = r2[3];
        a[8] = r3[0];
        a[9] = r3[1];
        a[10] = r3[2];
        a[11] = r3[3];
        a[12] = r4[0];
        a[13] = r4[1];
        a[14] = r4[2];
        a[15] = r4[3];
    }


    Matrix4x4 operator*(Matrix4x4 other){
        std::array<float,16> result;
        for(int i = 0; i<4; i++){
            for(int j = 0; j<4; j++){
                for(int k = 0; k<4; k++){
                    result[4*i + j] += a[4*i+k] * other.a[4*k + j];
                }
            }
        }
        return Matrix4x4{result};
    }

    // Perspective projection transform, outputs the normalized 2D coordinates in range -1 to 1 when multiplied by a normalized 3D point (Vector4)
    static Matrix4x4 PerspectiveProjection(float aspectRatio, float FOV, float z_near, float z_far){
        /*
            aspectRatio = Screen width / Screen height
            FOV = Field of view
            z_near = Near clipping plane
            z_far = Far clipping plane
        */

        float q = z_far / (z_far - z_near);
        FOV = FOV * M_PI / 180.0f;
        float fovAdjust = 1 / std::tanf(FOV/2);

        return Matrix4x4{{
            fovAdjust/aspectRatio, 0.f, 0.f, 0.f, 
            0.f, fovAdjust, 0.f, 0.f, 
            0.f, 0.f, q, 1.f,
            0.f, 0.f, - q * z_near, 0.f
        }};
    }

    // Scaling transform
    static Matrix4x4 Scale(float sx, float sy, float sz){
        return Matrix4x4{
            {
                sx, 0, 0, 0,
                0, sy, 0, 0,
                0, 0, sz, 0, 
                0, 0, 0, 1
            }
        };
    }

    // Translation transform
    static Matrix4x4 Translate(float tx, float ty, float tz){
        return Matrix4x4{
            {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                tx, ty, tz, 1
            }
        };
    }

    // Rotation about the x axis
    static Matrix4x4 RotateXAxis(float angle){
        angle = M_PI * angle / 180.0f;
        float sine = std::sinf(angle);
        float cosine = std::cosf(angle);
        return Matrix4x4{
            {
                1, 0, 0, 0,
                0, cosine, sine, 0,
                0, -sine, cosine, 0, 
                0, 0, 0, 1

            }
        };
    }
    static Matrix4x4 RotateYAxis(float angle){
        angle = M_PI * angle / 180.0f;
        float sine = std::sinf(angle);
        float cosine = std::cosf(angle);
        return Matrix4x4{
            {
                cosine, 0, sine, 0,
                0, 1, 0, 0,
                -sine , 0, cosine, 0, 
                0, 0, 0, 1

            }
        };
    }

    static Matrix4x4 RotateZAxis(float angle){
        angle = M_PI * angle / 180.0f;
        float sine = std::sinf(angle);
        float cosine = std::cosf(angle);
        return Matrix4x4{
            {
                cosine, sine, 0, 0, 
                -sine, cosine, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            }
        };
    }

    // This uses z+ as forward
    // Puts the world coordinate into the new coordinates, specified by the forward direction and translated into the eye position
    static Matrix4x4 PointAt(Point3f eyePoint, Point3f targetPoint, Vector3f upDirection ){
        
        Vector3f forward{eyePoint, targetPoint};
        forward.Normalize();

        Vector3f up = upDirection - forward * upDirection.Dot(forward);
        up.Normalize();

        Vector3f right = up.Cross(forward);
        right.Normalize();
        
        return Matrix4x4{
            {
                right.a[0], right.a[1], right.a[2], 0,
                up.a[0], up.a[1], up.a[2], 0,
                forward.a[0], forward.a[1], forward.a[2], 0,
                eyePoint.x, eyePoint.y, eyePoint.z, 1
            }
        };
    }


    static Matrix4x4 LookAt(Point3f eyePoint, Point3f targetPoint, Vector3f upDirection){

        Vector3f forward{eyePoint, targetPoint};
        forward.Normalize();

        Vector3f up = upDirection - forward * upDirection.Dot(forward);
        up.Normalize();

        Vector3f right = up.Cross(forward);
        right.Normalize();

        Vector3f eye {eyePoint};

        return Matrix4x4{
            {
                right.a[0], up.a[0], forward.a[0], 0, 
                right.a[1], up.a[1], forward.a[1], 0,
                right.a[2], up.a[2], forward.a[2], 0,
                - eye.Dot(right), -eye.Dot(up), -eye.Dot(forward), 1
            }
        };
    }

};





inline Vector4f operator*(Vector4f vec, Matrix4x4 mat){


    return Vector4f{
        vec.a[0]*mat.a[0] + vec.a[1]*mat.a[4] + vec.a[2]*mat.a[8] + vec.a[3]*mat.a[12],
        vec.a[0]*mat.a[1] + vec.a[1]*mat.a[5] + vec.a[2]*mat.a[9] + vec.a[3]*mat.a[13],
        vec.a[0]*mat.a[2] + vec.a[1]*mat.a[6] + vec.a[2]*mat.a[10] + vec.a[3]*mat.a[14],
        vec.a[0]*mat.a[3] + vec.a[1]*mat.a[7] + vec.a[2]*mat.a[11] + vec.a[3]*mat.a[15]
    };
}




}
