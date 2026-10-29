#pragma once
#include <vector>
#include <Geometry/triangle.hpp>

namespace gfx{

// Define a 2D mesh with triangles wound clockwise
class Mesh2D{
    
private:
    // Triangles (Clockwise winding)
    std::vector<Triangle> triangles;

public:

    Mesh2D(){
        triangles = std::vector<Triangle>{};
    }


};

}