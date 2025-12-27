#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include "source.h"
#include <stdio.h>
#include <iostream>

//*********************************************************************
const char* cVSCode = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform float fOffset;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x + fOffset, aPos.y, aPos.z, 1.0);\n"
"}\0";
//*********************************************************************
const char* cFSCode = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 OurColor;\n"
"void main()\n"
"{\n"
"   FragColor = OurColor;//vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";
//*********************************************************************
int main()

{
	//Initialize glfw...
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(iWidth, iHeight, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Initialize GLAD...
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to Intialize GLAD" << std::endl;
		return -1;
	}

	int iErr = createVertexShader();
	if (!iErr == 1)
		return iErr;
	iErr = createFragmentShader();
	if (!iErr == 1)
		return iErr;

	iErr = createShaderProgram();
	if (iErr != 1)
		return iErr;
	if(bTriangle)
		iErr = drawTriangle();
	else
		iErr = drawRectangle();
	if (iErr != 1)
	{
		if (bTriangle)
			std::cout << "Failed to Draw the Triangle.\n";
		else
			std::cout << "Failed to Draw the Rectangle.\n";
		return -1;
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Rendering loop
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(SP);
		int iLoc = glGetUniformLocation(SP, "fOffset");
		glUniform1f(iLoc, -0.5);
		updateUniformColor();

		glBindVertexArray(VAO);
		if(bTriangle)
			glDrawArrays(GL_TRIANGLES, 0, 3);
		else
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwPollEvents(); //IO events
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(SP);

	//Clear Allocated glfw resources
	glfwTerminate();
	return 0;
}
//*********************************************************************
int updateUniformColor()
{
	float fTimeValue = glfwGetTime();
	float fGreenValue = sin(fTimeValue) / 2.0f + 0.5f;
	int iVertexColorLoc = glGetUniformLocation(SP, "OurColor");
	glUniform4f(iVertexColorLoc, 0.0f, fGreenValue, 0.0f, 1.0f);
	return 1;
}
//*********************************************************************
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
//*********************************************************************
void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		drawTriangle();
	else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		drawRectangle();
}
//*********************************************************************
int drawTriangle()
{
	bTriangle = true;
	float fVerts[] = {
		-0.5,	 -0.5,	 0,
		 0.5,	 -0.5,	 0,
		 0,		  0.5,	 0
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fVerts), fVerts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	return 1;
}
//*********************************************************************
int drawRectangle()
{
	bTriangle = false;
	float fVertices[] = {
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	unsigned int iIndRef[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fVertices), fVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(iIndRef), iIndRef, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return 1;
}
//*********************************************************************
int createVertexShader()
{
	VS = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VS, 1, &cVSCode, NULL);
	glCompileShader(VS);

	int iSuccess;
	glGetShaderiv(VS, GL_COMPILE_STATUS, &iSuccess);
	if (!iSuccess)
	{
		char cInfoLog[512];
		glGetShaderInfoLog(VS, 512, NULL, cInfoLog);
		std::cout << "ERROR: Vertex Shader compilation failed.\n" << cInfoLog << std::endl;
		return 0;
	}
	return 1;
}
//*********************************************************************
int createFragmentShader()
{
	
	FS = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FS, 1, &cFSCode, NULL);
	glCompileShader(FS);

	int iSuccess = 0;
	glGetShaderiv(FS, GL_COMPILE_STATUS, &iSuccess);
	if (!iSuccess)
	{
		char cInfoLog[512];
		glGetShaderInfoLog(FS, 512, NULL, cInfoLog);
		std::cout << "ERROR: Fragment Shader compilation failed.\n" << cInfoLog << std::endl;
		return 0;
	}

	return 1;
}
//*********************************************************************
int createShaderProgram()
{
	SP = glCreateProgram();

	glAttachShader(SP, VS);
	glAttachShader(SP, FS);
	glLinkProgram(SP);

	int iSuccess = 0;
	glGetProgramiv(SP, GL_LINK_STATUS, &iSuccess);
	if (!iSuccess)
	{
		char cInfoLog[512];
		glGetProgramInfoLog(SP, 512, NULL, cInfoLog);
		std::cout << "Link Shader program Failed.\n " << cInfoLog << std::endl;
		return 0;
	}
	glUseProgram(SP);

	glDeleteShader(VS);
	glDeleteShader(FS);

	return 1;
}
