// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <stdexcept>

#include "gtest/gtest.h"

#include "Darwin.h"

//g++ -pedantic -std=c++0x -Wall TestDarwin.c++ Darwin.c++ -o TestDarwin -lgtest -lpthread -lgtest_main
// -----------
// TestDarwin
// -----------

// -----------
// Instruction
// -----------
TEST(Darwin, InstructionConstructorActionType1){
	Instruction i1(HOP);
	ASSERT_TRUE(i1.type==ACTION);
}
TEST(Darwin, InstructionConstructorActionType2){
	Instruction i1(LEFT);
	ASSERT_TRUE(i1.type==ACTION);
}
TEST(Darwin, InstructionConstructorActionType3){
	Instruction i1(RIGHT);
	ASSERT_TRUE(i1.type==ACTION);
}
TEST(Darwin, InstructionConstructorExec_Instr1){
	Instruction i1(RIGHT);
	ASSERT_TRUE(i1.exec_instr==Darwin::right_exec);
}
TEST(Darwin, InstructionConstructorExec_Instr2){
	Instruction i1(LEFT);
	ASSERT_TRUE(i1.exec_instr==Darwin::left_exec);
}
TEST(Darwin, InstructionConstructorExec_Instr3){
	Instruction i1(HOP);
	ASSERT_TRUE(i1.exec_instr==Darwin::hop_exec);
}

TEST(Darwin, InstructionConstructorControlType1){
	Instruction i1(IF_EMPTY,5);
	ASSERT_TRUE(i1.type==CONTROL);
}
TEST(Darwin, InstructionConstructorControlType2){
	Instruction i1(IF_WALL,5);
	ASSERT_TRUE(i1.type==CONTROL);
}
TEST(Darwin, InstructionConstructorControlType3){
	Instruction i1(IF_ENEMY,5);
	ASSERT_TRUE(i1.type==CONTROL);
}
TEST(Darwin, InstructionConstructorGO_TO1){
	Instruction i1(IF_WALL,5);
	ASSERT_TRUE(i1.go_to==5);
}
TEST(Darwin, InstructionConstructorGO_TO2){
	Instruction i1(IF_ENEMY,6);
	ASSERT_TRUE(i1.go_to==6);
}
TEST(Darwin, InstructionConstructorGO_TO3){
	Instruction i1(IF_ENEMY,0);
	ASSERT_TRUE(i1.go_to==0);
}
TEST(Darwin, InstructionConstructorExec_Instr4){
	Instruction i1(IF_ENEMY,6);
	ASSERT_TRUE(i1.exec_instr==Darwin::is_enemy_exec);
}
TEST(Darwin, InstructionConstructorExec_Instr5){
	Instruction i1(IF_WALL,6);
	ASSERT_TRUE(i1.exec_instr==Darwin::is_wall_exec);
}
TEST(Darwin, InstructionConstructorExec_Instr6){
	Instruction i1(IF_EMPTY,6);
	ASSERT_TRUE(i1.exec_instr==Darwin::is_empty_exec);
}
// -----------
// Species
// -----------
TEST(Darwin, SpeciesConstructor1){
	Species food("food");
	ASSERT_TRUE(strcmp(food.type,"food")==0);
}
TEST(Darwin, SpeciesConstructor2){
	Species food("water");
	ASSERT_TRUE(strcmp(food.type,"water")==0);
}
TEST(Darwin, SpeciesConstructor3){
	Species food("2water2");
	ASSERT_TRUE(strcmp(food.type,"2water2")==0);
}
TEST(Darwin, SpeciesConstructor4){
	Species food("");
	ASSERT_TRUE(strcmp(food.type,"")==0);
}

