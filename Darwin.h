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
class Instruction
{
	private:
	int name;

	public:
	int go_to;
	int type;
	bool (*exec_instr) (int&, int&, int);
	void display_name();
	Instruction(int instr);
	Instruction(int instr, int n);
};

class Species
{
	private:
	vector<Instruction> instructions_list;
	bool action_done;

	public:
	const char* type;
	Species(const char* _type);
	void exec_instructions(int& x, int& y, int dir, int& pc);
	void add_instruction(int instr);
	void add_instruction(int instr, int n);
	void display();
};

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
	Creature(Species& _s, int _dir, int _x, int _y);
	void run();
	void turn_left();
	void turn_right();
	void display();
	bool is_enemy(Creature& c);
	void reset_done();
	void reset_pc();
	bool is_done();
};

class Darwin
{
	private:
	static vector<Creature> creatures;
	static int xlen;
	static int ylen;
	static vector<vector <int> > grid;

	public:
	Darwin(int x, int y);
	~Darwin();
	void simulate();
	bool add_creature(Species& species, int direction, int y, int x);
	void display();
	static bool hop_exec(int& x,int& y,int dir);
	static bool left_exec(int& x,int& y,int dir);
	static bool right_exec(int& x,int& y,int dir);
	static bool infect_exec(int& x,int& y,int dir);
	static bool is_enemy_exec(int& x,int& y,int dir);
	static bool is_wall_exec(int& x,int& y,int dir);
	static bool is_random_exec(int& x,int& y,int dir);
	static bool is_empty_exec(int& x,int& y,int dir);
	static bool go_exec(int& x,int& y,int dir);
};


