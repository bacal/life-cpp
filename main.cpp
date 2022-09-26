#include <iostream>
#include <array>
#include <SDL.h>
const int grid_size = 100;
const int window_width =  800;
const int window_height = 800;
static int sim_time = 0;
int count_neighbors(std::array<std::array<int,grid_size>,grid_size>& grid, int r, int c){
	int count =0;
	if(!(r == grid_size-1 || c==grid_size-1 || r==0 || c==0)){

		for(int i=r-1; i<r+2; i++){
			for (int j = c-1; j < c+2; j++)
			{
				if(!(i==r && j==c) && grid[i][j]){
					count++;
				}
			}
		}

	}
	return count;
}


std::array<std::array<int,grid_size>,grid_size> get_next(std::array<std::array<int,grid_size>,grid_size>& grid){
	std::array<std::array<int,grid_size>,grid_size> next{};
	for(int i=0; i<grid_size; i++){
		for(int j=0; j<grid_size; j++){
			int cache  = count_neighbors(grid,i,j);
			if(grid[i][j]){
				if(cache < 2 || cache > 3){
					next[i][j] = 0;
				}
				else{
					next[i][j] = 1;
				}
			}
			else{
				if(cache==3){
					next[i][j] = 1;
				}
			}
		}
	}
	return next;
}

void draw_grid(std::array<std::array<int,grid_size>,grid_size>& grid,SDL_Renderer* renderer){
	SDL_Rect rect = {0,0,40,40};

	for(int i=0; i<grid_size; i++)
		for(int j=0; j<grid_size; j++){
			rect.x = j*window_width/grid_size;
			rect.y = i*window_height/grid_size;
			rect.w = 40;
			rect.h = 40;
			if(grid[i][j]){
				SDL_SetRenderDrawColor(renderer,255,255,255,255);
				SDL_RenderFillRect(renderer,&rect);
			}
			else{
				SDL_SetRenderDrawColor(renderer,0,0,0,0);
				SDL_RenderFillRect(renderer,&rect);
			}
			SDL_SetRenderDrawColor(renderer,0x3c,0x3f,0x40,0xff);
			SDL_RenderDrawRect(renderer,&rect);
		}
}

void mark_living(std::array<std::array<int,grid_size>,grid_size>& grid,int x_pos, int y_pos){
	if(window_width - x_pos < window_width && window_height - y_pos < window_height){
		int y_ind = ceil(x_pos/(window_width/grid_size));
		int x_ind = ceil(y_pos/(window_height/grid_size));
		grid[x_ind][y_ind] = !grid[x_ind][y_ind];
	}
}


int main()
{
	if(SDL_Init(SDL_INIT_EVERYTHING)){

	}
	static_assert(window_width/window_height == 1,"error: window must be at a 1:1 scale");
	SDL_Window* window = SDL_CreateWindow("Conway's Game of Life",-1,-1,window_width,window_height,0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_VIDEO_OPENGL);

	std::array<std::array<int,grid_size>,grid_size> grid{};

	grid[2][3] = 1;
	grid[4][3] = 1;
	grid[4][4] = 1;
	grid[3][4] = 1;
	grid[3][5] = 1;
	SDL_Event e;
	while (true)
		while(SDL_PollEvent(&e)){
			switch(e.type){
			case SDL_QUIT:
				exit(0);

			case SDL_KEYDOWN:
				switch(e.key.keysym.sym){
				case SDLK_SPACE:
					grid = get_next(grid);
					sim_time++;
					break;
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				mark_living(grid,e.button.x,e.button.y);
				break;
			}


			draw_grid(grid,renderer);
			SDL_RenderPresent(renderer);
		}
	return 0;
}
