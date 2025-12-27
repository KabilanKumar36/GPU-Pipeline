#pragma once
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);
int drawTriangle();
int drawRectangle();
int createVertexShader();
int createFragmentShader();
int createShaderProgram();
int updateUniformColor();

bool bTriangle = true;
int iWidth = 800;
int iHeight = 600;

unsigned int VBO;
unsigned int VAO;
unsigned int EBO;

unsigned int FS;
unsigned int VS;
unsigned int SP;