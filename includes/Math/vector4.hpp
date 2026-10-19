#pragma once

namespace gfx{

struct Vector4f{

    float a[4];
    Vector4f(float a0, float a1, float a2, float a3){
        a[0] = a0;
        a[1] = a1;
        a[2] = a2;
        a[3] = a3;
    }

};

}