#include "OpenGLWindow.h"

OpenGLWindow::OpenGLWindow()
{
	Logger::Log(EMessageType::LOG_INFO, "Constructing GL Window");
}

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { VertexBuffer, ColorBuffer, TextureBuffer};
enum Attrib_IDs { vPosition = 0 };

GLuint WindowVAO;
GLuint Buffers[3];
GLuint modelMatrix;
GLuint cameraMatrix; 
GLuint projMatrixLoc;
const GLuint NumVertices = 24;
const float screenWidth = 1520;
const float screenHeight = 790;

void OpenGLWindow::MakeWindow(int argc,char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Grub");

	glewInit();
	
	glEnable(GL_DEPTH_TEST);

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};

	program = LoadShaders(shaders);
	glUseProgram(program);
	camera = new GLCamera(glm::vec3(64.0f, 84.0f, 100.0f), glm::vec3(80, 0, 80), glm::vec3(0, 1.0f, 0), program);

	modelMatrix = glGetUniformLocation(program, "model_matrix");
}

void OpenGLWindow::SetDisplay(void (Display)()) {
	Logger::Log(EMessageType::LOG_INFO, "Setting display function");
	glutDisplayFunc(Display);
}

void OpenGLWindow::SetUpdate(void (UpdateCallBack)()) {
	Logger::Log(EMessageType::LOG_INFO, "Setting update function");
	glutIdleFunc(UpdateCallBack);
}

void OpenGLWindow::begin()
{
	glutMainLoop();
}

Camera* OpenGLWindow::GetCamera()
{
	return camera;
}

void OpenGLWindow::startRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLWindow::endRender()
{
	glutSwapBuffers();
}

void OpenGLWindow::renderPrimitive(PrimativeType prim, Grubuint VAO, int start, int length)
{
	glBindVertexArray(VAO);

	glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, &glm::mat4(1.0)[0][0]);

	glDrawArrays(GL_QUADS, start, length);
	glBindVertexArray(0);
}

void OpenGLWindow::renderModel(Model * model)
{

	glm::mat4 model_view = model->modelMatrix;

	glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, &model_view[0][0]);

	//glDrawArrays(GL_TRIANGLES, 0, model->vertexCount);
}

void OpenGLWindow::testDraw(glm::vec3 pos, int c)
{
	//glBindVertexArray(WindowVAO);

	//Logger::Log(EMessageType::LOG_UPDATE, "Test Draw Start");
	//Logger::Log(EMessageType::LOG_UPDATE, "Rotate Value: " + std::to_string(i));

	//glm::mat4 model_view = glm::translate(glm::mat4(1.0), pos);
	////model_view = glm::rotate(model_view, i, glm::vec3(0.0f, 1.0f, 0.0f));
	//glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, &model_view[0][0]);

	//glDrawArrays(GL_QUADS, 4 * c, NumVertices);
	//Logger::Log(EMessageType::LOG_UPDATE, "Test Draw End");
	//glBindVertexArray(0);
}

OpenGLWindow::~OpenGLWindow()
{
}
