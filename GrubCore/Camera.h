#ifndef GRUB_CAMERA
#define GRUB_CAMERA
#include "Constants.h"

class Camera
{
public:
	Matrix projection;
	Matrix view;

	virtual void Persepective(float fov, float aspect, float nearPlane, float farPlane) = 0;
	virtual void Ortho(float top, float bottom, float left, float right, float nearPlane, float farPlane) = 0;
	virtual void Move(Vector3 position) = 0;
	Vector3 GetPosition();
	Vector3 GetDirection();
	virtual void SetPosition(Vector3 position) = 0;
	virtual void Look(Vector3 target, Vector3 up) = 0;
protected:
	Vector3 position;
	Vector3 direction;
};

#endif