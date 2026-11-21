#pragma once

#include <vector>
#include <cstdint>

#include <Core/color.hpp>


namespace gfx{
    
/*
    Represents a frame buffer used to display the graphics onto the screen
    Designed to work with the SFML Library of C++ but can be adapted to other graphics pipeline as well
*/
class FrameBuffer{

private:
    std::vector<std::uint32_t> frameBuffer;
    std::vector<float> depthBuffer;
    
    // Height and width of the framebuffer (Number of rows and columns)
    int frameWidth, frameHeight; 
    int startX, startY;
    int endX, endY; // Exclusive 

public:

    // Initialized the background color of the frame buffer to solid white
    FrameBuffer(int width, int height, int xstart = 0, int ystart = 0, Color backgroundColor = Color{});

    /*
        @brief Clears the frame buffer with given color
        @param[in] clearColor The default color for the frame buffer
    */
    void Clear(Color clearColor = Color{});

    /*
        @brief Sets a pixel in the frame buffer and sets it in the left handed coordinate system
        @param[in] x Screen x coordinate
        @param[in] y Screen y coordinate
        @param[in] pixelColor Color of the pixel
        @param[in] z_depth Parameter for ordering the triangles (Default = 0)
    */ 
    void PutPixel(int x, int y, Color pixelColor, float z_depth = 0);

    /*
        @brief Get the width of the frame buffer
        @return Width of the frame buffer
    */
    int GetWidth() const{
        return frameWidth;
    }

    /*
        @brief Get the height of the frame buffer
        @return height of the frame buffer
    */
    int GetHeight() const{
        return frameHeight;
    }
 
    /*
        @brief Get the pixels in the frame buffer for window drawing libraries
        @return Vector of 32b integers with ABGR values
    */
    std::vector<std::uint32_t> GetPixels() const;

};

}