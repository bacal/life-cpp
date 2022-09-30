#include "grid.hpp"

namespace life{

	grid::grid(int n)
	:n{n}
	{
		data.resize(n);
		for(int i=0; i<n; i++)
		{
			data[i].resize(n);
		}
		calculate_indices();
		calculate_vertices(40);
	}

	std::vector<glm::vec3> grid::calculate_colors(cell c) const
	{
		std::vector<glm::vec3> colors;


		return colors;
	}

	void grid::update_cell(int r, int c, bool state, int time)
	{
		state?data[r][c].animate():data[r][c].kill(time);
	}

	void grid::calculate_indices()
	{
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				// Upper Triangle
				indices.emplace_back(((n+1)*i)+j);
				indices.emplace_back(((n+1)*i)+1+j);
				indices.emplace_back((n+1)*(i+1)+j);

				// Lower Triangle
				indices.emplace_back((n+1)*(i+1)+j);
				indices.emplace_back(((n+1)*(i+1))+1+j);
				indices.emplace_back(j+1);
			}
		}
	}

	void grid::calculate_vertices(int width)
	{
		int scale = width/n;

		for (int i=0; i<n+1; i++)
		{
			for (int j=0; j<n+1; j++)
			{
					vertices.push_back({((i)*scale),((j)*scale)});
			}
		}
	}

	std::vector<int> grid::get_indices() const
	{
		return indices;
	}

	std::vector<vertex> grid::get_vertices() const
	{
		std::vector<vertex> vertexes;
		for(const auto& vertex: vertices)
		{
			vertexes.push_back({glm::vec3(vertex.x,vertex.y,0.0f),glm::vec3(1.0f,1.0f,1.0f)});
		}
		return vertexes;
	}


}