// -----------
// Creature
// -----------
TEST(Darwin, CreatureConstructorSpeciesCheck1){
	Species food("food");
	Creature A(food,NORTH,1,2);
	ASSERT_TRUE(A.s==&food);
}
TEST(Darwin, CreatureConstructorSpeciesCheck2){
	Species water("water");
	Creature A(water,NORTH,2,2);
	ASSERT_TRUE(A.s==&water);
}
TEST(Darwin, CreatureConstructorSpeciesCheck3){
	Species food("food11241");
	Creature A(food,NORTH,1,1);
	ASSERT_TRUE(A.s==&food);
}
TEST(Darwin, CreatureConstructorSpeciesCheck4){
	Species food("");
	Creature A(food,NORTH,1,1);
	ASSERT_TRUE(A.s==&food);
}

TEST(Darwin, CreatureIs_Done1){
	Species food("food");
	Creature A(food,NORTH,1,2);
	ASSERT_TRUE(!A.is_done());
}
TEST(Darwin, CreatureIs_Done2){
	Species water("water");
	Creature A(water,NORTH,2,2);
	ASSERT_TRUE(!A.is_done());
}
TEST(Darwin, CreatureIs_Done3){
	Species food("food11241");
	Creature A(food,NORTH,1,1);
	ASSERT_TRUE(!A.is_done());
}
TEST(Darwin, CreatureIs_Done4){
	Species food("");
	Creature A(food,NORTH,1,1);
	ASSERT_TRUE(!A.is_done());
}

TEST(Darwin, CreatureIs_enemy1){
	Species food("food");
	Creature A(food,NORTH,1,2);
	ASSERT_TRUE(!A.is_enemy(A));
}
TEST(Darwin, CreatureIs_enemy2){
	Species water("water");
	Species food("food");
	Creature A(water,NORTH,2,2);
	Creature B(food,NORTH,3,2);
	ASSERT_TRUE(A.is_enemy(B));
}
TEST(Darwin, CreatureIs_enemy3){
	Species food("food11241");
	Creature A(food,NORTH,1,1);
	Creature B(food,NORTH,1,2);
	ASSERT_TRUE(!A.is_enemy(B));
}
TEST(Darwin, CreatureIs_enemy4){
	Species food("");
	Creature A(food,NORTH,1,1);
	Creature B(food,NORTH,1,2);
	ASSERT_TRUE(!A.is_enemy(B));
}
TEST(Darwin, CreatureIs_enemy5){
	Species water("food");
	Species food("food");
	Creature A(water,NORTH,2,2);
	Creature B(food,NORTH,3,2);
	ASSERT_TRUE(A.is_enemy(B));
}
// -----------
// Darwin
// -----------
TEST(Darwin, DarwinConstructorCheckDimensions1){
	Darwin d(20,20);
	ASSERT_TRUE(d.get_x()==20);
	ASSERT_TRUE(d.get_y()==20);
}
TEST(Darwin, DarwinConstructorCheckDimensions2){
	Darwin d(10,20);
	ASSERT_TRUE(d.get_x()==20);
	ASSERT_TRUE(d.get_y()==10);
}

TEST(Darwin, DarwinConstructorCheckDimensions3){
	Darwin d(1,1);
	ASSERT_TRUE(d.get_x()==1);
	ASSERT_TRUE(d.get_y()==1);
}
TEST(Darwin, DarwinConstructorCheckDimensions4){
	Darwin d(1,2);
	ASSERT_TRUE(d.get_x()==2);
	ASSERT_TRUE(d.get_y()==1);
}
TEST(Darwin, DarwinConstructorCheckDimensions5){
	Darwin d(0,0);
	ASSERT_TRUE(d.get_x()==0);
	ASSERT_TRUE(d.get_y()==0);
}


TEST(Darwin, DarwinConstructorCheckGrid1){
	Darwin d(10,20);

	ASSERT_TRUE(d.get_grid_x()==20);
	ASSERT_TRUE(d.get_grid_y()==10);
}
TEST(Darwin, DarwinConstructorCheckGrid2){
	Darwin d(1,1);

	ASSERT_TRUE(d.get_grid_x()==1);
	ASSERT_TRUE(d.get_grid_y()==1);
}
TEST(Darwin, DarwinConstructorCheckGrid3){
	Darwin d(1,2);

	ASSERT_TRUE(d.get_grid_x()==2);
	ASSERT_TRUE(d.get_grid_y()==1);
}
TEST(Darwin, DarwinConstructorCheckGrid4){
	Darwin d(0,0);

	ASSERT_TRUE(d.get_grid_x()==0);
	ASSERT_TRUE(d.get_grid_y()==0);
}

