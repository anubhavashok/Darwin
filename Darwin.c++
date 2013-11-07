#include <vector>
#include <stdio.h>
#include <string.h>
#include <cassert>
#include <stddef.h>
#include "Darwin.h"

vector<vector <int> > Darwin::grid;
vector<Creature> Darwin::creatures;
int Darwin::xlen;
int Darwin::ylen;

//Darwin instructions
bool Darwin::hop_exec(int& x,int& y,int dir)
{
	assert(grid[x][y]!=-1);
	if(is_empty_exec(x,y,dir))
	{

		switch(dir)
		{
			case EAST:	
					grid[x+1][y] = grid[x][y];
					grid[x][y]=-1;
					++x;
					break;
			case WEST:	
					grid[x-1][y] = grid[x][y];
					grid[x][y]=-1;
					--x;
					break;
			case SOUTH:	
					grid[x][y+1] = grid[x][y];
					grid[x][y]=-1;
					++y;
					break;
			case NORTH:	
					grid[x][y-1] = grid[x][y];
					grid[x][y]=-1;
					--y;
					break;
			default: printf("Error in hop\n");
		}
		
	}
	return true;
}
bool Darwin::left_exec(int& x,int& y,int dir)
{
	assert(grid[x][y]!=-1);
	Creature& c = creatures[grid[x][y]];
	c.turn_left();
	return true;
}
bool Darwin::right_exec(int& x,int& y,int dir)
{
	assert(grid[x][y]!=-1);
	Creature& c = creatures[grid[x][y]];
	c.turn_right();
	return true;
}
bool Darwin::infect_exec(int& x,int& y,int dir)
{
	if(is_enemy_exec(x,y,dir))
	{
		Creature& infector = creatures[grid[x][y]];
		int new_x, new_y;
		switch(dir)
		{
			case EAST:	
					new_x=x+1;
					break;
			case WEST:						
					new_x=x-1;
					break;
			case SOUTH:	
					new_y=y+1;
					break;
			case NORTH:	
					new_y=y-1;
					break;
			default:
						printf("Error in is_infect\n");
		}
		Creature& infected = creatures[grid[new_x][new_y]];
		infected.s=infector.s;
		infected.reset_pc();
	}
	return true;
}
bool Darwin::is_enemy_exec(int& x,int& y,int dir)
{

	int new_x=x;
	int new_y=y;
	if(is_wall_exec(x,y,dir)) return false;

	if(!is_empty_exec(x,y,dir))
	{
		
		if(grid[x][y]!=-1)
		{
			switch(dir)
			{
				case EAST:	
						new_x=x+1;
						break;
				case WEST:						
						new_x=x-1;
						break;
				case SOUTH:	
						new_y=y+1;
						break;
				case NORTH:	
						new_y=y-1;
						break;
				default:
							printf("Error in is_enemy_exec\n");
			}
		return(creatures[ grid[x][y] ].is_enemy( creatures[ grid[new_x][new_y] ] ));
		}
	}
	return false;
}
bool Darwin::is_wall_exec(int& x,int& y,int dir)
{
	assert(grid[x][y]!=-1);
		switch(dir)
		{
			case EAST:	
					return(x==xlen-1);
			case WEST:						
					return(x==0);
			case SOUTH:	
					return(y==ylen-1);
			case NORTH:	
					return(y==0);
			default:
						printf("Error in is_wall\n");
		}
	return false;
}
bool Darwin::is_random_exec(int& x,int& y,int dir)
{
	return((bool)(rand()%2==0));
	//UNREACHABLE
	assert(false);
	return true;
}
bool Darwin::is_empty_exec(int& x,int& y,int dir)
{
	assert(grid[x][y]!=-1);
	if(!is_wall_exec(x,y,dir))
	{
		switch(dir)
		{
			case EAST:
						return(grid[x+1][y]==-1);
			case WEST:
						return(grid[x-1][y]==-1);
			case SOUTH:
						return(grid[x][y+1]==-1);
			case NORTH:
						return(grid[x][y-1]==-1);
			default:
						printf("Error in is_empty\n");
		}
	}
	return false;
}
bool Darwin::go_exec(int& x,int& y,int dir){return true;}

//Instruction methods
	
	Instruction::Instruction(int instr)
	{
			switch(instr)
			{
				case HOP:
					name = instr;
					type = ACTION;
					go_to=0;
					exec_instr = Darwin::hop_exec;
					break;
				case LEFT:
					name = instr;
					type = ACTION;
					go_to=0;
					exec_instr = Darwin::left_exec;
					break;
				case RIGHT:
					name = instr;
					type = ACTION;
					go_to=0;
					exec_instr = Darwin::right_exec;
					break;
				case INFECT:
					name = instr;
					type = ACTION;
					go_to=0;
					exec_instr = Darwin::infect_exec;
					break;
				default: printf("Error in Instruction(int) constructor\n");
			}
	}

	Instruction::Instruction(int instr, int n)
	{
			switch(instr)
			{
				case IF_EMPTY:
					name = instr;
					go_to=n;
					type = CONTROL;
					exec_instr = Darwin::is_empty_exec;
					break;
				case IF_WALL:
					name = instr;
					go_to=n;
					type = CONTROL;
					exec_instr = Darwin::is_wall_exec;
					break;
				case IF_RANDOM:
					name = instr;
					go_to=n;
					type = CONTROL;
					exec_instr = Darwin::is_random_exec;
					break;
				case IF_ENEMY:
					name = instr;
					go_to=n;
					type = CONTROL;
					exec_instr = Darwin::is_enemy_exec;
					break;
				case GO:
					name = instr;
					go_to=n;
					type = CONTROL;
					exec_instr = Darwin::go_exec;
					break;
				default: printf("Error in Instruction(int,int) constructor\n");
			}	
	}
	void Instruction::display_name()
	{
		switch(name)
		{
			case HOP: printf("HOP\n"); break; 
			case LEFT: printf("LEFT\n"); break; 
			case RIGHT: printf("RIGHT\n"); break; 
			case INFECT: printf("INFECT\n"); break; 
			case IF_EMPTY: printf("IF_EMPTY\n"); break; 
			case IF_WALL: printf("IF_WALL\n"); break; 
			case IF_RANDOM: printf("IF_RANDOM\n"); break; 
			case IF_ENEMY: printf("IF_ENEMY\n"); break; 
			case GO: printf("GO\n"); break; 
		}
	}

