#ifndef GRUB_CAMERA
#define GRUB_CAMERA
#include "Constants.h"

class Camera
{
public:
	Matrix projection;
	Matrix view;

	/**
	Sets the projection matrix to be a perspective projection
	*/
	virtual void Persepective(float fov, float aspect, float nearPlane, float farPlane) = 0;
	/**
	Sets the projection matrix to be a orthographic projection
	*/
	virtual void Ortho(float top, float bottom, float left, float right, float nearPlane, float farPlane) = 0;
	/**
	Moves the camera a specified distance.
	*/
	virtual void Move(Vector3 position) = 0
	/**
	Returns a copy of the camera's position.
	*/;
	Vector3 GetPosition();
	/**
	Returns a copy of the camera's direction.
	*/;
	Vector3 GetDirection();
	/**
	Sets the camera's position, overwriting any position data that may already be there.
	*/;
	virtual void SetPosition(Vector3 position) = 0;
	/**
	Tells the camera to look at a target
	Up vector defines the rotation of the camera
	*/;
	virtual void Look(Vector3 target, Vector3 up) = 0;
protected:
	Vector3 position;
	Vector3 direction;
};

#endif