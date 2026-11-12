#pragma once
#include <Core/point.hpp>
#include <Core/framebuffer.hpp>
#include <Core/color.hpp>
#include <Math/vector3.hpp>

namespace gfx{

class Line2f{
    
private:
    Point2f start;
    Point2f end;

public:
    Line2f(Point2f startPoint, Point2f endPoint);

    void RasterizeVECGEN(FrameBuffer& frameBuffer,Color lineColor = Color{}, bool rasterizeOutside = true);
    
    void RasterizeBresenham(FrameBuffer& FrameBuffer, Color lineColor = Color{}, bool rasterizeOutside = true);

};

class Line2i{

private:
    Point2i start;
    Point2i end;
public:
    Line2i(Point2i startPoint, Point2i endPoint);
    void RasterizeBresenham(FrameBuffer& frameBuffer, Color lineColor = Color{}, bool rasterizeOutside = true);

};


class Line3f{

private:
    Point3f start;
    Point3f end;

public:
    Line3f(Point3f startPoint, Point3f endPoint): start(startPoint), end(endPoint){}
    Vector3f GetDirectionVector(){
        return Vector3f{start,end};
    }
    Point3f GetStartPoint(){
        return start;
    }
    Point3f GetEndPoint(){
        return end;
    }
};



}