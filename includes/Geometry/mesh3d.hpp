#pragma once
#include <Geometry/triangle.hpp>
#include <Geometry/mesh2d.hpp>
#include <Math/matrix4x4.hpp>
#include <View/camera.hpp>

namespace gfx{

// Define a 3D mesh with triangles wound clockwise
// Could store the points and triangles separate
class Mesh3D{
    
private:
    // Triangles (Clockwise winding)
    std::vector<Triangle3D> triangles;

public:

    Mesh3D(){
        triangles = std::vector<Triangle3D>{};
    }

    void AddTriangle(Triangle3D triangle){
        triangles.emplace_back(triangle);
    }

    Mesh2D PerspectiveTransform(int screenWidth, int screenHeight, float fieldOfView, float z_near, float z_far, Camera camera  = Camera{}){
        float aspectRatio = (float) screenWidth / screenHeight;
        Mesh2D output; 
        Matrix4x4 transform = Matrix4x4::PerspectiveProjection(aspectRatio,fieldOfView,z_near,z_far);
        
        for (auto& tri : triangles){

            Vector3f vecCameraToTriangle = Vector3f {camera.GetPosition(),tri.Centroid()};
            vecCameraToTriangle.Normalize();

            Vector3f triangleNormal = tri.Normal();
            
            std::cout << " Dot : " << triangleNormal.Dot(vecCameraToTriangle) << std::endl;

            if(triangleNormal.Dot(vecCameraToTriangle) > 0.0f){
                tri.ApplyTransform(transform);
                tri.DivideByZ();
                output.AddTriangle((Triangle2D) tri);
            }
        }

        output.DenormalizeCoordinates(screenWidth, screenHeight);
        return output;
    }
    
};


}