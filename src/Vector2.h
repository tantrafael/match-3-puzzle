#pragma once

struct Vector2
{
    float x;
    float y;
    
    Vector2();
    Vector2(const float x, const float y);
    Vector2(const int x, const int y);

    Vector2 operator + (const Vector2& v) const;
    Vector2 operator - (const Vector2& v) const;
    Vector2 operator * (const float t) const;
    Vector2 operator / (const float t) const;
    Vector2 operator - () const;
    bool operator == (const Vector2& v) const;
    bool operator != (const Vector2& v) const;
    void operator += (const Vector2& v);
    void operator -= (const Vector2& v);
    float sqrMagnitude();
    float magnitude();
    Vector2 normalized();

    static Vector2 zero, one, left, right, down, up;
};

