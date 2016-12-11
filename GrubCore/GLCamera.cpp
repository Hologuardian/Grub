#include "GLCamera.h"
#ifdef GRUB_USEOPENGL

GLCamera::GLCamera(Vector3 position, Vector3 lookAt, Vector3 up, GLuint program)
{
	GLCamera::position = position;
	GLCamera::direction = lookAt;
	cameraMatrix = glGetUniformLocation(program, "camera_matrix");
	projMatrixLoc = glGetUniformLocation(program, "proj_matrix");
	Persepective(45.0f, 1.777778f, 0.1f, 10000.0f);
	Move(position);
	Look(lookAt, up);
}
GLCamera::GLCamera(Vector3 position, Vector3 lookAt, Vector3 up, float fov, float aspect, float nearPlane, float farPlane, GLuint program)
{
	GLCamera::position = position;
	GLCamera::direction = lookAt;
	cameraMatrix = glGetUniformLocation(program, "camera_matrix");
	projMatrixLoc = glGetUniformLocation(program, "proj_matrix");
	Persepective(fov, aspect, nearPlane, farPlane);
	Move(position);
	Look(lookAt, up);
}

void GLCamera::Persepective(float fov, float aspect, float nearPlane, float farPlane)
{
	projection = glm::perspective(fov, aspect, nearPlane, farPlane);
	glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &projection[0][0]);
}
void GLCamera::Ortho(float top, float bottom, float left, float right, float nearPlane, float farPlane)
{
	projection = glm::ortho<GLfloat>(left, right, bottom, top, nearPlane, farPlane);
	glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &projection[0][0]);
}

void GLCamera::Move(const Vector3 position)
{
	Camera::position += position;
	view = glm::translate(view, position);
	glUniformMatrix4fv(cameraMatrix, 1, GL_FALSE, &view[0][0]);

}

void GLCamera::SetPosition(const Vector3 position)
{
	//Camera::position = position;
	//view = glm::translate(view, Camera::position);
	//glUniformMatrix4fv(cameraMatrix, 1, GL_FALSE, &view[0][0]);
}

void GLCamera::Look(const Vector3 direction, const  Vector3 up)
{
	Camera::direction = direction;
	Vector3 look = Camera::direction + Camera::position;
	view = glm::lookAt(Camera::position, look, up);
	glUniformMatrix4fv(cameraMatrix, 1, GL_FALSE, &view[0][0]);
}
#endif