// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <stdexcept>

#include "gtest/gtest.h"

#include "Darwin.h"

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
	ASSERT_TRUE(i1.exec_instr==Darwin.right_exec);
}
TEST(Darwin, InstructionConstructorExec_Instr2){
	Instruction i1(LEFT);
	ASSERT_TRUE(i1.exec_instr==Darwin.left_exec);
}
TEST(Darwin, InstructionConstructorExec_Instr3){
	Instruction i1(HOP);
	ASSERT_TRUE(i1.exec_instr==Darwin.hop_exec);
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
	ASSERT_TRUE(i1.exec_instr==Darwin.is_enemy_exec);
}
TEST(Darwin, InstructionConstructorExec_Instr5){
	Instruction i1(IF_WALL,6);
	ASSERT_TRUE(i1.exec_instr==Darwin.is_wall_exec);
}
TEST(Darwin, InstructionConstructorExec_Instr6){
	Instruction i1(IF_EMPTY,6);
	ASSERT_TRUE(i1.exec_instr==Darwin.is_empty_exec);
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

// -----------
// Creature
// -----------
TEST(Darwin, CreatureConstructorSpeciesCheck1){
	Species food("food");
	Creature A(food,NORTH,1,2);
	ASSERT_TRUE(s==&food);
}
TEST(Darwin, CreatureConstructorSpeciesCheck2){
	Species water("water");
	Creature A(water,NORTH,2,2);
	ASSERT_TRUE(s==&water);
}
TEST(Darwin, CreatureConstructorSpeciesCheck3){
	Species food("food11241");
	Creature A(food,NORTH,1,1);
	ASSERT_TRUE(s==&food);
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
// -----------
// Darwin
// -----------
TEST(Darwin, DarwinConstructorCheckDimensions1){
	Darwin d(20,20);
	ASSERT_TRUE(Darwin.xlen==20);
	ASSERT_TRUE(Darwin.ylen==20);
}
TEST(Darwin, DarwinConstructorCheckDimensions2){
	Darwin d(10,20);
	ASSERT_TRUE(Darwin.xlen==20);
	ASSERT_TRUE(Darwin.ylen==10);
}

TEST(Darwin, DarwinConstructorCheckDimensions3){
	Darwin d(1,1);
	ASSERT_TRUE(Darwin.xlen==1);
	ASSERT_TRUE(Darwin.ylen==1);
}
TEST(Darwin, DarwinConstructorCheckDimensions4){
	Darwin d(1,2);
	ASSERT_TRUE(Darwin.xlen==2);
	ASSERT_TRUE(Darwin.ylen==1);
}


TEST(Darwin, DarwinConstructorCheckGrid1){
	Darwin d(10,20);
	ASSERT_TRUE(Darwin.grid!=NULL);
	ASSERT_TRUE(Darwin.grid.size()==20);
	ASSERT_TRUE(Darwin.grid[0].size()==10);
}
TEST(Darwin, DarwinConstructorCheckGrid2){
	Darwin d(1,1);
	ASSERT_TRUE(Darwin.grid!=NULL);
	ASSERT_TRUE(Darwin.grid.size()==1);
	ASSERT_TRUE(Darwin.grid[0].size()==1);
}
TEST(Darwin, DarwinConstructorCheckGrid3){
	Darwin d(1,2);
	ASSERT_TRUE(Darwin.grid!=NULL);
	ASSERT_TRUE(Darwin.grid.size()==2);
	ASSERT_TRUE(Darwin.grid[0].size()==1);
}

TEST(Darwin, DarwinConstructorAdd_One_Creature1){
	Darwin d(10,20);
	Species food("food");
	
	d.add_creature(food,NORTH,1,2);
	ASSERT_TRUE(Darwin.creatures.size()==1);
	ASSERT_TRUE(Darwin.creatures[Darwin.grid[2][1]]].s==food);
}
TEST(Darwin, DarwinConstructorAdd_One_Creature2){
	Darwin d(10,20);
	Species fox("fox");
	
	d.add_creature(fox,NORTH,2,2);
	ASSERT_TRUE(Darwin.creatures.size()==1);
	ASSERT_TRUE(Darwin.creatures[Darwin.grid[2][2]]].s==fox);
}
TEST(Darwin, DarwinConstructorAdd_One_Creature3){
	Darwin d(10,20);
	Species water("food");
	
	d.add_creature(water,NORTH,1,2);
	ASSERT_TRUE(Darwin.creatures.size()==1);
	ASSERT_TRUE(Darwin.creatures[Darwin.grid[2][1]]].s==water);
}

TEST(Darwin, DarwinConstructorAdd_Two_Creatures1){
	Darwin d(10,20);
	Species fox("fox");
	
	d.add_creature(fox,NORTH,2,2);
	ASSERT_TRUE(Darwin.creatures.size()==1);
	ASSERT_TRUE(Darwin.creatures[Darwin.grid[2][2]]].s==fox);

	Species water("food");
	d.add_creature(water,NORTH,2,1);
	ASSERT_TRUE(Darwin.creatures.size()==2);
}
TEST(Darwin, DarwinConstructorAdd_Two_Creatures2){
	Darwin d(10,20);
	Species fox("fox");
	
	d.add_creature(fox,NORTH,2,2);
	ASSERT_TRUE(Darwin.creatures.size()==1);
	ASSERT_TRUE(Darwin.creatures[Darwin.grid[2][2]]].s==fox);

	d.add_creature(fox,NORTH,2,1);
	ASSERT_TRUE(Darwin.creatures.size()==2);
}
TEST(Darwin, DarwinConstructorAdd_Two_Creatures3){
	Darwin d(10,20);
	Species food("food");
	
	d.add_creature(food,NORTH,2,2);
	ASSERT_TRUE(Darwin.creatures.size()==1);
	ASSERT_TRUE(Darwin.creatures[Darwin.grid[2][2]]].s==food);

	d.add_creature(food,NORTH,2,1);
	ASSERT_TRUE(Darwin.creatures.size()==2);
}
