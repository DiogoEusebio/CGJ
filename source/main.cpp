///////////////////////////////////////////////////////////////////////////////
//
// Drawing two instances of a triangle in Clip Space.
// A "Hello 2D World" of Modern OpenGL.
//
// (c)2013-20 by Carlos Martinho
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <math.h> 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../header/MasterHeader.h"

#define VERTICES 0
#define COLORS 1
#define PI 3.14159265

GLuint VaoId, VboId[2];
GLuint VertexShaderId, FragmentShaderId, ProgramId;
GLint ModelID, ViewID, ProjectionID, ColorID;
egn::Camera camera = egn::Camera::Camera();
egn::vec3 eye = egn::vec3(0.0f, 0.0f, 5.0f);
egn::vec3 center = egn::vec3(0.0f, 0.0f, -1.0f);
egn::vec3 up = egn::vec3(0.0f, 1.0f, 0.0f);

#define ERROR_CALLBACK
#ifdef  ERROR_CALLBACK

void printGLMatrix(GLfloat* matrix) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << matrix[i + j * 4] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
////////////////////////////////////////////////// ERROR CALLBACK (OpenGL 4.3+)

static const std::string errorSource(GLenum source)
{
	switch (source) {
	case GL_DEBUG_SOURCE_API:				return "API";
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:		return "window system";
	case GL_DEBUG_SOURCE_SHADER_COMPILER:	return "shader compiler";
	case GL_DEBUG_SOURCE_THIRD_PARTY:		return "third party";
	case GL_DEBUG_SOURCE_APPLICATION:		return "application";
	case GL_DEBUG_SOURCE_OTHER:				return "other";
	default:								exit(EXIT_FAILURE);
	}
}

static const std::string errorType(GLenum type)
{
	switch (type) {
	case GL_DEBUG_TYPE_ERROR:				return "error";
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:	return "deprecated behavior";
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:	return "undefined behavior";
	case GL_DEBUG_TYPE_PORTABILITY:			return "portability issue";
	case GL_DEBUG_TYPE_PERFORMANCE:			return "performance issue";
	case GL_DEBUG_TYPE_MARKER:				return "stream annotation";
	case GL_DEBUG_TYPE_PUSH_GROUP:			return "push group";
	case GL_DEBUG_TYPE_POP_GROUP:			return "pop group";
	case GL_DEBUG_TYPE_OTHER_ARB:			return "other";
	default:								exit(EXIT_FAILURE);
	}
}

static const std::string errorSeverity(GLenum severity)
{
	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH:			return "high";
	case GL_DEBUG_SEVERITY_MEDIUM:			return "medium";
	case GL_DEBUG_SEVERITY_LOW:				return "low";
	case GL_DEBUG_SEVERITY_NOTIFICATION:	return "notification";
	default:								exit(EXIT_FAILURE);
	}
}

static void error(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam)
{
	std::cerr << "GL ERROR:" << std::endl;
	std::cerr << "  source:     " << errorSource(source) << std::endl;
	std::cerr << "  type:       " << errorType(type) << std::endl;
	std::cerr << "  severity:   " << errorSeverity(severity) << std::endl;
	std::cerr << "  debug call: " << std::endl << message << std::endl;
	std::cerr << "Press <return>.";
	std::cin.ignore();
}

void setupErrorCallback()
{
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(error, 0);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, 0, GL_FALSE);
	// params: source, type, severity, count, ids, enabled
}

#else // ERROR_CALLBACK

///////////////////////////////////////////////// ERROR HANDLING (All versions)

static const std::string errorString(GLenum error)
{
	switch (error) {
	case GL_NO_ERROR:
		return "No error has been recorded.";
	case GL_INVALID_ENUM:
		return "An unacceptable value is specified for an enumerated argument.";
	case GL_INVALID_VALUE:
		return "A numeric argument is out of range.";
	case GL_INVALID_OPERATION:
		return "The specified operation is not allowed in the current state.";
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		return "The framebuffer object is not complete.";
	case GL_OUT_OF_MEMORY:
		return "There is not enough memory left to execute the command.";
	case GL_STACK_UNDERFLOW:
		return "An attempt has been made to perform an operation that would cause an internal stack to underflow.";
	case GL_STACK_OVERFLOW:
		return "An attempt has been made to perform an operation that would cause an internal stack to overflow.";
	default: exit(EXIT_FAILURE);
	}
}

