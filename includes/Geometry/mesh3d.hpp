#pragma once
#include <Geometry/triangle.hpp>
#include <Geometry/mesh2d.hpp>
#include <Math/matrix4x4.hpp>
#include <View/camera.hpp>
#include <View/light.hpp>

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

    Mesh2D PerspectiveTransform(int screenWidth, int screenHeight, float fieldOfView, float z_near, float z_far, Camera camera  = Camera{}, Light light = Light{}){

        float aspectRatio = (float) screenWidth / screenHeight;

        // Output mesh
        Mesh2D output;
        
        // Perspective transform matrix
        Matrix4x4 perspectiveTransformMatrix = Matrix4x4::PerspectiveProjection(aspectRatio,fieldOfView,z_near,z_far);

        // Camera transform matrix
        Matrix4x4 cameraTransform = Matrix4x4::LookAt(camera.GetPosition(), camera.GetTarget(), camera.GetUpDirection());

        

        
        for (auto& tri : triangles){

            // Brightness for the lignting
            float brightness, diffuse;

            Vector3f vecCameraToTriangle = Vector3f {camera.GetPosition(),tri.Centroid()};
            vecCameraToTriangle.Normalize();

            Vector3f triangleNormal = tri.Normal();
            

            if(triangleNormal.Dot(vecCameraToTriangle) > 0.0f){

                std::cout << "Present" << std::endl;
            
                Triangle3D tri_transformed = tri.ReturnTransform(cameraTransform);
                tri_transformed.ApplyTransform(perspectiveTransformMatrix);
                tri_transformed.DivideByZ();

                Triangle2D tri_2d = (Triangle2D) tri_transformed;
                tri_2d.DenormalizeCoordinates(screenWidth, screenHeight);
                
                diffuse = std::max(0.0f, (  light.direction).Dot(triangleNormal));
                brightness = std::min (1.0f, 1.f + diffuse * light.intensity);
                

                tri_2d.SetColor(tri.GetSolidColor() * brightness);

                output.AddTriangle(tri_2d);
            }
        }

        return output;
    }

    void ApplyTransform(Matrix4x4 transformation){
        for (auto& tri: triangles){
            tri.ApplyTransform(transformation);
        }
    }
    
};


}