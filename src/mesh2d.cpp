#include <Geometry/mesh2d.hpp>


namespace gfx{

void Mesh2D::AddTriangle(Triangle2D triangle){
    triangles.push_back(triangle);
}

void Mesh2D::DrawMesh(FrameBuffer& frameBuffer, Color lineColor){
    for(auto& tri : triangles){
        tri.DrawEdges(frameBuffer, lineColor);
    }
}

void Mesh2D::RasterizeMesh(FrameBuffer& frameBuffer){
    for(auto& tri : triangles){
        tri.Rasterize(frameBuffer,"solid");
    }
}

void Mesh2D::DenormalizeCoordinates(int screenWidth, int screenHeight){
    for (auto& tri:triangles){
        tri.DenormalizeCoordinates(screenWidth, screenHeight);
    }
}



}
