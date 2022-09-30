//
// Created by Bacal Mesfin on 2022-09-30.
//

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "camera.hpp"
namespace life
{

	camera::camera(glm::vec2 position, int ratio)
	:position{position},ratio{ratio}
	{
		adjust_projection();
	}

	void camera::adjust_projection()
	{
		projection_matrix = glm::mat4(1.0f);
		projection_matrix = glm::ortho(0.0f,40.0f*ratio,40.0f*ratio,0.0f,0.0f,100.0f);
	}
	glm::mat4 camera::get_view_matrix()
	{
		auto front = glm::vec3(0.0f,0.0f,-1.0f);
		auto up = glm::vec3(0.0f,1.0f,0.0f);
		view_matrix = glm::lookAt(glm::vec3(position.x,position.y,20.0f),front+glm::vec3(position.x,position.y,0.0f),up);
		return view_matrix;
	}
glm::mat4 camera::get_projection_matrix()
{
	return projection_matrix;
}
}