static bool isOpenGLError()
{
	bool isError = false;
	GLenum errCode;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		std::cerr << "OpenGL ERROR [" << errorString(errCode) << "]." << std::endl;
	}
	return isError;
}

static void checkOpenGLError(std::string error)
{
	if (isOpenGLError()) {
		std::cerr << error << std::endl;
		exit(EXIT_FAILURE);
	}
}

#endif // ERROR_CALLBACK

/////////////////////////////////////////////////////////////////////// SHADERs

const GLchar* VertexShader =
{
	"#version 330 core\n"

	"in vec4 in_Position;\n"
	"in vec4 in_Color;\n"
	"out vec4 ex_Color;\n"

	"uniform mat4 ModelMatrix;\n"

	"uniform mat4 ViewMatrix;\n"
	"uniform mat4 ProjectionMatrix;\n"

	"void main(void)\n"
	"{\n"
	"	gl_Position = ProjectionMatrix * (ViewMatrix * (ModelMatrix * in_Position));\n"
	"	ex_Color = in_Color;\n"
	"}\n"
};

const GLchar* FragmentShader =
{
	"#version 330 core\n"

	"in vec4 ex_Color;\n"
	"out vec4 out_Color;\n"

	"uniform vec4 Color;\n"

	"void main(void)\n"
	"{\n"
	"	out_Color = Color;\n"
	"}\n"
};

void createShaderProgram()
{
	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, 0);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, 0);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);

	glBindAttribLocation(ProgramId, VERTICES, "in_Position");
	glBindAttribLocation(ProgramId, COLORS, "in_Color");

	glLinkProgram(ProgramId);
	ModelID = glGetUniformLocation(ProgramId, "ModelMatrix");
	ViewID = glGetUniformLocation(ProgramId, "ViewMatrix");
	ProjectionID = glGetUniformLocation(ProgramId, "ProjectionMatrix");
	ColorID = glGetUniformLocation(ProgramId, "Color");

	glDetachShader(ProgramId, VertexShaderId);
	glDeleteShader(VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);
	glDeleteShader(FragmentShaderId);

#ifndef ERROR_CALLBACK
	checkOpenGLError("ERROR: Could not create shaders.");
#endif
}

void destroyShaderProgram()
{
	glUseProgram(0);
	glDeleteProgram(ProgramId);

#ifndef ERROR_CALLBACK
	checkOpenGLError("ERROR: Could not destroy shaders.");
#endif
}

/////////////////////////////////////////////////////////////////////// VAOs & VBOs

typedef struct
{
	GLfloat XYZW[4];
	GLfloat RGBA[4];
} Vertex;


Vertex Vertices[] =
{
	{{ 0.0f, 0.0f, 0.0f, 1.0f }, { 0.4, 0.498, 0.960 }},
	{{ 0.25f, 0.0f, 0.0f, 1.0f }, { 0.4, 0.498, 0.960 }},
	{{ 0.25f, 0.25f, 0.0f, 1.0f }, { 0.4, 0.498, 0.960 }},
	{{ 0.0f, 0.0f, 0.0f, 1.0f }, { 0.4, 0.498, 0.960 }},
	{{ 0.25f, 0.25f, 0.0f, 1.0f }, { 0.4, 0.498, 0.960 }},
	{{ 0.0f, 0.25f, 0.0f, 1.0f }, { 0.4, 0.498, 0.960 }},
};

/*
const Vertex Vertices[] =
{
	{{ 0.25f, 0.25f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }},
	{{ 0.75f, 0.25f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }},
	{{ 0.50f, 0.75f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }}
};*/

const GLubyte Indices[] =
{
	0,1,2,3,4,5,0,2,1,3,5,4
};

void createBufferObjects()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	{
		glGenBuffers(2, VboId);

		glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(VERTICES);
			glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glEnableVertexAttribArray(COLORS);
			glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(Vertices[0].XYZW));
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
		}
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

#ifndef ERROR_CALLBACK
	checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
#endif
}

void destroyBufferObjects()
{
	glBindVertexArray(VaoId);
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(COLORS);
	glDeleteBuffers(2, VboId);
	glDeleteVertexArrays(1, &VaoId);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

#ifndef ERROR_CALLBACK
	checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
#endif
}

/////////////////////////////////////////////////////////////////////// SCENE

typedef GLfloat Matrix[16];

const Matrix I = {
	1.0f , 0.0f,  0.0f, 0.0f,
	0.0f , 1.0f,  0.0f, 0.0f,
	0.0f,  0.0f,  1.0f, 0.0f,
	0.0f,  0.0f,  0.0f, 1.0f
};


