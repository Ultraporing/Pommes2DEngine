#pragma once

struct COLOR4
{ 
	float r, g, b, a;
	COLOR4(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f) : r(r), g(g), b(b), a(a){}
};

struct RECTF
{ 
	float left, top, bottom, right;
	RECTF(float left = 0.0f, float top = 0.0f, float bottom = 0.0f, float right = 0.0f) : left(left), top(top), bottom(bottom), right(right){}
};

struct VEC3F
{
	float x, y, z;
	VEC3F(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
};