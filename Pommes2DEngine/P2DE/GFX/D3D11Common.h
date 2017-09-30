#pragma once

struct P2DE_COLOR4
{ 
	float r, g, b, a;
	P2DE_COLOR4(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f) : r(r), g(g), b(b), a(a){}
};

struct P2DE_RECTF
{ 
	float left, top, bottom, right;
	P2DE_RECTF(float left = 0.0f, float top = 0.0f, float bottom = 0.0f, float right = 0.0f) : left(left), top(top), bottom(bottom), right(right){}
};

struct P2DE_VEC3F
{
	float x, y, z;
	P2DE_VEC3F(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
};