GLfloat glViewMatrix[16];
GLfloat glProjectionMatrix[16];
GLfloat glDebugMatrix[16];


void createSquare(float sidelenght, egn::mat4 transformMatrix, float red, float green, float blue)
{
	GLfloat vec[16];
	transformMatrix.convertToGL(vec);
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, vec);
	glUniform4f(ColorID, red, green, blue, 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (GLvoid*)0);
	glUniform4f(ColorID, red * 0.5, green * 0.5, blue * 0.5, 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (GLvoid*)(sizeof(GLubyte) * 6));

}


void drawTetraminoLine(float sidelenght, egn::mat4 transformMatrix)
{
	egn::mat4 myTransform = transformMatrix;
	egn::mat4 nextTransform = egn::mat4::identityMatrix();

	nextTransform.data[1][3] += sidelenght + 0.05;

	for (int i = 0; i < 4; i++)
	{
		createSquare(0.25f, myTransform, 1.0f, 0.454f, 0.121f);
		myTransform *= nextTransform;
	}
}

void drawTetraminoeRightL(float sidelenght, egn::mat4 transformMatrix)
{
	egn::mat4 myTransform = transformMatrix;
	egn::mat4 nextTransform = egn::mat4::identityMatrix();
	nextTransform.data[1][3] += sidelenght + 0.05; //change y

	createSquare(0.25, myTransform, 0.349f, 0.839f, 0.0f);
	myTransform *= nextTransform;
	createSquare(0.25, myTransform, 0.349f, 0.839f, 0.0f);
	myTransform *= nextTransform;
	createSquare(0.25, myTransform, 0.349f, 0.839f, 0.0f);

	nextTransform.data[1][3] -= sidelenght + 0.05; //change y
	nextTransform.data[0][3] -= sidelenght + 0.05; //change x
	myTransform *= nextTransform;
	createSquare(0.25, myTransform, 0.349f, 0.839f, 0.0f);
}
void drawTetraminoeLeftL(float sidelenght, egn::mat4 transformMatrix)
{
	egn::mat4 myTransform = transformMatrix;
	egn::mat4 nextTransform = egn::mat4::identityMatrix();
	nextTransform.data[1][3] += sidelenght + 0.05; //change y

	createSquare(0.25, myTransform, 0.901f, 0.239f, 0.850f);
	myTransform *= nextTransform;
	createSquare(0.25, myTransform, 0.901f, 0.239f, 0.850f);
	myTransform *= nextTransform;
	createSquare(0.25, myTransform, 0.901f, 0.239f, 0.850f);

	nextTransform.data[1][3] -= sidelenght + 0.05; //change y
	nextTransform.data[0][3] += sidelenght + 0.05; //change x
	myTransform *= nextTransform;
	createSquare(0.25, myTransform, 0.901f, 0.239f, 0.850f);
}
void drawTetraminoeT(float sidelenght, egn::mat4 transformMatrix)
{
	egn::mat4 myTransform = transformMatrix;
	egn::mat4 nextTransform = egn::mat4::identityMatrix();
	nextTransform.data[0][3] += sidelenght + 0.05;

	createSquare(0.25, myTransform, 0.8f, 0.0f, 0.0f);
	myTransform *= nextTransform;
	createSquare(0.25, myTransform, 0.8f, 0.0f, 0.0f);
	myTransform *= nextTransform;
	createSquare(0.25, myTransform, 0.8f, 0.0f, 0.0f);
	nextTransform.data[0][3] -= 2 * (sidelenght + 0.05); //change x
	nextTransform.data[1][3] -= sidelenght + 0.05; //change y

	myTransform *= nextTransform;
	createSquare(0.25, myTransform, 0.0f, 0.0f, 0.0f);
}
void drawTetraminoeCube(float sidelenght, egn::mat4 transformMatrix)
{
	egn::mat4 myTransform = transformMatrix;
	egn::mat4 nextTransform = egn::mat4::identityMatrix();
	nextTransform.data[0][3] = sidelenght + 0.05;

	createSquare(0.25, myTransform, 0.980f, 0.988f, 0.309f);
	myTransform *= nextTransform;
	createSquare(0.25, myTransform, 0.980f, 0.988f, 0.309f);
	nextTransform.data[0][3] = -(sidelenght + 0.05); //reset x
	nextTransform.data[1][3] -= sidelenght + 0.05; //change y
	myTransform *= nextTransform;
	createSquare(0.25, myTransform, 0.980f, 0.988f, 0.309f);
	nextTransform.data[1][3] = 0; //reset y
	nextTransform.data[0][3] = sidelenght + 0.05; //change x
	myTransform *= nextTransform;
	createSquare(0.25, myTransform, 0.980f, 0.988f, 0.309f);
}
void drawTetraminoeS(float sidelenght, egn::mat4 transformMatrix)
{
	egn::mat4 myTransform = transformMatrix;
	egn::mat4 nextTransform = egn::mat4::identityMatrix();
	nextTransform.data[0][3] = sidelenght + 0.05;

	createSquare(0.25, myTransform, 0.309f, 0.988f, 0.878f);
	myTransform *= nextTransform;
	createSquare(0.25, myTransform, 0.309f, 0.988f, 0.878f);
	nextTransform.data[0][3] = -sidelenght - 0.05; //reset x
	nextTransform.data[1][3] -= sidelenght + 0.05; //change y
	myTransform *= nextTransform;
	createSquare(0.25, myTransform, 0.309f, 0.988f, 0.878f);
	nextTransform.data[1][3] = 0; //reset y
	myTransform *= nextTransform;
	createSquare(0.25, myTransform, 0.309f, 0.988f, 0.878f);
}
void drawTetraminoeSinverted(float sidelenght, egn::mat4 transformMatrix)
{
	egn::mat4 myTransform = transformMatrix;
	egn::mat4 nextTransform = egn::mat4::identityMatrix();
	nextTransform.data[0][3] = sidelenght + 0.05;

	createSquare(0.25, myTransform, 0.678f, 0.0f, 0.878f);
	myTransform *= nextTransform;
	createSquare(0.25, myTransform, 0.678f, 0.0f, 0.878f);
	nextTransform.data[0][3] = 0; //reset x
	nextTransform.data[1][3] -= sidelenght + 0.05; //change y
	myTransform *= nextTransform;
	createSquare(0.25, myTransform, 0.678f, 0.0f, 0.878f);
	nextTransform.data[1][3] = 0; //reset y
	nextTransform.data[0][3] = sidelenght + 0.05; //change x
	myTransform *= nextTransform;
	createSquare(0.25, myTransform, 0.678f, 0.0f, 0.878f);
}

