#include <math.h>
#include <Geometry/line.hpp>
#include <Core/point.hpp>
#include <Core/framebuffer.hpp>
#include <Core/color.hpp>
#include <Math/vector2.hpp>

namespace gfx{

Line_f::Line_f(Point2f startPoint, Point2f endPoint):start(startPoint),end(endPoint){}

void Line_f::RasterizeVECGEN(FrameBuffer& frameBuffer, Color lineColor, bool rasterizeOutside){
    if((start.x < 0 || start.y < 0 || start.x >= frameBuffer.GetWidth() || start.y >= frameBuffer.GetHeight()) && !rasterizeOutside){
        return;
    }
    
    // xa, xb, ya, yb are given as floating point numbers as end points, integer endpoints c and f need to be obtained in the algorithm
    // The formula for determining c and f depends upon the direction the line goes towards (right or left)

    // Components of the line in terms of vector
    float dx = end.x - start.x;
    float dy = end.y - start.y;

    if(dx == 0.0 && dy == 0.0){     // INVALID case - Only really happens when both the start and end coords are the same
        return;
    }

    if(std::abs(dx) > std::abs(dy)){          // Gentle slope case (m<1)

        float m = dy/dx;
        int c,f;  // c and f are the starting and ending integer points
        float d;  // d represents the y value for the starting x value 
        
        if (dx > 0){
            c = std::ceil(start.x);
            f = std::floor(end.x);
            d = start.y + m * (c-start.x);
        }
        else{
            c = std::ceil(end.x);
            f = std::floor(start.x);
            d = end.y + m * (c-end.x);
        }

        float r = std::floor(d + 0.5);     // r denotes the rounded value of d which gives the correct row index
        float h = r-d + m;                 // h denotes the difference between the line segment and the row index

        if(m>0){
            float m1 = m - 1;              // Change in y when change in x = 1 and row moves to the next index
            while(c<=f){
                frameBuffer.PutPixel(c,r,lineColor);
                c++;                        // Next column index
                if(h>=0.5){                 // Row change to the upper row at next index
                    r++;
                    h+=m1;
                }else{
                    h+=m;                   // Row does not change
                }
            }
        }else{
            m = -m;                         // Taking it as positive for maintaining similarity
            h = -h;                         // Taking it as positive fir maintaining similarity
            float m1 = m - 1;               // Change in y as dx = 1 and row moves to the next lower index
            while(c<=f){
                frameBuffer.PutPixel(c,r,lineColor);    
                c++;
                if(h > 0.5){                // Row change to lower row
                    r--;
                    h+=m1;                  // Both h and m should be negative but are taken positive
                }else{                      // No row change
                    h+=m;                   
                }
            }
        }
    }

    else{               // Sharp slope case (m > 1)

        float m = dx / dy;
        int r,f;
        float d;

        if(dy > 0){
            r = std::ceil(start.y);
            f = std::floor(end.y);
            d = start.x + m * (r - start.y);
        }else{
            r = std::ceil(end.y);
            f = std::floor(start.y);
            d = end.x + m * (r - end.y);
        }
        
        float c = std::floor(d + 0.5);
        float w = m + (c-d);

        if(m>0){
            float m1 = m - 1;
            while(r <= f){
                frameBuffer.PutPixel(c,r,lineColor);
                r++;
                if(w >= 0.5){
                    c++;
                    w += m1;
                }else{
                    w += m;
                }
            }
        }else{
            m = -m;
            w = -w;
            float m1 = m - 1;
            while(r <= f){
                frameBuffer.PutPixel(c,r,lineColor);
                r++;
                if(w>0.5){
                    c--;
                    w += m1;
                }else{
                    w+=m;
                }
            }
        }

    }
    
}
void Line_f::RasterizeBresenham(FrameBuffer& frameBuffer, Color lineColor, bool rasterizeOutside){
    Line_i{
        Point2i{static_cast<int>(std::round(start.x)),static_cast<int>(std::round(start.y))},
        Point2i{static_cast<int>(std::round(end.x)),static_cast<int>(std::round(end.y))}
    }.RasterizeBresenham(frameBuffer,lineColor,rasterizeOutside);
}

Line_i :: Line_i (Point2i startPoint, Point2i endPoint) : start(startPoint), end(endPoint){

}

void Line_i::RasterizeBresenham(FrameBuffer& frameBuffer, Color lineColor, bool rasterizeOutside){
    if((start.x < 0 || start.y < 0 || start.x >= frameBuffer.GetWidth() || start.y >= frameBuffer.GetHeight()) && !rasterizeOutside){
        return;
    }
    
    // Vector to be drawn
    int dx = end.x - start.x;
    int dy = end.y - start.y;


    if(std::abs(dx) > std::abs(dy)){
        // Gentle slope case (m<1)
        
        int c,f;    // The start and end points in x axis
        int r;      // Row index
        
        if(dx > 0){
            c = start.x;
            f = end.x;
            r = start.y;
        }else{
            c = end.x;
            f = start.x;
            r = end.y;
        }

        // Check variable is g
        // Initial value of h = m
        int g = 2 * std::abs(dy) - std::abs(dx);

        // There are two cases of increment
        int inc1 = 2*std::abs(dy);
        int inc2 = 2*(std::abs(dy) - std::abs(dx));

        if((dx>=0 && dy>=0) || (dx<0 && dy<0)){
            while(c<=f){
                frameBuffer.PutPixel(c,r,lineColor);
                c++;
                if(g>0){
                    r++;
                    g += inc2;
                }else{
                    g+=inc1;
                }
            }
        }
        else{
            while(c<=f){
                frameBuffer.PutPixel(c,r,lineColor);
                c++;
                if(g>0){
                    r--;
                    g += inc2;
                }else{
                    g+=inc1;
                }
            }
        }
    }
    else{
        
        int r,f; // Row index from start to finish
        int c;   // Column index

        if(dy>0){
            r = start.y;
            f = end.y;
            c = start.x;
        }else{
            r = end.y;
            f = start.y;
            c = end.x;
        }

        int g = 2* std::abs(dx) - std::abs(dy);
        // Two increments
        int inc1 = 2 * std::abs(dx);
        int inc2 = 2*(std::abs(dx) - std::abs(dy));

        if((dx>0 && dy>0) || (dx<0 && dy<0)){
            // Positive slope case
            while(r<=f){
                frameBuffer.PutPixel(c,r,lineColor);
                r++;
                if(g>0){
                    c++;
                    g+=inc2;
                }else{
                    g+=inc1;
                }
            }
        }
        else{
            // Negative slope case
            while (r<=f)
            {
                frameBuffer.PutPixel(c,r ,lineColor);
                r++;
                if(g>0){
                    c--;
                    g+=inc2;
                }else{
                    g+=inc1;
                }
            }
            
        }

    }


}



}