TEST(Darwin, DarwinConstructorAdd_One_Creature1){
	Darwin d(10,20);
	Species food("food");
	
	d.add_creature(food,NORTH,1,2);
	ASSERT_TRUE(d.get_creatures_size()==1);
	ASSERT_TRUE(d.get_creature(0).s==&food);
}
TEST(Darwin, DarwinConstructorAdd_One_Creature2){
	Darwin d(10,20);
	Species fox("fox");
	
	d.add_creature(fox,NORTH,2,2);
	ASSERT_TRUE(d.get_creatures_size()==1);
	ASSERT_TRUE(d.get_creature(0).s==&fox);
}
TEST(Darwin, DarwinConstructorAdd_One_Creature3){
	Darwin d(10,20);
	Species water("food");
	
	d.add_creature(water,NORTH,1,2);
	ASSERT_TRUE(d.get_creatures_size()==1);
	ASSERT_TRUE(d.get_creature(0).s==&water);
}
TEST(Darwin, DarwinConstructorAdd_One_Creature4){
	Darwin d(1,20);
	Species water("food");
	
	d.add_creature(water,NORTH,0,2);
	ASSERT_TRUE(d.get_creatures_size()==1);
	ASSERT_TRUE(d.get_creature(0).s==&water);
}
TEST(Darwin, DarwinConstructorAdd_One_Creature5){
	Darwin d(1,1);
	Species water("food");
	
	d.add_creature(water,NORTH,0,0);
	ASSERT_TRUE(d.get_creatures_size()==1);
	ASSERT_TRUE(d.get_creature(0).s==&water);
}

TEST(Darwin, DarwinConstructorAdd_Two_Creatures1){
	Darwin d(10,20);
	Species fox("fox");
	
	d.add_creature(fox,NORTH,2,2);
	ASSERT_TRUE(d.get_creatures_size()==1);
	ASSERT_TRUE(d.get_creature(0).s==&fox);

	Species water("food");
	d.add_creature(water,NORTH,2,1);
	ASSERT_TRUE(d.get_creatures_size()==2);
}
TEST(Darwin, DarwinConstructorAdd_Two_Creatures2){
	Darwin d(10,20);
	Species fox("fox");
	
	d.add_creature(fox,NORTH,2,2);
	ASSERT_TRUE(d.get_creatures_size()==1);
	ASSERT_TRUE(d.get_creature(0).s==&fox);

	d.add_creature(fox,NORTH,2,1);
	ASSERT_TRUE(d.get_creatures_size()==2);
}
TEST(Darwin, DarwinConstructorAdd_Two_Creatures3){
	Darwin d(10,20);
	Species food("food");
	
	d.add_creature(food,NORTH,2,2);
	ASSERT_TRUE(d.get_creatures_size()==1);
	ASSERT_TRUE(d.get_creature(0).s==&food);

	d.add_creature(food,NORTH,2,1);
	ASSERT_TRUE(d.get_creatures_size()==2);
}
TEST(Darwin, DarwinConstructorAdd_Two_Creatures4){
	Darwin d(1,2);
	Species food("food");
	
	d.add_creature(food,NORTH,0,0);
	ASSERT_TRUE(d.get_creatures_size()==1);
	ASSERT_TRUE(d.get_creature(0).s==&food);

	d.add_creature(food,NORTH,0,1);
	ASSERT_TRUE(d.get_creatures_size()==2);
}
TEST(Darwin, DarwinConstructorAdd_Two_Creatures5){
	Darwin d(1,100);
	Species food("food");
	
	d.add_creature(food,NORTH,0,2);
	ASSERT_TRUE(d.get_creatures_size()==1);
	ASSERT_TRUE(d.get_creature(0).s==&food);

	d.add_creature(food,NORTH,0,1);
	ASSERT_TRUE(d.get_creatures_size()==2);
}
