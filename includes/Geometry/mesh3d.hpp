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
        Mesh2D output; 
        Matrix4x4 transform = Matrix4x4::PerspectiveProjection(aspectRatio,fieldOfView,z_near,z_far);

        std::cout << light.intensity;
        
        for (auto& tri : triangles){

            // Brightness for the lignting
            float brightness;

            Vector3f vecCameraToTriangle = Vector3f {camera.GetPosition(),tri.Centroid()};
            vecCameraToTriangle.Normalize();

            Vector3f triangleNormal = tri.Normal();
            std::cout << triangleNormal.a[0] << " " << triangleNormal.a[1] << " " << triangleNormal.a[2] << std::endl;
            
            // std::cout << " Dot : " << triangleNormal.Dot(vecCameraToTriangle) << std::endl;

            if(triangleNormal.Dot(vecCameraToTriangle) > 0.0f){
                tri.ApplyTransform(transform);
                tri.DivideByZ();
                Triangle2D tri_2d = (Triangle2D) tri;

                if(light.direction.a[0] == 0.0f || light.direction.a[1] == 0.0f || light.direction.a[2] == 0.0f){
                    brightness = light.intensity;
                } else {
                    brightness = std::max(0.0f, (light.direction).Dot(triangleNormal)) * light.intensity;
                }

                tri_2d.SetColor(tri.GetSolidColor() * brightness);
                std::cout << (-light.direction).Dot(triangleNormal) << std::endl;

                output.AddTriangle(tri_2d);
            }
        }

        output.DenormalizeCoordinates(screenWidth, screenHeight);
        return output;
    }
    
};


}