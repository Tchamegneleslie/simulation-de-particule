//#pragma one
#ifndef VECTOR2_H_INCLUDED
#define VECTOR2_H_INCLUDED
#include <cmath>


struct Vector2 {
    float x = 0.0f;
    float y = 0.0f;

    Vector2() = default;
    
    Vector2(float x_, float y_) : x(x_), y(y_){}
    
    Vector2 operator+(const Vector2& vec) const { return {x + vec.x, y + vec.y}; }
    Vector2 operator-(const Vector2& vec) const { return {x - vec.x, y - vec.y}; }
    Vector2 operator*(float s) const { return {x * s, y * s}; }
    Vector2 operator+=(const Vector2& vec) { x += vec.x, y += vec.y; return *this;}
    float Lenght() const { return std::sqrt(x * x + y * y);}
    Vector2 Normalized() const { 
        float l = Lenght();
        return l > 0 ? Vector2{x / l, y / l} : Vector2{0, 0};
    }
    void Clamp( float max ){
        float len = Lenght();
        if(len > max){
            float scale = max / len;
            x *= scale;
            y *= scale;
        }
    }

};

#endif