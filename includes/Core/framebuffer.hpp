#pragma once
#include <vector>
#include <cstdint>
#include <Core/color.hpp>

/*
    Represents a frame buffer used to display the graphics onto the screen
    Designed to work with the SFML Library of C++ but can be adapted to other graphics pipeline as well

*/


namespace gfx{
    
class FrameBuffer{

private:
    std::vector<std::uint32_t> frameBuffer;
    
    // Height and width of the framebuffer (Number of rows and columns)
    int frameWidth, frameHeight; 

public:

    // Initialized the background color of the frame buffer to solid white
    FrameBuffer(int width, int height,Color backgroundColor = Color{});

    // Clears the frame buffer with given color
    void Clear(Color clearColor = Color{});

    // Sets a pixel in the frame buffer
    void PutPixel(int x, int y, Color pixelColor);

    // Get the width of the frame buffer
    int GetWidth() const{
        return frameWidth;
    }

    // Get the height of the frame buffer
    int GetHeight() const{
        return frameHeight;
    }
 
    // Get the pixels
    // Note: Modify this so the frame buffer has the end points of coordinate space and set the
    // pixels accordingly, for now its ok
    std::vector<std::uint32_t> GetPixels() const;

};

}