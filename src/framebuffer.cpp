#include <Core/framebuffer.hpp>
#include <algorithm>

namespace gfx{

    FrameBuffer::FrameBuffer(int width, int height, int xstart, int ystart, Color backgroundColor):frameWidth(width), frameHeight(height), startX(xstart), startY(ystart){  
        frameBuffer = std::vector<std::uint32_t>(width*height, backgroundColor.ToRGBA());
        depthBuffer = std::vector<float>(width*height,0.0f);
        endX = startX + width;
        endY = startY + height;
    }

    void FrameBuffer::Clear(Color clearColor){
        std::uint32_t color = clearColor.ToRGBA();
        for(int i = 0; i<frameHeight*frameWidth;++i){
            frameBuffer[i] = color;
            depthBuffer[i] = 0.0f;
        }
    }

    void FrameBuffer::PutPixel(int x, int y, Color pixelColor, float z_depth){

        // Will turn on the pixels according to the normal right handed coordinate system 

        if(x<startX || y<startY || x >=endX || y >=endY){
            return;
        }

        x = x - startX;
        y = y - startY;
        y = frameHeight - 1 - y;

        if(z_depth < depthBuffer[y*frameWidth + x]){
            return;
        }

        frameBuffer[y*frameWidth + x] = pixelColor.ToRGBA();
        depthBuffer[y*frameWidth + x] = z_depth;
    }

    std::vector<std::uint32_t> FrameBuffer::GetPixels() const{
        return frameBuffer;
    }

}