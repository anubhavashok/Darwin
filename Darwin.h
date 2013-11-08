#include <vector>
#include <stdio.h>
#include <string.h>
#include <cassert>
#include <cstdlib>
#include <stddef.h>

using namespace std;

enum{WEST, NORTH, EAST,SOUTH };
enum{HOP, LEFT, RIGHT, INFECT, IF_EMPTY, IF_WALL, IF_RANDOM, IF_ENEMY, GO};
enum{ACTION, CONTROL};

/**
 * @class Instruction
 * Contains and executes instructions
 */
class Instruction
{
	private:
	int name;

	public:
	int go_to;
	int type;
	bool (*exec_instr) (int&, int&, int);
	void display_name();

	// --------
	// Instruction
	// --------
	/**
	 * Constructs an Instruction object for ACTION instructions
	 * @param instr an int representing an instruction
	 */
	Instruction(int instr);
	// --------
	// Instruction
	// --------
	/**
	 * Constructs an Instruction object for CONTROL instructions
	 * @param instr an int representing an instruction
	 * @param n an int representing the instruction's go_to value
	 */
	Instruction(int instr, int n);
};

/**
 * @class Species
 * Contains Species data and instructions
 */
class Species
{
	private:
	vector<Instruction> instructions_list;
	bool action_done;

	public:
	const char* type;

	// --------
	// Species
	// --------
	/**
	 * Constructs an Species object
	 * @param _type a char* containing the Species name
	 */
	Species(const char* _type);

	// --------
	// exec_instructions
	// --------
	/**
	 * Executes instructions added to the Species object
	 * @param x an int& representing the x-coordinate of the creature
	 * @param y an int& representing the y-coordinate of the creature
	 * @param dir an int representing the direction of the creature
	 * @param pc an int& representing the program counter of the creature
	 */
	void exec_instructions(int& x, int& y, int dir, int& pc);

	// --------
	// add_instruction
	// --------
	/**
	 * Adds an ACTION instruction to the Species object
	 * @param instr an int representing an instruction
	 */
	void add_instruction(int instr);

	// --------
	// add_instruction
	// --------
	/**
	 * Adds a CONTROL instruction to the Species object
	 * @param instr an int representing an instruction
	 * @param n an int representing the go_to value of the instruction
	 */
	void add_instruction(int instr, int n);

	// --------
	// display
	// --------
	/**
	 * Displays the first character of the Species name
	 */
	void display();
};

/**
 * @class Creature 
 * Contains Creature data
 */
class Creature
{
	private:
	int dir;
	int x;
	int y;
	int pc;
	bool done;

	public:
	Species* s;
	Creature& operator = (const Creature &c){return *this;}

	// --------
	// Creature
	// --------
	/**
	 * Constructs a creature object
	 * @param _s a Species& representing the Species of the creature
	 * @param _dir an int representing the direction the creature is facing
	 * @param _x an int representing the x-coordinate of the creature
	 * @param _y an int representing the y-coordinate of the creature
	 */
	Creature(Species& _s, int _dir, int _x, int _y);

	// --------
	// run
	// --------
	/**
	 * Runs instructions on the creature
	 */
	void run();

	// --------
	// turn_left
	// --------
	/**
	 * Changes the creature's direction to the direction it would face if it turned left
	 */
	void turn_left();

	// --------
	// turn_right
	// --------
	/**
	 * Changes the creature's direction to the direction it would face if it turned right
	 */
	void turn_right();

	// --------
	// display
	// --------
	/**
	 * Displays first character of its Species
	 */
	void display();

	// --------
	// is_enemy
	// --------
	/**
	 * Checks if the given creature is of a different Species
	 * @param c a Creature& representing another creature
	 * @return a bool contaning true if it is an enemy and false otherwise
	 */
	bool is_enemy(Creature& c);

	// --------
	// reset_done
	// --------
	/**
	 * Resets the done bool of the creature to false
	 */
	void reset_done();

	// --------
	// reset_pc
	// --------
	/**
	 * Resets the program counter of the creature to 0
	 */
	void reset_pc();

	// --------
	// is_done
	// --------
	/**
	 * Checks if the creature has performed an action in the current round
	 * @return a bool containing true if it has performed an action in the current round
	 */
	bool is_done();
};

/**
 * @class Darwin
 * Contains grid and creatures
 */
class Darwin
{
	private:
	static vector<Creature> creatures;
	static int xlen;
	static int ylen;
	static vector<vector <int> > grid;

	public:

	// --------
	// Darwin
	// --------
	/**
	 * Constructs a grid and initializes static variables
	 * @param x an int representing the x dimension of the grid
	 * @param y an int representing the y dimension of the grid
	 */
	Darwin(int x, int y);

