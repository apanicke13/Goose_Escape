#ifndef GOOSE_ESCAPE_GAMEPLAY
#define GOOSE_ESCAPE_GAMEPLAY
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"

/*This file is all about the game world. You will modify this to add
constants and function prototypes.  Modify gooseGamePlay.cpp to
actually add functionality.
*/

/*
Declare constants to indicate various game world features in the board
array.  Modify them to fit what you would like to do in the game. You can
change the type if you choose to store your game board as something other
than intengers.
*/	
// Going further:  Learn how to use an enum for these values
const bool UP= true;
const int FREE = 0;
const int POWER = 3;
const int SHALL_NOT_PASS = 1;
const int WINNER = 2;
const int WIN=13;
const int SUPE=20;
/*
    A few examples of characters both for actors and for the game board
    itself are shown.
*/	
//display characters
const int PLAYER_CHAR = int('H');
const int MONSTER_CHAR = int('G');
const int WALL_CHAR = int('*');
const int WIN_CHAR = int('W'); 
const int POWER_CHAR = int('+');
//% sign, a special character used in the ancient game "Rogue"

/*
    Game play function prototypes are give below.
*/
void print_board(int x, int y, int feature, char featureChar,
					int game_world[NUM_BOARD_X][NUM_BOARD_Y]);

void setup ( ifstream & fin_wall,ifstream & fin_power,
					int game_world[NUM_BOARD_X][NUM_BOARD_Y]);
/*
void print_board(int game_world)
{
	for(int i=0;i<100;i++)
	{
		for(int j=0; j<100;j++)
		{
			cout<<game_world[i][j];
		}
		cout<<endl;
	}
} */
// print the game board function protype

/*
    Do something when the goose captures the player
    
    If you want to attack or something else, this is the function you 
    need to change.  For example, maybe the two touch each other and
    then fight.  You could add a health to the Actor class that is
    updated.  Run, use weapons, it's up to you!
*/
bool captured(Actor const & player, Actor const & monster);

void wall_win_rebuilder(int x,int y,
						int game_world[NUM_BOARD_X][NUM_BOARD_Y]);

void power_point_checker(Actor & player, Actor & goose,
						int game_world[NUM_BOARD_X][NUM_BOARD_Y]);


/*
Move the player to a new location based on the user input.  You may want
to modify this if there are extra controls you want to add.
    
All key presses start with "TK_" then the character.  So "TK_A" is the a
key being pressed.
    
A look-up table might be useful.
You could decide to learn about switch statements and use them here.
*/

void movePlayer(int key, Actor & player,
				int game_world[NUM_BOARD_X][NUM_BOARD_Y]);

void move_the_Goose(Actor &player, Actor &goose,
					int game_world[NUM_BOARD_X][NUM_BOARD_Y]);

void s_power (int key, Actor & player, 
						int game_world[NUM_BOARD_X][NUM_BOARD_Y]);

/*
What other functions do you need to make the game work?  What can you
/add to the basic functionality to make it more fun to play?
*/


#endif
