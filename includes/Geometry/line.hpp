#pragma once
#include <Core/point.hpp>
#include <Core/framebuffer.hpp>
#include <Core/color.hpp>

namespace gfx{

class Line_f{
    
private:
    Point2f start;
    Point2f end;

public:
    Line_f(Point2f startPoint, Point2f endPoint);

    void RasterizeVECGEN(FrameBuffer& frameBuffer,Color lineColor = Color{}, bool rasterizeOutside = true);
    // Do convert this to Bresenham rasterizer

};

class Line_i{

private:
    Point2i start;
    Point2i end;
public:
    Line_i(Point2i startPoint, Point2i endPoint);
    void RasterizeBresenham(FrameBuffer& frameBuffer, Color lineColor = Color{});

};
}