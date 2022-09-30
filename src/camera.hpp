#pragma once
#include <glm/glm.hpp>
namespace life
{

	class camera
	{
	private:
		glm::mat4 projection_matrix;
		glm::mat4 view_matrix;
		glm::vec2 position;
		int ratio;
		void adjust_projection();
	public:
		explicit camera(glm::vec2 position, int grid_size);
		glm::mat4 get_view_matrix();
		glm::mat4 get_projection_matrix();

	};
}