void drawScene()
{
	// Drawing directly in clip space

	glBindVertexArray(VaoId);
	glUseProgram(ProgramId);
	glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, glProjectionMatrix);
	glUniformMatrix4fv(ViewID, 1, GL_FALSE, glViewMatrix);
	float sidelenght = 0.25;
	egn::mat4 rotation = egn::mat4(cos(45 * PI / 180), -sin(45 * PI / 180), 0.0f, -0.25f,
		sin(45 * PI / 180), cos(45 * PI / 180), 0.0f, 0.25f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	egn::mat4 LRight = egn::mat4(cos(PI), -sin(PI), 0.0f, -(sidelenght + 0.05),
		sin(PI), cos(PI), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	egn::mat4 LLeftnorot = egn::mat4(cos(PI), -sin(PI), 0.0f, -(sidelenght + 0.05),
		sin(PI), cos(PI), 0.0f, (sidelenght + 0.05),
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	egn::mat4 LLeft = egn::mat4(cos(270 * PI / 180), -sin(270 * PI / 180), 0.0f, -1.65 * (sidelenght + 0.05) - 0.05,
		sin(270 * PI / 180), cos(270 * PI / 180), 0.0f, (sidelenght + 0.05),
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	egn::mat4 Line = egn::mat4(cos(PI), -sin(PI), 0.0f, 2 * (sidelenght + 0.05),
		sin(PI), cos(PI), 0.0f, (sidelenght + 0.05),
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	egn::mat4 S = egn::mat4(cos(90 * PI / 180), -sin(90 * PI / 180), 0.0f, 0.0f,
		sin(90 * PI / 180), cos(90 * PI / 180), 0.0f, -2 * sidelenght - 0.05,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	drawTetraminoLine(sidelenght, rotation * Line);
	drawTetraminoeRightL(sidelenght, rotation * LRight);
	drawTetraminoeLeftL(sidelenght, rotation * LLeft);
	//drawTetraminoeT(sidelenght, InitialTransform);
	//drawTetraminoeCube(sidelenght, InitialTransform);
	drawTetraminoeS(sidelenght, rotation * S);
	//drawTetraminoeSinverted(sidelenght, InvertedS);

	glUseProgram(0);
	glBindVertexArray(0);

#ifndef ERROR_CALLBACK
	checkOpenGLError("ERROR: Could not draw scene.");
#endif
}

///////////////////////////////////////////////////////////////////// CALLBACKS

void window_close_callback(GLFWwindow* win)
{
	destroyShaderProgram();
	destroyBufferObjects();
}

void window_size_callback(GLFWwindow* win, int winx, int winy)
{
	glViewport(0, 0, winx, winy);
}

void glfw_error_callback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
}

void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	std::cout << "key: " << key << " " << scancode << " " << action << " " << mods << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(win, GLFW_TRUE);
		window_close_callback(win);
	}
	if (key == GLFW_KEY_P && action == 1) {
		camera.switchProjectionMatrix();
		camera.getProjectionMatrix().convertToGL(glProjectionMatrix);
	}

	if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{	
		camera.addTranslation(egn::vec3(0.1f, 0.0f, 0.0f));
		camera.getViewMatrix().convertToGL(glViewMatrix);
		/*
		egn::vec3 view = egn::vec3(center);
		view -= eye;
		egn::vec3 v = egn::vec3::normalize(view);
		eye += (egn::vec3(v.z, 0, -v.x) * 0.2);
		center += (egn::vec3(v.z, 0, -v.x) * 0.2);
		camera.ViewMatrix(eye, center, up);
		camera.getViewMatrix().convertToGL(glViewMatrix);
		*/
	}

	if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{	
		camera.addTranslation(egn::vec3(-0.1f, 0.0f, 0.0f));
		camera.getViewMatrix().convertToGL(glViewMatrix);
		/*
		egn::vec3 view = egn::vec3(center);
		view -= eye;
		egn::vec3 v = egn::vec3::normalize(view);
		eye -= (egn::vec3(v.z, 0, -v.x) * 0.2);
		center -= (egn::vec3(v.z, 0, -v.x) * 0.2);
		camera.ViewMatrix(eye, center, up);
		camera.getViewMatrix().convertToGL(glViewMatrix);
		*/
	}
	if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		camera.addTranslation(egn::vec3(0.0f, 0.0f, 0.1f));

		camera.getViewMatrix().convertToGL(glViewMatrix);
		/*/
		egn::vec3 view = egn::vec3(center);
		view -= eye;
		egn::vec3 v = egn::vec3::normalize(view);
		eye += (v * 0.2);
		center += (v * 0.2);
		camera.ViewMatrix(eye, center, up);
		camera.getViewMatrix().convertToGL(glViewMatrix);
		*/
		}

	if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{	
		camera.addTranslation(egn::vec3(0.0f, 0.0f, -0.1f));
		camera.getViewMatrix().convertToGL(glViewMatrix);
		/*
		egn::vec3 view = egn::vec3(center);
		view -= eye;
		egn::vec3 v = egn::vec3::normalize(view);
		eye -= (v * 0.2);
		center -= (v * 0.2);
		camera.ViewMatrix(eye, center, up);
		camera.getViewMatrix().convertToGL(glViewMatrix);
		*/
	}

	//RESET CAMERA
	if (key == GLFW_KEY_T) {
		camera = egn::Camera::Camera();
		eye = egn::vec3(0.0f, 0.0f, 5.0f);
		center = egn::vec3(0.0f, 0.0f, -1.0f);
		up = egn::vec3(0.0f, 1.0f, 0.0f);
		camera.ViewMatrix(eye, center, up);
		camera.OrthographicProjectionMatrix(-2.0f, 2.0f, -2.0f, 2.0f, 1.0f, 10.0f);
		camera.PerspectiveProjectionMatrix(30.0f, 640.0f / 480.0f, 1.0f, 10.0f);

		camera.getViewMatrix().convertToGL(glViewMatrix);
		camera.getProjectionMatrix().convertToGL(glProjectionMatrix);
		printGLMatrix(glViewMatrix);
		printGLMatrix(glProjectionMatrix);
	}


}

void mouse_callback(GLFWwindow* win, double xpos, double ypos)
{
	//std::cout << "mouse: " << xpos << " " << ypos << std::endl;
	int state = glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS) {
		camera.mouseCallBack((float)xpos, (float)ypos);
		camera.getViewMatrix().convertToGL(glViewMatrix);
		//eye = camera.getEye();
		center = camera.getCenter();

	}
	else
		camera.setFirstMouseMovement(true);
}

