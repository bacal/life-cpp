#pragma once
namespace life
{
	class cell
	{
	 private:
		int death_time;
		bool alive;
	 public:
		cell():death_time{0},alive{false} {}
		void kill(int time){death_time = time; alive=false;}
		bool is_dead() const {return alive;}
		int time_of_death() const {return death_time;}
		void animate(){alive = true;}
	};

}
