#include <Geometry/mesh3d.hpp>


namespace gfx{

void Mesh3D::AddTriangle(Triangle3D triangle){
    triangles.emplace_back(triangle);
}

void Mesh3D::SetColor(Color color){
    for(auto& tri : triangles){
        tri.SetSolidColor(color);
    }
}

Mesh2D Mesh3D::PerspectiveTransform(int screenWidth, int screenHeight, float fieldOfView, float z_near, float z_far, Camera camera, Light light){

    float aspectRatio = (float) screenWidth / screenHeight;

    // Output mesh
    Mesh2D output;
    
    // Perspective transform matrix
    Matrix4x4 perspectiveTransformMatrix = Matrix4x4::PerspectiveProjection(aspectRatio,fieldOfView,z_near,z_far);

    // Camera transform matrix
    Matrix4x4 cameraTransform = Matrix4x4::LookAt(camera.GetPosition(), camera.GetTarget(), camera.GetUpDirection());

    // Planes for viewport transform
    std::vector<Plane> viewPortPlanes ={
                    Plane{Point3f{-1,-1,-1}, Vector3f{1,0,0}},
                    Plane{Point3f{-1,-1,-1}, Vector3f{0,1,0}},
                    Plane{Point3f{1,1,1}, Vector3f{-1,0,0}},
                    Plane{Point3f{1,1,1}, Vector3f{0,-1,0}}
                };

    for (auto& tri : triangles){

        // Brightness for the lignting
        float brightness, diffuse;

        Vector3f vecCameraToTriangle = Vector3f {camera.GetPosition(),tri.Centroid()};
        vecCameraToTriangle.Normalize();

        Vector3f triangleNormal = tri.Normal();
        triangleNormal.Normalize();

        if(triangleNormal.Dot(vecCameraToTriangle) > 0.0f){

        
            Triangle3D tri_transformed = tri.ReturnTransform(cameraTransform);

            std::vector <Triangle3D> clippedTriangles;
            clippedTriangles = tri_transformed.ClipTriangle(Plane{Point3f{0,0,z_near}, Vector3f{0,0,1}});


            for(auto& clippedTri : clippedTriangles){
                clippedTri.ApplyTransform(perspectiveTransformMatrix);
                //clippedTri.DivideByZ();
            
                std::vector <Triangle3D> viewportClippedTriangles = clippedTri.ClipTriangle(viewPortPlanes);

                for (auto& viewporttri : viewportClippedTriangles){
                    
                    Triangle2D tri_2d = (Triangle2D) viewporttri;
                    tri_2d.DenormalizeCoordinates(screenWidth, screenHeight);
                    
                    diffuse = std::max(0.0f, (light.direction).Dot(triangleNormal));
                    brightness = std::min (1.0f, 0.25f + diffuse * light.intensity);
                    

                    tri_2d.SetColor(tri.GetSolidColor() * brightness);

                    output.AddTriangle(tri_2d);

                }
                

            }                
        }
    }

    return output;
}

void Mesh3D::ApplyTransform(Matrix4x4 transformation){
    for (auto& tri: triangles){
        tri.ApplyTransform(transformation);
    }
}

std::vector<Triangle3D> Mesh3D::GetTriangles(){
    return triangles;
}

void Mesh3D::ExtendMesh(Mesh3D otherMesh){
    triangles.insert(triangles.end(), otherMesh.triangles.begin(), otherMesh.triangles.end());
}

void Mesh3D::IncludePoint(Point3f includedPoint){
    for(auto& tri : triangles){
        tri.ContainPoint(includedPoint);
    }
}

}