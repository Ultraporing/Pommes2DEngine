#include "Camera.h"
#include "Graphics.h"

using namespace P2DE::GFX;

Camera::Camera()
{
	m_Graphics = NULL;
	m_CameraPos = D2D1::Point2F();
}

Camera::Camera(P2DE::GFX::Graphics* gfx)
{
	m_Graphics = NULL;
	m_Graphics = gfx;
	m_CameraPos = D2D1::Point2F();
}

Camera::~Camera()
{
	m_Graphics = NULL;
}

void Camera::SetCameraPos(D2D1_POINT_2F newPos)
{
	m_CameraPos = newPos;
	m_Graphics->SetTransform(D2D1::Matrix3x2F::Translation(-m_CameraPos.x, -m_CameraPos.y));
}

void Camera::MoveCamera(D2D1_POINT_2F delta)
{
	m_CameraPos.x += delta.x;
	m_CameraPos.y += delta.y;

	m_Graphics->SetTransform(D2D1::Matrix3x2F::Translation(-m_CameraPos.x, -m_CameraPos.y));
}