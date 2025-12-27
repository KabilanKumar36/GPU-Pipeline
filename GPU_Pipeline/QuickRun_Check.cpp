#include "glad\glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


void Not_main()
{
	/*glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* pWindow = glfwCreateWindow(600, 800, "OpenGL Check", NULL, NULL);
	glfwMakeContextCurrent(pWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return;

	int iNrAttribs = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &iNrAttribs);
	std::cout << "No. of maximum Vertex Attributes : " << iNrAttribs << std::endl;*/
	glm::vec4 vec(1.0f, 1.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(1.0f, 5.0f, 1.0f));
	vec = trans * vec;
	std::cout << "Output Vector :" << vec.x << ", " << vec.y << ", " << vec.z << std::endl;
}