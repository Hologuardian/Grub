#include "OpenGLWindow.h"

OpenGLWindow::OpenGLWindow()
{
	Logger::Log(EMessageType::LOG_INFO, "Constructing GL Window");
}

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLuint location;
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

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	GLfloat vertices[NumVertices][3] = {
		//{ -0.10,  0, -0.10 }, // Square
		//{ 0.1, 0, -0.10 },
		//{ 0.10, 0, 0.10 },
		//{ -0.1, 0, 0.10 },
		//{ -0.10,  0, -0.10 }, // Square
		//{ 0.1, 0, -0.10 },
		//{ 0.10, 0, 0.10 },
		//{ -0.1, 0, 0.10 }
		{ 0.1,0.1,-0.1 },
		{ 0.1,0.1,0.1 },
		{ -0.1,0.1,0.1 },
		{ -0.1,0.1,-0.1 },//
		{ 0.1,-0.1,-0.1 },
		{ 0.1,-0.1,0.1 },
		{ -0.1,-0.1,0.1 },
		{ -0.1,-0.1,-0.1 },//
		{ 0.1,-0.1,0.1 },
		{ 0.1,0.1,0.1 },
		{ 0.1,0.1,-0.1 },
		{ 0.1,-0.1,-0.1 },//
		{ -0.1,-0.1,0.1 },
		{ -0.1,0.1,0.1 },
		{ -0.1,0.1,-0.1 },
		{ -0.1,-0.1,-0.1 },//
		{ -0.1,0.1,0.1 },
		{ 0.1,0.1,0.1 },
		{ 0.1,-0.1,0.1 },
		{ -0.1,-0.1,0.1 },//
		{ -0.1,0.1,-0.1 },
		{ 0.1,0.1,-0.1 },
		{ 0.1,-0.1,-0.1 },
		{ -0.1,-0.1,-0.1 }//
	};

	GLfloat colorData[NumVertices][3] = {
		//{ 0,1,0 },
		//{ 0,1,0 },
		//{ 0,1,0 },
		//{ 0,1,0 },//
		//{ 0,0.8f,0 },
		//{ 0,0.8f,0 },
		//{ 0,0.8f,0 },
		//{ 0,0.8f,0 }//
		{ 0,1,0 },
		{ 0,1,0 },
		{ 0,1,0 },
		{ 0,1,0 },//
		{ 0,1,1 },
		{ 0,1,1 },
		{ 0,1,1 },
		{ 0,1,1 },//
		{ 1,0,1 },
		{ 1,0,1 },
		{ 1,0,1 },
		{ 1,0,1 },//
		{ 0,0,1 },
		{ 0,0,1 },
		{ 0,0,1 },
		{ 0,0,1 },//
		{ 1,1,1 },
		{ 1,1,1 },
		{ 1,1,1 },
		{ 1,1,1 }//
	};

	glGenBuffers(2, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindAttribLocation(program, 0, "vPosition");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);
	glBindAttribLocation(program, 1, "vertexColor");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(1);
	


	location = glGetUniformLocation(program, "model_matrix");
	cameraMatrix = glGetUniformLocation(program, "camera_matrix");
	projMatrixLoc = glGetUniformLocation(program, "proj_matrix");

	glm::mat4 proj = glm::perspective(45.0f, screenWidth / screenHeight, 0.1f, 100.0f);
	glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &proj[0][0]);
}

void OpenGLWindow::SetDisplay(void (Display)()) {
	Logger::Log(EMessageType::LOG_INFO, "Setting display function");
	glutDisplayFunc(Display);
	glutMainLoop();
}

void OpenGLWindow::SetUpdate(void (UpdateCallBack)()) {
	Logger::Log(EMessageType::LOG_INFO, "Setting update function");
	glutIdleFunc(UpdateCallBack);
}

void OpenGLWindow::startRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLWindow::endRender()
{
	glutSwapBuffers();
}

void OpenGLWindow::renderPrimitive(PrimativeType prim)
{
}

void OpenGLWindow::renderModel(Model * model)
{

	glm::mat4 model_view = model->modelMatrix;

	glUniformMatrix4fv(location, 1, GL_FALSE, &model_view[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, model->vertexCount);
}

float i = 0.0f;
void OpenGLWindow::testDraw(glm::vec3 pos, int c, glm::vec3 cam)
{
	i += 0.0005f;
	Logger::Log(EMessageType::LOG_UPDATE, "Test Draw Start");
	Logger::Log(EMessageType::LOG_UPDATE, "Rotate Value: " + std::to_string(i));

	glm::mat4 model_view = glm::translate(glm::mat4(1.0), pos);
	//model_view = glm::rotate(model_view, i, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(location, 1, GL_FALSE, &model_view[0][0]);
	glm::vec3 tar = cam - glm::vec3(0, 2.0f, 5.0f);
	glm::mat4 camMat = glm::lookAt(cam, tar, glm::vec3(0.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(cameraMatrix, 1, GL_FALSE, &camMat[0][0]);

	glDrawArrays(GL_QUADS, 4 * c, NumVertices);
	Logger::Log(EMessageType::LOG_UPDATE, "Test Draw End");
}

OpenGLWindow::~OpenGLWindow()
{
}
