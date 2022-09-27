#pragma once
#include "cell.hpp"
#include <vector>
#include <glm/glm.hpp>

namespace life
{
	struct vertex
	{
		glm::vec3 position;
		glm::vec3 color;
	};
	class grid
	{
	 private:
		std::vector<std::vector<cell>> data;
		glm::vec3 calculate_color(cell c) const;
		int n;
		std::vector<vertex> calculate_vertices(int width) const;
		std::vector<int> calculate_indices() const;
	 public:
		grid(int n); // creates an n by n grid
		void update_cell(int r, int c, bool state, int time);
		void draw() const;
	};

}