void mouse_button_callback(GLFWwindow* win, int button, int action, int mods)
{
	std::cout << "button: " << button << " " << action << " " << mods << std::endl;
}



///////////////////////////////////////////////////////////////////////// SETUP

GLFWwindow* setupWindow(int winx, int winy, const char* title,
	int is_fullscreen, int is_vsync)
{
	GLFWmonitor* monitor = is_fullscreen ? glfwGetPrimaryMonitor() : 0;
	GLFWwindow* win = glfwCreateWindow(winx, winy, title, monitor, 0);
	if (!win)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(win);
	glfwSwapInterval(is_vsync);
	return win;
}

void setupCallbacks(GLFWwindow* win)
{
	glfwSetKeyCallback(win, key_callback);
	glfwSetWindowCloseCallback(win, window_close_callback);
	glfwSetWindowSizeCallback(win, window_size_callback);
	glfwSetCursorPosCallback(win, mouse_callback);
	glfwSetMouseButtonCallback(win, mouse_button_callback);
}

GLFWwindow* setupGLFW(int gl_major, int gl_minor,
	int winx, int winy, const char* title, int is_fullscreen, int is_vsync)
{
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	GLFWwindow* win = setupWindow(winx, winy, title, is_fullscreen, is_vsync);
	setupCallbacks(win);

#if _DEBUG
	std::cout << "GLFW " << glfwGetVersionString() << std::endl;
#endif
	return win;
}

