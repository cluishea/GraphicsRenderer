#include <Core/framebuffer.hpp>
#include <algorithm>

namespace gfx{

    FrameBuffer::FrameBuffer(int width, int height, Color backgroundColor):frameWidth(width), frameHeight(height){
        frameBuffer = std::vector<std::uint32_t>(width*height, backgroundColor.ToRGBA());
    }

    void FrameBuffer::Clear(Color clearColor){
        std::uint32_t color = clearColor.ToRGBA();
        for(int i = 0; i<frameHeight*frameWidth;++i){
            frameBuffer[i] = color;
        }
    }

    void FrameBuffer::PutPixel(int x, int y, Color pixelColor){
        if(x<0 || y<0 || x >=frameWidth || y >=frameHeight){
            return;
        }
        frameBuffer[y*frameWidth + x] = pixelColor.ToRGBA();
    }

    std::vector<std::uint32_t> FrameBuffer::GetPixels() const{
        return frameBuffer;
    }

}