#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Core/framebuffer.hpp>
#include <Geometry/line.hpp>
#include <Geometry/triangle.hpp>
#include <Core/color.hpp>
#include <Math/matrix3x3.hpp>

#include <iostream>

int main()
{

    int width = 100, height = 100;
    unsigned int scale = 4;


    gfx::FrameBuffer frame{width,height};
    frame.Clear(gfx::Color{255,255,255,255});


    /*
    gfx::Line_i line0{gfx::Point2i{1,17},gfx::Point2i{54,64}};
    line0.RasterizeBresenham(frame,gfx::Color{255,0,0,255});

    gfx::Line_i line1{gfx::Point2i{54,64},gfx::Point2i{92,12}};
    line1.RasterizeBresenham(frame,gfx::Color{255,0,0,255});

    gfx::Line_i line2{gfx::Point2i{92,12},gfx::Point2i{1,17}};
    line2.RasterizeBresenham(frame,gfx::Color{255,0,0,255});
    */

    gfx::Triangle triangle = gfx::Triangle{gfx::Point2f{10,10}, gfx::Point2f{90,10}, gfx::Point2f{10,90}};
    triangle.SetColor(std::vector<gfx::Color>{gfx::Color{255,0,0,255},gfx::Color{0,255,0,255},gfx::Color{255,0,0,0}});
    
     gfx::Matrix3x3 rotate45 = gfx::Matrix3x3::Rotate(30);
     triangle.ApplyTransform(rotate45);

    triangle.Rasterize(frame,"interpolate");
    
    
    sf::RenderWindow window(
        sf::VideoMode({width*scale, height*scale}),
        "Renderer"
    );


    sf::Texture texture {sf::Vector2u{(unsigned int)width,(unsigned int)height}};
    sf::Sprite sprite{texture};

    texture.setSmooth(false);
    sprite.setScale(sf::Vector2f{(float)scale,(float)scale});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())            
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        
        
        texture.update(reinterpret_cast<const std::uint8_t*> (frame.GetPixels().data()));


        window.clear();
        window.draw(sprite);
        window.display();
    }
    

    return 0;
}
