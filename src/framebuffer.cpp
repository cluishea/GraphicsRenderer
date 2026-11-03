#include <Core/framebuffer.hpp>
#include <algorithm>

namespace gfx{

    FrameBuffer::FrameBuffer(int width, int height, int xstart, int ystart, Color backgroundColor):frameWidth(width), frameHeight(height), startX(xstart), startY(ystart){  
        frameBuffer = std::vector<std::uint32_t>(width*height, backgroundColor.ToRGBA());

        endX = startX + width;
        endY = startY + width;
    }

    void FrameBuffer::Clear(Color clearColor){
        std::uint32_t color = clearColor.ToRGBA();
        for(int i = 0; i<frameHeight*frameWidth;++i){
            frameBuffer[i] = color;
        }
    }

    void FrameBuffer::PutPixel(int x, int y, Color pixelColor){

        // Will turn on the pixels according to the normal right handed coordinate system 

        if(x<startX || y<startY || x >=endX || y >=endY){
            return;
        }

        x = x - startX;
        y = y - startY;
        y = frameHeight - 1 - y;

        frameBuffer[y*frameWidth + x] = pixelColor.ToRGBA();
    }

    std::vector<std::uint32_t> FrameBuffer::GetPixels() const{
        return frameBuffer;
    }

}