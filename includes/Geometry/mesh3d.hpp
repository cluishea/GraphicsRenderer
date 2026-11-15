#pragma once
#include <Geometry/triangle.hpp>
#include <Geometry/mesh2d.hpp>
#include <Math/matrix4x4.hpp>
#include <View/camera.hpp>
#include <View/light.hpp>

namespace gfx{

/*
    3D mesh for holding triangles representing a 3D object mesh
*/
class Mesh3D{
    
private:
    // Triangles (Clockwise winding)
    std::vector<Triangle3D> triangles;

public:

    Mesh3D(){
        triangles = std::vector<Triangle3D>{};
    }

    Mesh3D (std::vector<Triangle3D> tri) : triangles(tri){

    }

    /*
        @brief Add a triangle in the mesh
        @param[in] triangle Triangle to be added
    */
    void AddTriangle(Triangle3D triangle);

    /*
        @brief Set the solid color of the mesh
        @param[in] color Color of the mesh
    */
    void SetColor(Color color = Color{});

    /*
        @brief Transform the Mesh3D to Mesh2D applying the perspective projection transform and camera pointat transform
        @param[in] screenWidth Width of the screen in pixels
        @param[in] screenHeight Height of the screen in pixels
        @param[in] fieldOfView FOV of the camera (in Degree)
        @param[in] z_near Near face for viewing
        @param[in] z_far Far face for viewing
        @param[in] camera Camera object for the transform
        @param[in] light Light object representing lighting in the world
        @return Mesh2D representing mesh of the triangles in screen coordinates illuminated accordingly

    */
    Mesh2D PerspectiveTransform(int screenWidth, int screenHeight, float fieldOfView, float z_near, float z_far, Camera camera  = Camera{}, Light light = Light{});

    /*
        @brief Applies the transform to all triangles
        @param[in] transform 4x4 Matrix representing the transform
    */
    void ApplyTransform(Matrix4x4 transformation);
    
};


}