#pragma once
#include <vector>
#include <Geometry/triangle.hpp>

namespace gfx{

// Define a 2D mesh with triangles wound clockwise
class Mesh2D{
    
private:
    // Triangles (Clockwise winding)
    std::vector<Triangle2D> triangles;

public:

    Mesh2D(){
        triangles = std::vector<Triangle2D>{};
    }

    void AddTriangle(Triangle2D triangle){
        triangles.emplace_back(triangle);
    }

    void DrawMesh(FrameBuffer& frameBuffer, Color lineColor = Color{0,0,0}){
        for(auto tri : triangles){
            tri.DrawEdges(frameBuffer, lineColor);
        }
    }

    void DenormalizeCoordinates(int screenWidth, int screenHeight){
        for (auto& tri:triangles){
            tri.DenormalizeCoordinates(screenWidth, screenHeight);
        }
    }

};

}