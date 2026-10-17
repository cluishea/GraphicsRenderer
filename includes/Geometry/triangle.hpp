#pragma once
#include <Core/point.hpp>
#include <Core/color.hpp>
#include <Core/framebuffer.hpp>
#include <Math/vector2.hpp>
#include <vector>
#include <string>

namespace gfx{

// The triangle class stores points as float points (Point2f)
// The rendering system uses clockwise direction for polygon faces winding order

class Triangle{

private:
    Point2f p0,p1,p2;
    Color c0,c1,c2;

    Color DEFAULT_COLOR = Color{0,0,0};

    // Returns whether the edge is top flat or left edge
    bool isTopOrLeftEdge(Vector2f edge) const;

public:
    // Construct the triangle with three points also apply three colors for the points
    Triangle(Point2f p0, Point2f p1, Point2f p2, Color c0 , Color c1 , Color c2 );

    // Construct the triangle with just the three points
    Triangle(Point2f p0, Point2f p1, Point2f p2);

    // Construct the triangle with three points and a solid color
    Triangle(Point2f p0, Point2f p1, Point2f p2, Color solidColor);

    // Give a solid Color to all pixels
    void SetColor(Color color);

    // Give color as a vector
    void SetColor(std::vector<Color> colors);


    // Rasterize the triangle (fill)
    // Modes = "solid" or "interpolate"
    void Rasterize(FrameBuffer& frameBuffer, std::string mode = "solid", Color fillColor = Color{0,0,0}) const;

    

};

}