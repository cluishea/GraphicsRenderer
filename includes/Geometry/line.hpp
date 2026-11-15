#pragma once
#include <Core/point.hpp>
#include <Core/framebuffer.hpp>
#include <Core/color.hpp>
#include <Math/vector3.hpp>

namespace gfx{

/*
    2D line represented as float values
*/
class Line2f{
    
private:
    Point2f start;
    Point2f end;

public:
    Line2f(Point2f startPoint, Point2f endPoint);

    /*
        @brief Puts the line on the framebuffer using the VECGEN algorithm
        @param[in] frameBuffer Reference to the frame buffer
        @param[in] lineColor Color of the line (Default = Black)
        @param[in] rasterizeOutside Rasterize outside the frame buffer (Default = true)
    */
    void RasterizeVECGEN(FrameBuffer& frameBuffer,Color lineColor = Color{}, bool rasterizeOutside = true);
    
    /*
        @brief Puts the line on the framebuffer using the Bresenham algorithm after rounding the points into integer
        @param[in] frameBuffer Reference to the frame buffer
        @param[in] lineColor Color of the line (Default = Black)
        @param[in] rasterizeOutside Rasterize outside the frame buffer (Default = true)
    */
    void RasterizeBresenham(FrameBuffer& FrameBuffer, Color lineColor = Color{}, bool rasterizeOutside = true);

};

/*
    2D line represented as integer values
*/
class Line2i{

private:

    Point2i start;
    Point2i end;

public:
    Line2i(Point2i startPoint, Point2i endPoint);

    /*
        @brief Puts the line on the framebuffer using the VECGEN algorithm
        @param[in] frameBuffer Reference to the frame buffer
        @param[in] lineColor Color of the line (Default = Black)
        @param[in] rasterizeOutside Rasterize outside the frame buffer (Default = true)
    */
    void RasterizeBresenham(FrameBuffer& frameBuffer, Color lineColor = Color{}, bool rasterizeOutside = true);

};

/*
    3D line represented as float values
*/
class Line3f{

private:
    Point3f start;
    Point3f end;

public:
    Line3f(Point3f startPoint, Point3f endPoint): start(startPoint), end(endPoint){}

    /*
        @brief Get the Direction vector of the line
        @return Vector2f representing the direction of the line
    */
    Vector3f GetDirectionVector(){
        return Vector3f{start,end};
    }

    /*
        @brief Get the starting point of the line
        @return Start point
    */
    Point3f GetStartPoint(){
        return start;
    }

    /*
        @brief Get the ending point of the line
        @return Ending point
    */
    Point3f GetEndPoint(){
        return end;
    }
};


}