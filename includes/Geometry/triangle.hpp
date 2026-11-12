#pragma once
#include <Core/point.hpp>
#include <Core/color.hpp>
#include <Core/framebuffer.hpp>
#include <Math/vector2.hpp>
#include <Math/matrix3x3.hpp>
#include <Math/matrix4x4.hpp>
#include <Geometry/plane.hpp>
#include <vector>
#include <string>

namespace gfx{

// The triangle class stores points as float points (Point2f)
// The rendering system uses clockwise direction for polygon faces winding order

class Triangle2D{

private:
    Point2f p0,p1,p2;
    Color c0,c1,c2;
    Color solidColor;

    Color DEFAULT_COLOR = Color{0,0,0};


    // Returns whether the edge is top flat or left edge
    bool isTopOrLeftEdge(Vector2f edge) const;

    // Ensures that the winding is clockwise
    void CheckClockwise();


public:
    // Construct the triangle with three points also apply three colors for the points
    Triangle2D(Point2f p0, Point2f p1, Point2f p2, Color c0 , Color c1 , Color c2 );

    // Construct the triangle with just the three points
    Triangle2D(Point2f p0, Point2f p1, Point2f p2);

    // Construct the triangle with three points and a solid color
    Triangle2D(Point2f p0, Point2f p1, Point2f p2, Color solidColor);

    // Give a solid Color to all pixels
    void SetColor(Color color);

    // Give color as a vector
    void SetColor(std::vector<Color> colors);



    // Rasterize the triangle (fill)
    // Modes = "solid" or "interpolate"
    void Rasterize(FrameBuffer& frameBuffer, std::string mode = "solid") const;

    // Draw the edges
    void DrawEdges(FrameBuffer& FrameBuffer, Color lineColor = Color{0,0,0}) const;

    // Apply the given transformation, input given as the transformation matrix
    void ApplyTransform(Matrix3x3 transformMatrix);

    // Denormalize the points
    void DenormalizeCoordinates(int screenWidth, int screenHeight){
        p0.Denormalize(screenWidth, screenHeight);
        p1.Denormalize(screenWidth, screenHeight);
        p2.Denormalize(screenWidth, screenHeight);
    }

};


/*
    Three dimensional triangles
*/
class Triangle3D{

private:
    Point3f p0, p1, p2; 
    Color solidColor;
    Color DEFAULT_COLOR = Color{0,0,0};


public:

    Triangle3D();

    // Construct with three points
    Triangle3D(Point3f p0, Point3f p1, Point3f p2);

    // Construct with three points and solid color
    Triangle3D(Point3f p0, Point3f p1, Point3f p2, Color solidColor);

    // Apply the given transform, input is 4x4 matrix
    void ApplyTransform(Matrix4x4 transformMatrix);

    // Apply the given transform, returning a Triangle2D
    Triangle3D ReturnTransform(Matrix4x4 transformMatrix);

    void DivideByZ();

    // Get triangle point
    Point3f Centroid(){
        return Point3f{
            (p0.x+p1.x+p2.x)/3,
            (p0.y+p1.y+p2.y)/3,
            (p0.z+p1.z+p2.z)/3
        };
    }

    // Get solid color
    Color GetSolidColor(){
        return solidColor;
    }

    // Convert to Triangle2D just keeping the x and y coordinates
    operator Triangle2D(){
        return Triangle2D{
            (Point2f)p0,
            (Point2f)p1,
            (Point2f)p2
        };
    }

    // Get the normal of the triangle (Assumed to be wound clockwise)
    Vector3f Normal(){
        Vector3f l1 = Vector3f {p0,p1};
        Vector3f l2 = - Vector3f {p0,p2};
        
        Vector3f normal = l1.Cross(l2);
        normal.Normalize();
        return normal;
    }



    // Clip the triangle against the given plane
    std::vector<Triangle3D> ClipTriangle(Plane clippingPlane){

        std::vector<Triangle3D> outputTriangles = std::vector<Triangle3D>{};
        
        std::vector <Point3f> insidePoints = std::vector <Point3f>{};
        std::vector <Point3f> outsidePoints = std::vector <Point3f>{};

        if(clippingPlane.IsOnPositiveSide(p0)){
            insidePoints.push_back(p0);
        }else{
            outsidePoints.push_back(p0);
        }
        if(clippingPlane.IsOnPositiveSide(p1)){
            insidePoints.push_back(p1);
        }else{
            outsidePoints.push_back(p1);
        }
        if(clippingPlane.IsOnPositiveSide(p2)){
            insidePoints.push_back(p2);
        }else{
            outsidePoints.push_back(p2);
        }

        int numberOfPointsInside = insidePoints.size();

        switch (numberOfPointsInside)
        {
        case 0:
            break;

        case 3:
            outputTriangles.push_back(Triangle3D{p0,p1,p2});
            break;
        
        case 1:
            outputTriangles.push_back(Triangle3D{
                insidePoints[0],
                clippingPlane.FindIntersectionPoint(Line3f{outsidePoints[0], insidePoints[0]}),
                clippingPlane.FindIntersectionPoint(Line3f{outsidePoints[1], insidePoints[0]})
            });
            break;

        case 2: 
            // Calculation of the two points
            Point3f point1 = clippingPlane.FindIntersectionPoint(Line3f{insidePoints[0], outsidePoints[0]});
            Point3f point2 = clippingPlane.FindIntersectionPoint(Line3f{insidePoints[1], outsidePoints[0]});

            outputTriangles.push_back(Triangle3D{
                insidePoints[0],
                insidePoints[1],
                point1
            });

            outputTriangles.push_back(Triangle3D{
                insidePoints[0],
                insidePoints[1],
                point2
            });


        }
        return outputTriangles;
    
    }

    

};





}
