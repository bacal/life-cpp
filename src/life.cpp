
/*
 * macOS has is in charge of loading the correct OpenGL functions, no loading library is needed.
 */
#if defined( __APPLE__ )
#define GL_SILENCE_DEPRECATION
#include <OpenGL/GL.h>
#else
#include <GL/glew.h>
#include <GL/gl.h>
#endif

#include <GLFW/glfw3.h>

#include <iostream>
#include "grid.hpp"

const int win_size = 100;

const static std::string vertex_src = "";
const static std::string frag_src = "";


int main(int argc, char** argv){

	if(!glfwInit()){}

	// Request OpenGL 4.1 context if available
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(win_size,win_size,"Conway's Game of Life", nullptr, nullptr);

	if(!window){

	}
	glfwMakeContextCurrent(window);
	glClearColor(0xff,0x00,0xff,0x00);

	std::cout << "Initialized OpenGL\nVersion: " << glGetString(GL_VERSION) << '\n';
	while(!glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT);

		unsigned int vertex_buffer=0,frgment_buffer=0;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	life::grid g(5);
	g.update_cell(0,0,true,1);
	g.update_cell(1,1,true,1);

}