	// --------
	// ~Darwin
	// --------
	/**
	 * Destroys the grid and creatures vector
	 */
	~Darwin();

	// --------
	// simulate
	// --------
	/**
	 * Simulates a round on the grid
	 */
	void simulate();

	// --------
	// add_creature
	// --------
	/**
	 * Adds a creature facing (direction) to the grid in position (x,y)
	 * @param species a Species& representing the Species of the creature
	 * @param direction an int representing the direction the creature is facing
	 * @param y an int representing the y-coordinate of the creature
	 * @param x an int representing the x-coordinate of the creature
	 * @return a bool if it was successful
	 */
	bool add_creature(Species& species, int direction, int y, int x);

	// --------
	// display
	// --------
	/**
	 * Displays the current state of the grid
	 */
	void display();

	// --------
	// hop_exec
	// --------
	/**
	 * If the space ahead is empty, move forward, otherwise, do nothing.
	 * @param x an int& representing the x-coordinate of the creature
	 * @param y an int& representing the y-coordinate of the creature
	 * @param dir an int representing the direction the creature is facing
	 * @return a bool containing true if successful
	 */
	static bool hop_exec(int& x,int& y,int dir);

	// --------
	// left_exec
	// --------
	/**
	 * Turn to face left.
	 * @param x an int& representing the x-coordinate of the creature
	 * @param y an int& representing the y-coordinate of the creature
	 * @param dir an int representing the direction the creature is facing
	 * @return a bool containing true if successful
	 */
	static bool left_exec(int& x,int& y,int dir);

	// --------
	// right_exec
	// --------
	/**
	 * Turn to face right.
	 * @param x an int& representing the x-coordinate of the creature
	 * @param y an int& representing the y-coordinate of the creature
	 * @param dir an int representing the direction the creature is facing
	 * @return a bool containing true if successful
	 */
	static bool right_exec(int& x,int& y,int dir);

	// --------
	// infect_exec
	// --------
	/**
	 * If the space ahead contains a creature of a different species, 
	 * change that creature to be of your species, reset the program counter, 
	 * but leave the direction unchanged, otherwise, do nothing.
	 * @param x an int& representing the x-coordinate of the creature
	 * @param y an int& representing the y-coordinate of the creature
	 * @param dir an int representing the direction the creature is facing
	 * @return a bool containing true if successful
	 */
	static bool infect_exec(int& x,int& y,int dir);

	// --------
	// is_enemy_exec
	// --------
	/**
	 * If the space ahead is empty, go to line n, otherwise, go to the next line.
	 * @param x an int& representing the x-coordinate of the creature
	 * @param y an int& representing the y-coordinate of the creature
	 * @param dir an int representing the direction the creature is facing
	 * @return a bool containing true if space ahead is an enemy
	 */
	static bool is_enemy_exec(int& x,int& y,int dir);

	// --------
	// is_wall_exec
	// --------
	/**
	 * If the space ahead is a wall, go to line n, otherwise, go to the next line.
	 * @param x an int& representing the x-coordinate of the creature
	 * @param y an int& representing the y-coordinate of the creature
	 * @param dir an int representing the direction the creature is facing
	 * @return a bool containing true if space ahead is a wall
	 */
	static bool is_wall_exec(int& x,int& y,int dir);

	// --------
	// is_random_exec
	// --------
	/**
	 * Randomly choose between going to line n or the next line.
	 * @param x an int& representing the x-coordinate of the creature
	 * @param y an int& representing the y-coordinate of the creature
	 * @param dir an int representing the direction the creature is facing
	 * @return a bool containing true if successful 
	 */
	static bool is_random_exec(int& x,int& y,int dir);

	// --------
	// is_empty_exec
	// --------
	/**
	 * If the space ahead contains a creature of a different species, go to line n, otherwise, go to the next line.
	 * @param x an int& representing the x-coordinate of the creature
	 * @param y an int& representing the y-coordinate of the creature
	 * @param dir an int representing the direction the creature is facing
	 * @return a bool containing true if space ahead is empty
	 */
	static bool is_empty_exec(int& x,int& y,int dir);

	// --------
	// go_exec
	// --------
	/**
	 * Go to line n.
	 * @param x an int& representing the x-coordinate of the creature
	 * @param y an int& representing the y-coordinate of the creature
	 * @param dir an int representing the direction the creature is facing
	 * @return a bool containing true
	 */
	static bool go_exec(int& x,int& y,int dir);
	
	//Test getters
	static int get_x(){return xlen;}
	static int get_y(){return ylen;}
	static int get_grid_x(){return grid.size();}
	static int get_grid_y(){return grid[0].size();}
	static int get_creatures_size(){return creatures.size();}
	static Creature& get_creature(int i){return creatures[i];}
	
};


