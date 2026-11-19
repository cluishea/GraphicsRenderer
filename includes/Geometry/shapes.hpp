#pragma once

#include <Geometry/mesh3d.hpp>

namespace gfx{

// This namespace contains the definitions of different 3D shapes used in the renderer
namespace Shapes{

    /*
        @brief Returns a Parallelpiped
        @param[in] referencePoint A reference corner of the parallelpiped
        @param[in] sides std::vector<Vector3f> of size 3 containing the three adjacent edges of the referencePoint
        @return The Mesh3D for the parallelpiped
    */
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
            triangles[i].AlignWithVector(diagonalVector * ((i<6) ? 1:-1));
        }

        return Mesh3D{triangles};

    }

    /*
        @brief Returns a Cuboid
        @param[in] referencePoint A reference corner of the cuboid
        @param[in] x_length Length of the cuboid in the x axis
        @param[in] y_length Length of the cuboid in the y axis
        @param[in] z_length Length of the cuboid in the z axis
        @return The Mesh3D for the cuboid
    */
    Mesh3D Cuboid(Point3f referencePoint, float x_length, float y_length, float z_length){
        return ParallelPiped(referencePoint, {Vector3f{x_length,0,0}, Vector3f{0,y_length,0}, Vector3f{0,0,z_length}});
    }
    
    /*
        @brief Returns a Cube
        @param[in] referencePoint A reference corner of the cube
        @param[in] length Length of the cube
        @return The Mesh3D for the cuboid
    */
    Mesh3D Cube(Point3f referencePoint, float length){
        return Cuboid(referencePoint,length,length,length);
    }

    /*
        @brief Returns a Sphere, resolution set in the code
        @param[in] centre The centre of the sphere
        @param[in] radius Radius of the sphere
        @return The Mesh3D for the sphere
    */
    Mesh3D Sphere(Point3f centre, float radius){

        float yawDivision = 5;
        float pitchDivision = 5;

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

        std::vector <Triangle3D> outputTriangles;
        for(int i = 0; i < pitchSize - 1 ; i++){
            for(int j = 0; j < yawSize - 1 ; j++){


                outputTriangles.push_back(Triangle3D{sampledPoints.at(i).at(j), sampledPoints.at(i).at(j+1), sampledPoints.at(i+1).at(j+1)});
                outputTriangles.push_back(Triangle3D{sampledPoints.at(i).at(j), sampledPoints.at(i+1).at(j), sampledPoints.at(i+1).at(j+1)});
            }

            outputTriangles.push_back(Triangle3D{sampledPoints.at(i).at(yawSize-1), sampledPoints.at(i).at(0), sampledPoints.at(i+1).at(0)});
            outputTriangles.push_back(Triangle3D{sampledPoints.at(i).at(yawSize-1), sampledPoints.at(i+1).at(yawSize-1), sampledPoints.at(i+1).at(0)});
        }

        for(auto& tri: outputTriangles){
            tri.ContainPoint(centre);
        }

        return outputTriangles;

    }

    /*
        @brief Returns a 3D polygon
        @param[in] points Points of the polygon in clockwise order
        @param[in] bothSides Allow Both sided polygon (Default = true)
        @param[in] includedPoint Point to include for one sided polygon
        @return 3D polygon
    */
    Mesh3D Polygon(std::vector<Point3f> points, bool bothSides = true, Point3f includedPoint = Point3f{}){

        std::vector<Triangle3D> triangles;
        int size = points.size();
        for(int i = 1; i < size - 1; i++){
            triangles.push_back(
                Triangle3D{
                    points[0], points[i], points[i+1]
                }
            );
            if(bothSides){
                triangles.push_back(
                    Triangle3D{
                        points[0], points[i+1], points[i]
                    }
                );
            }
        }

        if(!bothSides){
            for(auto& tri : triangles){
                tri.ContainPoint(includedPoint);
            }
        }
        return Mesh3D{triangles};
    }

    /*
        @brief Returns a Cylinder, axis along the z axis
        @param[in] centre Centre of the circle
        @param[in] Radius of circle
        @return Circle of given radius and centre
    */
    Mesh3D Circle(Point3f centre, float radius, bool bothSides = true, Point3f containedPoint = Point3f{}){

        std::vector<Triangle3D> triangles;

        float yawDivision = 10;

        std::vector <Point3f> sampledPoints;

        for(int yaw = 0; yaw < 360; yaw += yawDivision){
            float theta = (float) yaw * M_PI / 180.0;
            sampledPoints.push_back(Point3f{
                centre.x + radius * std::cosf(theta),
                centre.y + radius * std::sinf(theta),
                centre.z
            });
        }

        int pointsSize = sampledPoints.size();
        
        for(int i = 0; i + 1< pointsSize; i++){
            triangles.push_back( Triangle3D {centre, sampledPoints[i], sampledPoints[i+1] });
            if (bothSides){
                triangles.push_back( Triangle3D { centre, sampledPoints[i+1], sampledPoints[i]  });
            }
        }
        triangles.push_back( Triangle3D {centre, sampledPoints[pointsSize-1], sampledPoints[0] });
        triangles.push_back( Triangle3D {centre, sampledPoints[0], sampledPoints[pointsSize-1] });

        if(!bothSides){
            for(auto& tri : triangles){
                tri.ContainPoint(containedPoint);
            }
        }

        return Mesh3D{triangles};
    }



    /*
        @brief Returns a Cylinder, axis along the z axis
        @param[in] referencePoint Centre of an end circle of cylinder
        @param[in] Radius of cylinder
        @param[in] Length of cylinder
        @return Cylinder of given length and radius
    */
    Mesh3D Cylinder(Point3f referencePoint, float radius, float length){

        std::vector<Triangle3D> triangles;

        float yawDivision = 10;

        std::vector <Point3f> sampledPointsNear;
        std::vector <Point3f> sampledPointsFar;

        for(int yaw = 0; yaw < 360; yaw += yawDivision){
            float theta = (float) yaw * M_PI / 180.0;
            sampledPointsNear.push_back(Point3f{
                referencePoint.x + radius * std::cosf(theta),
                referencePoint.y + radius * std::sinf(theta),
                referencePoint.z
            });
            sampledPointsFar.push_back(Point3f{
                referencePoint.x + radius * std::cosf(theta),
                referencePoint.y + radius * std::sinf(theta),
                referencePoint.z + length
            });
        }

        int pointsSize = sampledPointsFar.size();
        
        for(int i = 0; i + 1< pointsSize; i++){
            triangles.push_back( Triangle3D {sampledPointsNear[i], sampledPointsNear[i+1], sampledPointsFar[i] });
            triangles.push_back( Triangle3D {sampledPointsNear[i+1], sampledPointsFar[i+1], sampledPointsFar[i] });
        }
        triangles.push_back( Triangle3D {sampledPointsNear[pointsSize-1], sampledPointsNear[0], sampledPointsFar[pointsSize-1] });
        triangles.push_back( Triangle3D {sampledPointsNear[0], sampledPointsFar[0], sampledPointsFar[pointsSize-1] });
        
        Point3f containedPoint{referencePoint.x, referencePoint.y, referencePoint.z + length / 2.f};   

        std::vector<Triangle3D> circle1 = Circle(referencePoint, radius, false, containedPoint).GetTriangles();
        std::vector<Triangle3D> circle2 = Circle(Point3f{referencePoint.x, referencePoint.y, referencePoint.z + length}, radius, false, containedPoint).GetTriangles();

        triangles.insert(triangles.end(), circle1.begin(), circle1.end());
        triangles.insert(triangles.end(), circle2.begin(), circle2.end());

        for(auto& tri:triangles){
            tri.ContainPoint(containedPoint);
        }

        return Mesh3D{triangles};
    }

    /*
        @brief Returns a Cone, axis along the z axis
        @param[in] referencePoint Centre of the base circle of the cone
        @param[in] Radius of cone
        @param[in] Length of cone
        @return Cone of given dimentions
    */
    Mesh3D Cone(Point3f referencePoint, float radius, float length){

        std::vector<Triangle3D> triangles;

        float yawDivision = 10;

        std::vector <Point3f> sampledPoints;

        for(int yaw = 0; yaw < 360; yaw += yawDivision){
            float theta = (float) yaw * M_PI / 180.0;
            sampledPoints.push_back(Point3f{
                referencePoint.x + radius * std::cosf(theta),
                referencePoint.y + radius * std::sinf(theta),
                referencePoint.z
            });
        }

        int pointsSize = sampledPoints.size();
        Point3f tipPoint = Point3f{referencePoint.x, referencePoint.y, referencePoint.z+length};

        for(int i = 0; i + 1< pointsSize; i++){
            triangles.push_back( Triangle3D {tipPoint, sampledPoints[i], sampledPoints[i+1] });
        }
        triangles.push_back( Triangle3D {tipPoint, sampledPoints[pointsSize-1], sampledPoints[0] });
        
        Point3f containedPoint{referencePoint.x, referencePoint.y, referencePoint.z + length / 2.f};   

        std::vector<Triangle3D> circle1 = Circle(referencePoint, radius, false, containedPoint).GetTriangles();

        triangles.insert(triangles.end(), circle1.begin(), circle1.end());

        for(auto& tri:triangles){
            tri.ContainPoint(containedPoint);
        }

        return Mesh3D{triangles};
    }


}

}