void setupGLEW()
{
	glewExperimental = GL_TRUE;
	// Allow extension entry points to be loaded even if the extension isn't 
	// present in the driver's extensions string.
	GLenum result = glewInit();
	if (result != GLEW_OK)
	{
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	GLenum err_code = glGetError();
	// You might get GL_INVALID_ENUM when loading GLEW.
}

void checkOpenGLInfo()
{
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cerr << "OpenGL Renderer: " << renderer << " (" << vendor << ")" << std::endl;
	std::cerr << "OpenGL version " << version << std::endl;
	std::cerr << "GLSL version " << glslVersion << std::endl;
}

void setupOpenGL(int winx, int winy)
{
#if _DEBUG
	checkOpenGLInfo();
#endif
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glViewport(0, 0, winx, winy);
}

GLFWwindow* setup(int major, int minor,
	int winx, int winy, const char* title, int is_fullscreen, int is_vsync)
{
	GLFWwindow* win =
		setupGLFW(major, minor, winx, winy, title, is_fullscreen, is_vsync);
	setupGLEW();
	setupOpenGL(winx, winy);
#ifdef ERROR_CALLBACK
	setupErrorCallback();
#endif
	createShaderProgram();
	createBufferObjects();
	return win;
}

////////////////////////////////////////////////////////////////////////// RUN

void display(GLFWwindow* win, double elapsed_sec)
{
	drawScene();
}

void run(GLFWwindow* win)
{
	double last_time = glfwGetTime();
	while (!glfwWindowShouldClose(win))
	{
		double time = glfwGetTime();
		double elapsed_time = time - last_time;
		last_time = time;

		// Double Buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		display(win, elapsed_time);
		glfwSwapBuffers(win);
		glfwPollEvents();
#ifndef ERROR_CALLBACK
		checkOpenGLError("ERROR: MAIN/RUN");
#endif
	}
	glfwDestroyWindow(win);
	glfwTerminate();
}

////////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char* argv[])
{
	int gl_major = 4, gl_minor = 3;
	int is_fullscreen = 0;
	int is_vsync = 1;

	camera.ViewMatrix(eye, center, up);
	camera.OrthographicProjectionMatrix(-2.0f, 2.0f, -2.0f, 2.0f, 1.0f, 10.0f);
	camera.PerspectiveProjectionMatrix(30.0f, 640.0f / 480.0f, 1.0f, 10.0f);

	camera.getViewMatrix().convertToGL(glViewMatrix);
	camera.getProjectionMatrix().convertToGL(glProjectionMatrix);
	printGLMatrix(glViewMatrix);
	printGLMatrix(glProjectionMatrix);
	//printGLMatrix((camera.getProjectionMatrix() * camera.getViewMatrix()).convertToGL(glDebugMatrix));

	GLFWwindow* win = setup(gl_major, gl_minor,
		500, 500, "3D assignment", is_fullscreen, is_vsync);
	run(win);
	exit(EXIT_SUCCESS);
}


/////////////////////////////////////////////////////////////////////////// END