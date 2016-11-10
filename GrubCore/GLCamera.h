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

	void Persepective(float fov, float aspect, float nearPlane, float farPlane) override;
	void Ortho(float top, float bottom, float left, float right, float nearPlane, float farPlane) override;
	void Move(Vector3 position) override;
	void SetPosition(Vector3 position) override;
	void Look(Vector3 target, Vector3 up) override;
private:
	GLuint cameraMatrix;
	GLuint projMatrixLoc;
};

#endif