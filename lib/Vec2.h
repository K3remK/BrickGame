#pragma once

class Vec2
{
public:
    Vec2();
    Vec2(float x, float y);
    Vec2& operator=(const Vec2& rhs);
    Vec2 operator+(const Vec2& rhs) const;
    Vec2& operator+=(const Vec2& rhs);
    Vec2 operator-(const Vec2& rhs) const;
    Vec2& operator-=(const Vec2& rhs);
    Vec2 operator*(const float val) const;
    Vec2& operator*=(const float val);
    float GetLength() const;
    float GetLengthSq() const;
    Vec2& Normalize();
    Vec2 GetNormalized() const;
public:
    float x, y;        
};