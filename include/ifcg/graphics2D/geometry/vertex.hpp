#pragma once

class Vertex2D {
public:
    Vertex2D(float x, float y, float r, float g, float b, float a) 
        : x(x), y(y), r(r), g(g), b(b), a(a) {}

    float x, y;
    float r, g, b, a;
};