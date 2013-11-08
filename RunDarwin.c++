// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2013
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall Darwin.c++ RunDarwin.c++ -o RunDarwin
    % valgrind RunDarwin > RunDarwin.out

To configure Doxygen:
    doxygen -g
That creates the file Doxyfile.
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    doxygen Doxyfile
*/

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h"
// ----
// main
// ----

int main () {
    using namespace std;

    // ----
    // food
    // ----
	Species food("food");
    /*
     0: left
     1: go 0
    */
	food.add_instruction(LEFT);
	food.add_instruction(GO,0);
    // ------
    // hopper
    // ------
	Species hopper("hopper");
    /*
     0: hop
     1: go 0
    */
	hopper.add_instruction(HOP);
	hopper.add_instruction(GO,0);
    // -----
    // rover
    // -----
	Species rover("rover");
    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */
	rover.add_instruction(IF_ENEMY,9);
	rover.add_instruction(IF_EMPTY,7);
	rover.add_instruction(IF_RANDOM,5);
	rover.add_instruction(LEFT);
	rover.add_instruction(GO,0);
	rover.add_instruction(RIGHT);
	rover.add_instruction(GO,0);
	rover.add_instruction(HOP);
	rover.add_instruction(GO,0);
	rover.add_instruction(INFECT);
	rover.add_instruction(GO,0);
    // ----
    // trap
    // ----
	Species trap("trap");
    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */
	trap.add_instruction(IF_ENEMY,3);
	trap.add_instruction(LEFT);
	trap.add_instruction(GO,0);
	trap.add_instruction(INFECT);
	trap.add_instruction(GO,0);

    // ----
    // best
    // ----
	Species best("best");
    /*
	 0: if_enemy 6
	 1: if_empty 4
	 2: left
	 3: go 0
	 4: hop
	 5: go 0
	 6: infect
	 7: go 0
    */
	best.add_instruction(IF_ENEMY,6);
	best.add_instruction(IF_EMPTY,4);
	best.add_instruction(LEFT);
	best.add_instruction(GO,0);
	best.add_instruction(HOP);
	best.add_instruction(GO,0);
	best.add_instruction(INFECT);
	best.add_instruction(GO,0);
    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;

		Darwin d(8,8);
		
		d.add_creature(food,EAST,0,0);
		d.add_creature(hopper,NORTH,3,3);
		d.add_creature(hopper,EAST,3,4);
		d.add_creature(hopper,SOUTH,4,4);
		d.add_creature(hopper,WEST,4,3);
		d.add_creature(food,NORTH,7,7);

		for(int i=0; i<=5; i++)
		{
			cout<< "Turn = " << i << "."<<endl;
			d.display();
			d.simulate();
		}
        /*
        8x8 Darwin
        Food,   facing east,  at (0, 0)
        Hopper, facing north, at (3, 3)
        Hopper, facing east,  at (3, 4)
        Hopper, facing south, at (4, 4)
        Hopper, facing west,  at (4, 3)
        Food,   facing north, at (7, 7)
        Simulate 5 moves.
        Print every grid.
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 7x9
    // ----------

    try {
        cout << "*** Darwin 7x9 ***" << endl;
        srand(0);
		
		Darwin d(7,9);

		d.add_creature(trap,SOUTH,0,0);
		d.add_creature(hopper,EAST,3,2);
		d.add_creature(rover,NORTH,5,4);
		d.add_creature(trap,WEST,6,8);
		for(int i=0; i<=5; i++)
		{
			cout<< "Turn = " << i << "."<<endl;
			d.display();
			d.simulate();
		}
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // without best
    // ------------

    try {
        cout << "*** Darwin 72x72 without Best ***" << endl;
        srand(0);

		Darwin d(72,72);

		for(int i=0; i<10; i++)
		{
			int pos =rand() % 5184;
			int x = pos%72;
			int y = pos/72;
			int dir =rand()%4;
			d.add_creature(food,dir,x,y);
		}

		for(int i=0; i<10; i++)
		{
			int pos =rand() % 5184;
			int x = pos%72;
			int y = pos/72;
			int dir =rand()%4;
			d.add_creature(hopper,dir,x,y);
		}

		for(int i=0; i<10; i++)
		{
			int pos =rand() % 5184;
			int x = pos%72;
			int y = pos/72;
			int dir =rand()%4;
			d.add_creature(rover,dir,x,y);
		}

		for(int i=0; i<10; i++)
		{
			int pos =rand() % 5184;
			int x = pos%72;
			int y = pos/72;
			int dir =rand()%4;
			d.add_creature(trap,dir,x,y);
		}

		for(int i=0; i<=1000; i++)
		{
			if(i<=10)
			{
			cout<< "Turn = " << i << "."<<endl;
				d.display();
			}
			else if(i%100 == 0)
			{
			cout<< "Turn = " << i << "."<<endl;
				d.display();
			}
			d.simulate();
			
		}
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        Simulate 1000 moves.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // with best
    // ------------

    try {
        cout << "*** Darwin 72x72 with Best ***" << endl;
        srand(0);

		Darwin d(72,72);

		for(int i=0; i<10; i++)
		{
			int pos =rand() % 5184;
			int x = pos%72;
			int y = pos/72;
			int dir =rand()%4;
			d.add_creature(food,dir,x,y);
		}

		for(int i=0; i<10; i++)
		{
			int pos =rand() % 5184;
			int x = pos%72;
			int y = pos/72;
			int dir =rand()%4;
			d.add_creature(hopper,dir,x,y);
		}

		for(int i=0; i<10; i++)
		{
			int pos =rand() % 5184;
			int x = pos%72;
			int y = pos/72;
			int dir =rand()%4;
			d.add_creature(rover,dir,x,y);
		}

		for(int i=0; i<10; i++)
		{
			int pos =rand() % 5184;
			int x = pos%72;
			int y = pos/72;
			int dir =rand()%4;
			d.add_creature(trap,dir,x,y);
		}
		for(int i=0; i<10; i++)
		{
			int pos =rand() % 5184;
			int x = pos%72;
			int y = pos/72;
			int dir =rand()%4;
			d.add_creature(best,dir,x,y);
		}
		for(int i=0; i<=1000; i++)
		{
			if(i<=10)
			{
			cout<< "Turn = " << i << "."<<endl;
				d.display();
			}
			else if(i%100 == 0)
			{
			cout<< "Turn = " << i << "."<<endl;
				d.display();
			}
			d.simulate();
			
		}
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        10 Best
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------------
    // Additional tests
    // ----------------
	//1. osaprych
	//2. davismc
	//3. bsy6766
	//4. ss48333
	//5. nlaz

    try {
        cout << "*** Darwin 30x50 without Best ***" << endl;
        srand(0);
        Darwin d(30, 50);
		for(int i=0; i<100; i++)
		{
			int pos =rand() % 1500;
			int x = pos%30;
			int y = pos/50;
			int dir =rand()%4;
			d.add_creature(food,dir,x,y);
		}

		for(int i=0; i<10; i++)
		{
			int pos =rand() % 1500;
			int x = pos%30;
			int y = pos/50;
			int dir =rand()%4;
			d.add_creature(hopper,dir,x,y);
		}

		for(int i=0; i<10; i++)
		{
			int pos =rand() % 1500;
			int x = pos%30;
			int y = pos/50;
			int dir =rand()%4;
			d.add_creature(rover,dir,x,y);
		}

		for(int i=0; i<10; i++)
		{
			int pos =rand() % 1500;
			int x = pos%30;
			int y = pos/50;
			int dir =rand()%4;
			d.add_creature(trap,dir,x,y);
		}

        int s = 0;
        for (; s <= 20; s++){
            d.display();
            d.simulate();
        }
        for (; s <= 2000; s++){
            d.simulate();
        }
        d.display();

    } catch (const invalid_argument&) {
        assert(false);
    } catch (const out_of_range&) {
        assert(false);
    }


    try {
        cout << "*** Darwin 2x2 without Best ***" << endl;
        srand(0);
       	Darwin d(2, 2);

			{
			int pos =rand() % 4;
			int x = pos%2;
			int y = pos/2;
			int dir =rand()%4;
			d.add_creature(hopper,dir,x,y);
			}
			int pos =rand() % 4;
			int x = pos%2;
			int y = pos/2;
			int dir =rand()%4;
			d.add_creature(rover,dir,x,y);

        int s = 0;
        for (; s <= 7; s++){
            d.display();
            d.simulate();
        }
    } catch (const invalid_argument&) {
        assert(false);
    } catch (const out_of_range&) {
        assert(false);
    }

    try {
        cout << "*** Fod Walk Meet In Middle 4x4 ***" << endl;
        Darwin d(4, 6);
        d.add_creature(hopper, EAST, 0, 0);
        d.add_creature(hopper, EAST, 1, 0);
        d.add_creature(hopper, EAST, 2, 0);
        d.add_creature(hopper, EAST, 3, 0);
        d.add_creature(hopper, WEST, 0, 5);
        d.add_creature(hopper, WEST, 1, 5);
        d.add_creature(hopper, WEST, 2, 5);
        d.add_creature(hopper, WEST, 3, 5);
        const int NUM_MOVES = 4;
        d.display();
        std::cout << std::endl;
        for (int i = 0; i < NUM_MOVES; ++i) {
            d.simulate();
            d.display();
            std::cout << endl;
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);} 


    try{
        cout << "*** Darwin 50x50 with hoppers ***" << endl;
        srand(0);
        
        Darwin map(50, 50);

        for(int i = 0; i<50; i++){
            int randPos = rand() % 2500;
            map.add_creature(hopper,rand()%4, randPos%50, randPos/50);
        }
        map.display();

        for(int i = 1; i<=100; i++){
            map.simulate();
            if(i < 10)
                map.display();
            else{
                if(i % 100 == 0)
                    map.display();
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    try {
        cout << "*** Darwin 4x4 Trap ***" << endl;
        /*
        8x8 Darwin
        Simulate 10 moves.
        Print the final grid. Every hopper should of been trapped. 
        */
        srand(0);
        Darwin game(4, 4);
        game.add_creature(trap, NORTH, 3,0);
        game.add_creature(trap, NORTH, 3,1);
        game.add_creature(trap, NORTH, 3,2);
        game.add_creature(trap, NORTH, 3,3);

        game.add_creature(hopper, SOUTH, 0,0);
        game.add_creature(hopper, SOUTH, 0,1);
        game.add_creature(hopper, SOUTH, 0,2);
        game.add_creature(hopper, SOUTH, 0,3);
        
        game.display();
        for(uint32_t i = 0; i < 10; ++i){
            game.simulate();
        }
        game.display(); 
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    try {
        cout << "*** Darwin 5x5 ***" << endl;
        srand(0);

        Darwin grid(5,5);
        grid.add_creature(trap, WEST, 0, 0);
        grid.add_creature(hopper, NORTH, 0, 1);
        grid.add_creature(hopper, EAST, 0, 2);
        grid.add_creature(hopper, SOUTH, 0, 3);
        grid.display();
        for (int i = 0; i < 5; i++){
            grid.simulate();
            grid.display();
        }
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}

