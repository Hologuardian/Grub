#ifndef GRUB_GLCAMERA
#define GRUB_GLCAMERA
#include "Camera.h"

#include "opengl\include\glew.h"
#include "opengl\include\glut.h"
#include "glut\include\vgl.h"
#include "glm\glm\gtc\matrix_transform.hpp"

class GLCamera : public Camera
{
public:
	GLCamera(Vector3 position, Vector3 lookAt, Vector3 up, GLuint program);
	GLCamera(Vector3 position, Vector3 lookAt, Vector3 up, float fov, float aspect, float nearPlane, float farPlane, GLuint program);

	/**
	Sets the projection matrix to be a perspective projection
	*/
	void Persepective(float fov, float aspect, float nearPlane, float farPlane) override;
	/**
	Sets the projection matrix to be a orthographic projection
	*/
	void Ortho(float top, float bottom, float left, float right, float nearPlane, float farPlane) override;
	/**
	Moves the camera a specified distance.
	*/
	void Move(Vector3 position) override;
	/**
	Sets the camera's position, overwriting any position data that may already be there.
	*/
	void SetPosition(Vector3 position) override;
	/**
	Tells the camera to look at a target
	Up vector defines the rotation of the camera
	*/
	void Look(Vector3 direction, Vector3 up) override;
private:
	GLuint cameraMatrix;
	GLuint projMatrixLoc;
};

#endif