#include "GLWindow.h"

GLWindow::GLWindow()
{
	Logger::Log(EMessageType::LOG_INFO, "Constructing GL Window");
}

GLuint modelMatrix;
GLuint cameraMatrix; 
GLuint projMatrixLoc;

void GLWindow::MakeWindow(int argc,char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(0, 0);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutCreateWindow("Grub");
	//glutFullScreen();

	glewInit();
	
	glEnable(GL_DEPTH_TEST);

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};
	program = LoadShaders(shaders);

	ShaderInfo uishaders[] = {
		{GL_VERTEX_SHADER, "uiShader.vert}"},
		{ GL_NONE, NULL }
	};
	uiprogram = LoadShaders(uishaders);
	glUseProgram(program);

	camera = new GLCamera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0), program);

	modelMatrix = glGetUniformLocation(program, "model_matrix");
}

void GLWindow::SetDisplay(void (Display)()) {
	Logger::Log(EMessageType::LOG_INFO, "Setting display function");
	glutDisplayFunc(Display);
}

void GLWindow::SetKeyDownInput(void(*KeyboardDown)(unsigned char key, int x, int y))
{
	Logger::Log(EMessageType::LOG_INFO, "Setting KeyboardDown input function");
	glutKeyboardFunc(KeyboardDown);
}

void GLWindow::SetKeyUpInput(void(*KeyboardUp)(unsigned char key, int x, int y))
{
	Logger::Log(EMessageType::LOG_INFO, "Setting KeyboardUp input function");
	glutKeyboardUpFunc(KeyboardUp);
}

void GLWindow::SetMouseClickInput(void(*Click)(int button, int state, int x, int y))
{
	Logger::Log(EMessageType::LOG_INFO, "Setting Click input function");
	glutMouseFunc(Click);
}

void GLWindow::SetMouseMoveInput(void(*Move)(int x, int y))
{
	Logger::Log(EMessageType::LOG_INFO, "Setting Move input function");
	glutPassiveMotionFunc(Move);
}

void GLWindow::SetMouseDragInput(void(*Drag)(int x, int y))
{
	Logger::Log(EMessageType::LOG_INFO, "Setting Drag input function");
	glutMotionFunc(Drag);
}

void GLWindow::SetSpecialKeyDownInput(void(*SpecialDown)(int key, int x, int y))
{
	Logger::Log(EMessageType::LOG_INFO, "Setting SpecialDown input function");
	glutSpecialFunc(SpecialDown);
}

void GLWindow::SetSpecialKeyUpInput(void(*SpecialUp)(int key, int x, int y))
{
	Logger::Log(EMessageType::LOG_INFO, "Setting SpecialUp input function");
	glutSpecialUpFunc(SpecialUp);
}

void GLWindow::SetUpdate(void (UpdateCallBack)()) {
	Logger::Log(EMessageType::LOG_INFO, "Setting update function");
	glutIdleFunc(UpdateCallBack);
}

void GLWindow::begin()
{
	glutMainLoop();
}

Camera* GLWindow::GetCamera()
{
	return camera;
}

void GLWindow::startRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWindow::endRender()
{
	glutSwapBuffers();
}

void GLWindow::renderPrimitive(Primitive prim, Grubuint VAO, int start, int length)
{
	glBindVertexArray(VAO);

	glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, &glm::mat4(1.0)[0][0]);
	switch (prim)
	{
	case Primitive::QUAD:
		glDrawArrays(GL_QUADS, start, length);
	case Primitive::TRI:
		glDrawArrays(GL_TRIANGLES, start, length);
	}
	glBindVertexArray(0);
}

void GLWindow::renderModel(Model * model)
{
	glm::mat4 model_view = model->modelMatrix;

	glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, &model_view[0][0]);

	//glDrawArrays(GL_TRIANGLES, 0, model->vertexCount);
}

void GLWindow::testDraw(glm::vec3 pos, int c)
{
	//glUseProgram(uiprogram);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0, 0, 0);
	//glScalef(0.1f, 0.1f, 0.1f);
	glColor3f(1.0f, 0.0f, 1.0f);
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 65);
	glPopMatrix();
	//glUseProgram(program);
}

GLWindow::~GLWindow()
{
}
