#include "Vec2.h"
#include <cmath>

Vec2::Vec2()
    :
    x(0.0f),
    y(0.0f)
    {}

Vec2::Vec2(float x, float y)
    :
    x(x),
    y(y)
    {}

Vec2& Vec2::operator=(const Vec2 & rhs)
{
    this->x = rhs.x;
    this->y = rhs.y;
    return *this;
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
    return Vec2(this->x - rhs.x, this->y - rhs.y);
}

Vec2& Vec2::operator-=(const Vec2& rhs)
{
    *this = *this - rhs;
    return *this;
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
    return Vec2(this->x + rhs.x, this->y + rhs.y);
}

Vec2& Vec2::operator+=(const Vec2& rhs)
{
    return (*this = *this + rhs);
}

Vec2 Vec2::operator*(const float val) const
{
    return Vec2(this->x * val, this->y * val);
}

Vec2& Vec2::operator*=(const float val)
{
    return (*this = *this * val);
}

float Vec2::GetLength() const
{
    return std::sqrt(GetLengthSq());
}

float Vec2::GetLengthSq() const
{
    return (x*x + y*y);
}

Vec2& Vec2::Normalize()
{
    return (*this = GetNormalized());
}

Vec2 Vec2::GetNormalized() const
{
    float l = GetLength();
    if(l != 0.0f)
        return Vec2(x / l, y / l);
    return *this;
}