//Species methods
	Species::Species(const char* _type)
	{
		assert(_type!=NULL);
		type = _type;
		action_done = false;
	}	

	void Species::exec_instructions(int& x, int& y, int dir, int& pc)
	{
		assert(action_done==false);
		while(pc<(int) instructions_list.size())
		{
			Instruction& instr = instructions_list[pc];		
			if(instr.type==ACTION)
			{
				if(!action_done)
				{
					instr.exec_instr(x,y, dir);
					//instr.display_name();
					action_done = true;
				}
				else
				{
					++pc;
					action_done =false;
					return;
				}
			}
			else
			{
				//instr.display_name();
				//printf("x,y: %d,%d \n",x,y);
				if(instr.exec_instr(x,y, dir))
				{
					pc=instr.go_to;		
				}
				else
				{
					++pc;
				}
			}
			
		}
		action_done =false;
	}
	
	void Species::add_instruction(int instr)
	{
		Instruction i(instr);
		instructions_list.push_back(i);
	}
	void Species::add_instruction(int instr, int n)
	{
		Instruction i(instr, n);
		instructions_list.push_back(i);
	}
	void Species::display()
	{
		printf("%c",type[0]);
	}

//Creature methods

	Creature::Creature(Species& _s, int _dir, int _x, int _y): 
	s(&_s),dir(_dir), x(_x), y(_y)
	{
		done = false;
		pc = 0;
	}
	void Creature::run()
	{
		(*s).exec_instructions(x, y, dir, pc);
		done = true;
		//printf("\n");
		return;
	}
	
	void Creature::turn_left()
	{
		switch(dir)
		{
			case NORTH: dir = WEST; break;
			case SOUTH: dir = EAST; break;
			case EAST: dir = NORTH; break;
			case WEST: dir = SOUTH; break;
			default: printf("Error in turn_left\n");
		}
	}
	
	void Creature::turn_right()
	{
		switch(dir)
		{
			case NORTH: dir = EAST; break;
			case SOUTH: dir = WEST; break;
			case EAST: dir = SOUTH; break;
			case WEST: dir = NORTH; break;
			default: printf("Error in turn_right\n");
		}
	}
	
	void Creature::display()
	{
		(*s).display();
		return;
	}

	bool Creature::is_enemy(Creature& c)
	{
		//same species
		return(s!=c.s);
	}
	
	void Creature::reset_done()
	{
		done=false;
	}

	bool Creature::is_done()
	{
		return done;
	}
	
	void Creature::reset_pc()
	{
		pc=0;
	}

//Darwin methods

	Darwin::Darwin(int y, int x)
	{
		xlen=x;
		ylen=y;
		//initialize grid as -1
		grid.resize( x , vector<int>( y , -1 ) );
		assert((int) grid.size()==xlen);
		assert((int) grid[0].size()==ylen);
	}

	Darwin::~Darwin()
	{
		for(int i=0;i<(int) grid.size();i++)
		{
			grid[i].clear();
		}
		grid.clear();
		creatures.clear();
	}
	//Darwin::simulate
	void Darwin::simulate()
	{
		for(int j=0; j<ylen;j++)
		{
			for(int i =0; i<xlen;i++)
			{
				
				if((grid[i][j]!=-1))
				{	
					//has creature on grid
					//printf("creature address: %p\n",grid[i][j]);
					Creature& c = creatures[grid[i][j]];
					if(!c.is_done())
						c.run();
					
				}
			}
		}
		for(int i=0; i<(int) creatures.size(); i++)
		{
			creatures[i].reset_done();
		}
	}

	//Darwin::add_creature
	bool Darwin::add_creature(Species& species, int direction, int y, int x)
	{
		if(grid[x][y]==-1)
		{
			{
			Creature c(species,direction,x,y);
			creatures.push_back(c);
			grid[x][y]=creatures.size()-1;
			//printf("creature added to grid[%d][%d]: %d\n", x, y, grid[x][y]);
			}
			return true;
		}
			return false;
	}
	void Darwin::display()
	{
		printf("  ");
		for(int i =0; i<xlen;i++)
		{
			printf("%d", i%10);
		}
		printf("\n");

		for(int j=0; j<ylen; j++)
		{
			printf("%d ", j%10);
			for(int i=0; i<xlen; i++)
			{
				if(grid[i][j]==-1)
				{
					printf(".");
				}				
				else
				{
					Creature& c = creatures[grid[i][j]];
					c.display();
				}
			}
			printf("\n");
		}
		printf("\n");
	}
