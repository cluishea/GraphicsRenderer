#pragma once

#include <Geometry/mesh3d.hpp>

namespace gfx{

// This namespace contains the definitions of different 3D shapes used in the renderer
namespace Shapes{


    Mesh3D ParallelPiped(Point3f referencePoint, std::vector<Vector3f> sides){

        if(sides.size() != 3){
            return Mesh3D{};
        }

        Point3f p0 = referencePoint;
        // Calculation of the three adjacent points
        Point3f p1 = referencePoint + sides[0];
        Point3f p2 = referencePoint + sides[1];
        Point3f p3 = referencePoint + sides[2];
        
        // Calculation of the secondary points
        Point3f p4 = p1 + sides[1];
        Point3f p5 = p1 + sides[2];
        Point3f p6 = p3 + sides[1];

        // Final tertiary point
        Point3f p7 = p4 + sides[2];

        std::vector<Triangle3D> triangles{12};
        // Calculation of the six triangles of the primary point
        triangles[0] = Triangle3D{p0,p1,p5};
        triangles[1] = Triangle3D{p0,p3,p5};
        triangles[2] = Triangle3D{p0,p1,p4};
        triangles[3] = Triangle3D{p0,p2,p4};
        triangles[4] = Triangle3D{p0,p2,p6};
        triangles[5] = Triangle3D{p0,p3,p6};
        // Calculation of the six triangles of the secondary point
        triangles[6] = Triangle3D{p7,p4,p1};
        triangles[7] = Triangle3D{p7,p5,p1};
        triangles[8] = Triangle3D{p7,p5,p3};
        triangles[9] = Triangle3D{p7,p6,p3};
        triangles[10] = Triangle3D{p7,p4,p2};
        triangles[11] = Triangle3D{p7,p6,p2};

        Vector3f diagonalVector = sides[0]+sides[1]+sides[2];
        for(int i = 0; i < 12; i++){
            triangles[i].AlignWithVector(diagonalVector * ((i<6) ? -1:1));
        }

        return Mesh3D{triangles};

    }


    Mesh3D Cuboid(Point3f referencePoint, float x_length, float y_length, float z_length){
        return ParallelPiped(referencePoint, {Vector3f{x_length,0,0}, Vector3f{0,y_length,0}, Vector3f{0,0,z_length}});
    }

    Mesh3D Cube(Point3f referencePoint, float length){
        return Cuboid(referencePoint,length,length,length);
    }

    Mesh3D Sphere(Point3f centre, float radius){

        float yawDivision = 20;
        float pitchDivision = 10;

        std::vector<std::vector<Point3f>> sampledPoints {};
        for(int pitch = 0; pitch <= 180; pitch+=pitchDivision){
            float phi = (float) pitch * M_PI / 180.0;
            std::vector<Point3f> points{};
            for(int yaw = 0; yaw <= 360; yaw += yawDivision){
                float theta = (float) yaw * M_PI / 180.0;
                points.push_back(Point3f{
                    centre.x + radius * std::sinf(phi) * std::cosf(theta),
                    centre.y + radius * std::sinf(phi) * std::sinf(theta),
                    centre.z + radius * std::cosf(phi)
                 });
            }
            sampledPoints.push_back(points);
        }

        int pitchSize = sampledPoints.size();
        int yawSize = sampledPoints.at(0).size();
        std::cout << pitchSize << yawSize << std::endl;

        std::vector <Triangle3D> outputTriangles;
        for(int i = 0; i < pitchSize - 1 ; i++){
            for(int j = 0; j < yawSize - 1 ; j++){

                std::cout << "1" << std::endl;

                outputTriangles.push_back(Triangle3D{sampledPoints.at(i).at(j), sampledPoints.at(i).at(j+1), sampledPoints.at(i+1).at(j+1)});
                outputTriangles.push_back(Triangle3D{sampledPoints.at(i).at(j), sampledPoints.at(i+1).at(j), sampledPoints.at(i+1).at(j+1)});
            }

            std::cout << "2" << std::endl;

            outputTriangles.push_back(Triangle3D{sampledPoints.at(i).at(yawSize-1), sampledPoints.at(i).at(0), sampledPoints.at(i+1).at(0)});
            outputTriangles.push_back(Triangle3D{sampledPoints.at(i).at(yawSize-1), sampledPoints.at(i+1).at(yawSize-1), sampledPoints.at(i+1).at(0)});
        }

        for(auto& tri: outputTriangles){
            tri.ContainPoint(centre);
        }

        return outputTriangles;

    }


}

}