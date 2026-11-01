#pragma once
#include <Geometry/triangle.hpp>
#include <Geometry/mesh2d.hpp>
#include <Math/matrix4x4.hpp>

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

    Mesh2D PerspectiveTransform(int screenWidth, int screenHeight, float fieldOfView, float z_near, float z_far){
        float aspectRatio = (float) screenWidth / screenHeight;
        Mesh2D output; 
        Matrix4x4 transform = Matrix4x4::PerspectiveProjection(aspectRatio,fieldOfView,z_near,z_far);
        
        for (auto& tri : triangles){
            tri.ApplyTransform(transform);
            tri.DivideByZ();
            output.AddTriangle((Triangle2D) tri);
        }

        output.DenormalizeCoordinates(screenWidth, screenHeight);
        return output;
    }
    
};


}