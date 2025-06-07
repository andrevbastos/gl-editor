#pragma once

class Vertex3D {
public:
    Vertex3D(float x, float y, float z, float r, float g, float b, float a) 
    : x(x), y(y), z(z), r(r), g(g), b(b), a(a) {}

    float x, y, z;
    float r, g, b, a;
};