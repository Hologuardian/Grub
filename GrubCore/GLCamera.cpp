#include "GLCamera.h"

GLCamera::GLCamera(Vector3 position, Vector3 lookAt, Vector3 up, GLuint program)
{
	cameraMatrix = glGetUniformLocation(program, "camera_matrix");
	projMatrixLoc = glGetUniformLocation(program, "proj_matrix");
	Persepective(75.0f, 1.777778f, 0.1f, 100.0f);
	Move(position);
	Look(lookAt, up);
}
GLCamera::GLCamera(Vector3 position, Vector3 lookAt, Vector3 up, float fov, float aspect, float nearPlane, float farPlane, GLuint program)
{
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
void GLCamera::Move(Vector3 position)
{
	view = glm::translate(view, position);
	glUniformMatrix4fv(cameraMatrix, 1, GL_FALSE, &view[0][0]);

}
void GLCamera::Look(Vector3 target, Vector3 up)
{
	view = glm::lookAt(Vector3(view[3]), target, up);
	glUniformMatrix4fv(cameraMatrix, 1, GL_FALSE, &view[0][0]);
}