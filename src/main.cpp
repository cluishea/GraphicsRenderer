#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Core/framebuffer.hpp>
#include <Geometry/line.hpp>
#include <Geometry/triangle.hpp>
#include <Core/color.hpp>
#include <Math/matrix3x3.hpp>
#include <Geometry/mesh2d.hpp>
#include <Geometry/mesh3d.hpp>

#include <iostream>

int main()
{

    int width = 100, height = 100;
    unsigned int scale = 4;


    gfx::FrameBuffer frame{width,height};
    frame.Clear(gfx::Color{255,255,255,255});


    /*
    gfx::Line_f line0{gfx::Point2f{40,40},gfx::Point2f{60,0}};
    line0.RasterizeVECGEN(frame,gfx::Color{255,255,0,255});

    gfx::Line_i line1{gfx::Point2i{54,64},gfx::Point2i{92,12}};
    line1.RasterizeBresenham(frame,gfx::Color{255,0,0,255});

    gfx::Line_i line2{gfx::Point2i{92,12},gfx::Point2i{1,17}};
    line2.RasterizeBresenham(frame,gfx::Color{255,0,0,255});
    */

    
    /*gfx::Triangle triangle = gfx::Triangle{gfx::Point2f{10,10}, gfx::Point2f{78,10}, gfx::Point2f{10,90}};
    triangle.SetColor(std::vector<gfx::Color>{gfx::Color{255,0,0,255},gfx::Color{0,255,0,255},gfx::Color{255,0,0,0}});
    
    gfx::Matrix3x3 rotate45 = gfx::Matrix3x3::Rotate(4);
    triangle.ApplyTransform(rotate45);

    
    triangle.Rasterize(frame,"interpolate", gfx::Color{255,0,0});
    triangle.DrawEdges(frame);
    */

    /*
    gfx::Triangle2D t1 = gfx::Triangle2D(gfx::Point2f{10,10},gfx::Point2f{50,10},gfx::Point2f{10,50});
    gfx::Triangle2D t2 = gfx::Triangle2D(gfx::Point2f{15,10},gfx::Point2f{50,10},gfx::Point2f{60,50});
    

    gfx::Mesh2D mesh;
    mesh.AddTriangle(t1);
    mesh.AddTriangle(t2);

    mesh.DrawMesh(frame);

    */

    gfx::Point3f p0{1,1,1};
    gfx::Point3f p1{1,2,1};
    gfx::Point3f p2{2,2,1};
    gfx::Point3f p3{2,1,1};
    gfx::Point3f p4{1,1,2};
    gfx::Point3f p5{1,2,2};
    gfx::Point3f p6{2,2,2};
    gfx::Point3f p7{2,1,2};

    gfx::Triangle3D t1 {p0,p1,p2};
    gfx::Triangle3D t2 {p0, p2,p3};
    gfx::Triangle3D t3 {p6,p5,p4};
    gfx::Triangle3D t4 {p7, p6, p4};
    gfx::Triangle3D t5 {p1,p5,p2};
    gfx::Triangle3D t6 {p2, p5, p6};
    gfx::Triangle3D t7 {p3, p2, p7};
    gfx::Triangle3D t8 {p7,p2,p6};
     gfx::Triangle3D t9 {p0,p5,p1};
    gfx::Triangle3D t10 {p4, p5, p0};
    gfx::Triangle3D t11 {p0, p4, p3};
    gfx::Triangle3D t12 {p3,p7,p4};

    gfx::Mesh3D mesh;
    mesh.AddTriangle(t1);
    mesh.AddTriangle(t2);
    mesh.AddTriangle(t3);
    mesh.AddTriangle(t4);
    mesh.AddTriangle(t5);
    mesh.AddTriangle(t6);
    mesh.AddTriangle(t7);
    mesh.AddTriangle(t8);
    mesh.AddTriangle(t9);
    mesh.AddTriangle(t10);
    mesh.AddTriangle(t11);
    mesh.AddTriangle(t12);

    gfx::Mesh2D mesh2 = mesh.PerspectiveTransform(width, height,120,0.1f,100);
    mesh2.DrawMesh(frame);
    
    //gfx::Triangle2D t = gfx::Triangle2D{gfx::Point2f{10,10}, gfx::Point2f{40,0}, gfx::Point2f{0,40}};
    //t.Rasterize(frame);

    // Fix the issue where 3D to 2D operation messes up the winding order of triangles

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
