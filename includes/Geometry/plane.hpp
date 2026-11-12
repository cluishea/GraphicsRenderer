#pragma once
#include <Math/vector3.hpp>
#include <Core/point.hpp>
#include <Geometry/line.hpp>

namespace gfx{

class Plane{

private:

    Point3f pointOnPlane;
    Vector3f normalVector;

    // D value of the plane
    float dValue;

public:

    Plane(Point3f point, Vector3f normal): pointOnPlane(point), normalVector(normal){
        Vector3f pointPos = Vector3f{pointOnPlane};
        dValue = normalVector.Dot(pointPos);
    }

    Point3f FindIntersectionPoint(Line3f line){
        
        Vector3f lineDirectionVector = line.GetDirectionVector();
        Point3f lineStartPoint = line.GetStartPoint();
        Vector3f LoPo = Vector3f{lineStartPoint, pointOnPlane};

        float t = normalVector.Dot(LoPo) / normalVector.Dot(lineDirectionVector);

        return Point3f{
            lineStartPoint.x + t * lineDirectionVector.a[0],
            lineStartPoint.y + t * lineDirectionVector.a[1],
            lineStartPoint.z + t * lineDirectionVector.a[2]
        };
    }

    bool IsOnPositiveSide(Point3f point){

        Vector3f pointPos = Vector3f{point};
        return (normalVector.Dot(pointPos) - dValue) > 0;

    }

};


}