#include <Geometry/triangle.hpp>
#include <Geometry/line.hpp>
#include <math.h>
#include <iostream>

namespace gfx{

Triangle2D::Triangle2D(Point2f p0, Point2f p1, Point2f p2, Color c0, Color c1, Color c2):p0(p0), p1(p1), p2(p2), c0(c0), c1(c1), c2(c2){}

Triangle2D::Triangle2D(Point2f p0, Point2f p1, Point2f p2):p0(p0), p1(p1), p2(p2){
    c0 = DEFAULT_COLOR;
    c1 = DEFAULT_COLOR;
    c2 = DEFAULT_COLOR;
}

Triangle2D::Triangle2D(Point2f p0, Point2f p1, Point2f p2, Color solidColor):p0(p0), p1(p1), p2(p2){
    c0 = solidColor;
    c1 = solidColor;
    c2 = solidColor;
}

void Triangle2D::SetColor(Color solidColor){
    c0 = solidColor;
    c1 = solidColor;
    c2 = solidColor;
}

void Triangle2D::SetColor(std::vector<Color> colors){

    if(colors.size() != 3){ return; }
    c0 = colors[0];
    c1 = colors[1];
    c2 = colors[2];

    //std::cout <<  std::hex << c0.ToRGBA() << " " << c1.ToRGBA() << " " << c2.ToRGBA() << std::endl;
}

bool Triangle2D::isTopOrLeftEdge(Vector2f edge) const{
    // It assumes clockwise winding of edges
    return ((edge.y == 0.f && edge.x > 0.f) || (edge.y < 0.f));
}


void Triangle2D::Rasterize(FrameBuffer& frameBuffer, std::string mode, Color fillColor) const {

    float topLeftBiasTerm = -0.0000001;

    // Check if mode string is invalid
    if(mode != "solid" && mode != "interpolate"){
        return;
    }    

    bool interpolate = false;

    // Find the minimum and maximum x which helps in limiting the number of checks as well as discard the part of the triangle outside the buffer
    
    int x_max = std::ceil(std::max(p0.x, std::max(p1.x,p2.x)));
    int x_min = std::floor(std::min(p0.x, std::min(p1.x,p2.x)));
    int y_max = std::ceil(std::max(p0.y, std::max(p1.y,p2.y)));
    int y_min = std::floor(std::min(p0.y, std::min(p1.y,p2.y)));

    // If triangle to display are outside the buffer, set the limits to the buffer
    if(x_min < 0) x_min = 0;
    if(y_min < 0) y_min = 0;
    if(x_max >= frameBuffer.GetWidth()) x_max = frameBuffer.GetWidth() - 1;
    if(y_max >= frameBuffer.GetHeight()) y_max = frameBuffer.GetHeight() - 1;

    // Check if have to interpolate
    if(mode == "interpolate"){
        interpolate = true;
    }


    /*  ALGORITHM
        Loop through each pixel in the boundary.
        Calculate the cross product of vector from vertex to point and vector from vertex to next vertex (clockwise winding)
        If the cross product for all vertices is positive, the point lies within the triangle

        Finding the cross product is a bit computationally expensive. 
        It is found that in each column step, the cross product with respect to same vertex changes by a constant amount and by a different amount for step through
        each column. So this is used to update the value of cross product rather than compute for each step rather than compute each step.
        This is only possible as the scanline is parallel and perpendicular to the indices direction.
        From calculation, 
        Cross(vec_01,pos_0p) = ci(p1x-p0x) + ri(poy-p1y) + (p1y pox - p1x poy)
        
        If cross product > 0, the pixel is filled.
        But this brings an issue of overdraw where some pixels are shared by multiple triangles.
        For this, the top left convention is used in which the pixels in the top or left edge are filled but those on other edges are ignored.
        To acheive so, a bias term is added to each cross product term. For top or left edge cross product terms, bias = 0 and for other edges it should be the negative
        of least value the data type can hold. (It is not perfect for floats, so fixed floats are useful.).
        If pixel which is right on the non top or left edge has cross product 0, it is pushed to a negative value so not painted.

        The function also allows interpolation of color, which is done through Barycentric coordinates, alpha, beta and gamma values, which is the fraction of area of triangle
        held on the opposite side by the point.


    
    */

    // Three side vectors (Taken clockwise)
    Vector2f side_01 = Vector2f(p0,p1);
    Vector2f side_12 = Vector2f(p1,p2);
    Vector2f side_20 = Vector2f(p2,p0);

    // Value proportional to the area of triangle for the interpolation
    float triangleArea = side_01.Cross(-side_20);

    // Bias terms for the edges
    float bias_side_01 = isTopOrLeftEdge(side_01) ? 0 : topLeftBiasTerm;
    float bias_side_12 = isTopOrLeftEdge(side_12) ? 0 : topLeftBiasTerm;
    float bias_side_20 = isTopOrLeftEdge(side_20) ? 0 : topLeftBiasTerm;


    
    // Cross product for the top pixel (x max, y max)
    // The cross products are defined by w0, w1, w2. It follows convention of opposite edge for the purpose of Barycenter computation
    
    float w0_init = side_12.Cross({p1,Point2f{static_cast<float>(x_min),static_cast<float>(y_min)}}) + bias_side_12;
    float w1_init = side_20.Cross({p2,Point2f{static_cast<float>(x_min),static_cast<float>(y_min)}}) + bias_side_20;
    float w2_init = side_01.Cross({p0,Point2f{static_cast<float>(x_min),static_cast<float>(y_min)}}) + bias_side_01;

    //std::cout << x_min << y_min << x_max << y_max<< std::endl;
    //std::cout << w0_init << " " << w1_init << " " << w2_init << std::endl;

    // From derived formula, calculating w_delta for row and column

    float delta_w0_column = p1.y - p2.y;
    float delta_w0_row = p2.x - p1.x;

    float delta_w1_column = p2.y - p0.y;
    float delta_w1_row = p0.x - p2.x;

    float delta_w2_column = p0.y - p1.y;
    float delta_w2_row = p1.x - p0.x;

    // Looping through the candidate points
    for (int j = y_min; j < y_max ; j++){

        float w0 = w0_init;
        float w1 = w1_init;
        float w2 = w2_init;

        for(int i = x_min; i <= x_max; i++){

            //std::cout << i << " , " << j << w0 << " " << " " << w1 << " " << w2 << std::endl;

            // Check for whether the pixel belongs to the triangle
            if(w0 > 0 && w1 > 0 && w2 > 0){
                //std::cout << "Did" << std::endl;
                if(interpolate){
                    float alpha = w0 / triangleArea;
                    float beta = w1 / triangleArea;
                    float gamma = w2 / triangleArea;
                    // std::cout << alpha << " " << beta << " " << gamma << std::endl;
                    fillColor = c0 * alpha + c1 * beta + c2 * gamma;
                    // std::cout << std::hex << fillColor.ToRGBA() << std::endl;
                }
                frameBuffer.PutPixel(i,j,fillColor);
            }

            w0+=delta_w0_column;
            w1+=delta_w1_column;
            w2+=delta_w2_column;
        }

        w0_init += delta_w0_row;
        w1_init += delta_w1_row;
        w2_init += delta_w2_row;
    }
}

void Triangle2D::DrawEdges(FrameBuffer& frameBuffer, Color lineColor) const{

    std::cout << p0.x << " " << p0.y << std::endl;
    std::cout << p1.x << " " << p1.y << std::endl;
    std::cout << p2.x << " " << p2.y << std::endl;

    Line_f{p0,p1}.RasterizeBresenham(frameBuffer,lineColor);
    Line_f{p1,p2}.RasterizeBresenham(frameBuffer,lineColor);
    Line_f{p0,p2}.RasterizeBresenham(frameBuffer,lineColor);
}

void Triangle2D::ApplyTransform(Matrix3x3 transformation){
    p0 = (Vector3f::Wrap2DPoint(p0)*transformation).Unwrap2DPoint();
    p1 = (Vector3f::Wrap2DPoint(p1)*transformation).Unwrap2DPoint();
    p2 = (Vector3f::Wrap2DPoint(p2)*transformation).Unwrap2DPoint();
}




Triangle3D::Triangle3D(Point3f p0, Point3f p1, Point3f p2):p0(p0), p1(p1), p2(p2){}

void Triangle3D::DivideByZ(){
    if(p0.z!=0){
        p0.x /= p0.z;
        p0.y /= p0.z;
    }
    if(p1.z!=0){
        p1.x /= p1.z;
        p1.y /= p1.z;
    }
    if(p2.z!=0){
        p2.x /= p2.z;
        p2.y /= p2.z;
    }   

}

void Triangle3D::ApplyTransform(Matrix4x4 transformation){
    p0 = (Vector4f::Wrap3DPoint(p0)*transformation).Unwrap3DPoint();
    p1 = (Vector4f::Wrap3DPoint(p1)*transformation).Unwrap3DPoint();
    p2 = (Vector4f::Wrap3DPoint(p2)*transformation).Unwrap3DPoint();
}



















}