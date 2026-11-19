#pragma once
#include <vector>
#include <Geometry/triangle.hpp>

namespace gfx{

/*
    2D mesh for holding triangles representing a mesh
*/
class Mesh2D{
    
private:
    // Triangles (Clockwise winding)
    std::vector<Triangle2D> triangles;

public:

    Mesh2D(){
        triangles = std::vector<Triangle2D>{};
    }

    /*
        @brief Add a triangle in the mesh
        @param[in] triangle Triangle to be added
    */
    void AddTriangle(Triangle2D triangle);

    /*
        @brief Puts the Mesh2D in the frame buffer by drawing the triangle edges
        @param[in] frameBuffer Reference to the frame buffer
        @param[in] lineColor Color of the triangle edges
    */
    void DrawMesh(FrameBuffer& frameBuffer, Color lineColor = Color{0,0,0});

    /*
        @brief Puts the Mesh2D in the frame buffer by filling the triangle
        @param[in] frameBuffer Reference to the frame buffer
    */
    void RasterizeMesh(FrameBuffer& frameBuffer);

    /*
        @brief Denormalizes the coordinates of the triangles of the mesh tto the Screen coordinates
        @param[in] screenWidth Width of the screen in pixels
        @param[in] screenHeight Height of the screen in pixels
    */  
    void DenormalizeCoordinates(int screenWidth, int screenHeight);

    /*
        @brief Add triangles into the mesh
        @param[in] addedTriangles List of triangles to add to the mesh
    */
    void AddTriangles(std::vector<Triangle2D> newTriangles);

    /*
        @brief Extend the mesh with another mesh
        @param[in] anotherMesh Anther Mes2D object
    */
    void ExtendMesh(Mesh2D otherMesh);
};

}