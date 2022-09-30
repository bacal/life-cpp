#include "opengl.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include "grid.hpp"
#include "shader.hpp"
#include "camera.hpp"
void GLAPIENTRY
MessageCallback( GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam )
{
	fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
			type, severity, message );
}

const int win_size = 800;
const int grid_size = 2;


std::string vertex_src =   		 "#version 410 core\n"
							     "layout(location=0) in vec2 aPos;\n"
							     "layout(location=1) in vec3 aColor;\n"
							     "\n"
								 "uniform mat4 uProj;"
								 "uniform mat4 uView;"
							     "out vec3 fColor;\n"
							     "\n"
							     "void main(){\n"
							     "    gl_Position = uProj*uView*vec4(aPos.x,aPos.y,0.0,1.0);\n"
							     "    fColor=aColor;\n"
							     "}";

std::string frag_src =   "#version 410 core\n"
							   "in vec3 fColor;\n"
							   "out vec4 color;"
							   "\n"
							   "void main(){\n"
							   "    color = vec4(fColor,1.0);\n"
							   "}";


int main(int argc, char** argv){

	if(!glfwInit()){}

	// Request OpenGL 4.1 context if available
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(win_size,win_size,"Conway's Game of Life", nullptr, nullptr);

	if(!window){

	}

	glfwMakeContextCurrent(window);
	if(glewInit() != GLEW_OK)
	{

	}
	glDisable(GL_BLEND);
	glDisable(GL_POLYGON_SMOOTH);
	glClearColor(0x00,0x00,0x00,0x00);
	glEnable              ( GL_DEBUG_OUTPUT );
	glDebugMessageCallback( MessageCallback, 0 );

	life::shader shader{vertex_src,frag_src};
	life::camera camera(glm::vec2(0.0f,0.0f),grid_size);

	life::grid grid{grid_size};
	auto indexes = grid.get_indices();
	auto vertexes = grid.get_vertices();


	vertexes[0].color={1.0f,1.0f,0.0f};
	vertexes[3].color={1.0f,1.0f,0.0f};

	unsigned int vao,vbo,ibo;
	glGenVertexArrays(1,&vao);
	glGenBuffers(1,&vbo);
	glGenBuffers(1,&ibo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,indexes.size()*sizeof(float),indexes.data(),GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,vertexes.size()*sizeof(struct life::vertex),vertexes.data(),GL_STATIC_DRAW);

	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(struct life::vertex),(void*)offsetof(life::vertex,position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(struct life::vertex),(void*)offsetof(life::vertex,color));
	glEnableVertexAttribArray(1);



	std::cout << "Initialized OpenGL\nVersion: " << glGetString(GL_VERSION) << '\n';



	while(!glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT);

		shader.bind();
		shader.push_mat4("uProj",camera.get_projection_matrix());
		shader.push_mat4("uView",camera.get_view_matrix());
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES,indexes.size(),GL_UNSIGNED_INT,0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	life::grid g(5);
	g.update_cell(0,0,true,1);
	g.update_cell(1,1,true,1);

}


