#pragma once
#include <Geometry/mesh3d.hpp>
#include <View/camera.hpp>

namespace gfx{

/*
    Class for organizing the objects in the world
*/

class World{

private:
    std::vector<Mesh3D> objects;

    Camera& camera;

public:

    World(std::vector<Mesh3D> obj, Camera& cam):camera(cam){
        objects = obj;
    }

    Mesh2D ConvertToScreen(int screenWidth, int screenHeight){
        Mesh2D mesh2d;

        for(auto& mesh:objects){
            mesh2d.ExtendMesh(mesh.PerspectiveTransform(screenWidth, screenHeight, camera.GetFOV(), camera.GetZNear(), camera.GetZFar(), camera , gfx::Light{gfx::Point3f{1,1,1}, 0.75}));
        }

        return mesh2d;
    }
    
    void AddObject(Mesh3D obj){
        objects.push_back(obj);
    }

    void AddObjects(std::vector<Mesh3D> obj){
        objects.insert(objects.end(), obj.begin(), obj.end());
    }

    void ApplyTransform(Matrix4x4 transform){
        for(auto& obj : objects){
            obj.ApplyTransform(transform);
        }
    }

    

};

}