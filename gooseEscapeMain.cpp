#include <BearLibTerminal.h>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

//set up the console.   Don't modify this line!
Console out;


const int RANDOM=21;
const int MONSTER_X=70;
const int MONSTER_Y=20;

int random_position_generator(int rand_num)
{
	int r_num=rand_num;
	srand(time(0));
    int num=(rand () % r_num)+1;
    return num;
}

int main()
{
	int x=0,y=0;
	//Set up the window.  Don't edit these two lines
    terminal_open();
  	terminal_set(SETUP_MESSAGE);

	
/*
The code below provides a skeleton of the game play.  You will need to
write code for setting up the game board, and playing the game itself.
You can modify the code given as needed.
    
Call the functions that you have written in the game play file, and that
you have added to the Actor class.
*/
 	
    //make the player
  
    x=random_position_generator(80);
    y=random_position_generator(21);
	Actor player(PLAYER_CHAR, x,y); 
/* random function called to assign different starting
positions each time the game is played.*/
	
	//make the monster
	Actor monster(MONSTER_CHAR, MONSTER_X,MONSTER_Y);
	
    // Declare the array that will hold the game board "map"
  	int game_world[NUM_BOARD_X][NUM_BOARD_Y]={0};
/*
Initiallize locations in the game board to have game features.  What if you
have man things to add to the game board?  Should you use a loop?  Does it
make sense to store this information in a file?  Should this code be a
function as well?
*/
//we are using files to input the walls and the power up points into the game
	ifstream fin_wall("wall.txt");
	ifstream fin_power("power.txt");
	if(!fin_wall||!fin_power)
	{
		cout<<"ERROR IN FILE !!!";
		return 1;
	}

    /* game map location */
    /* game map location */ 
	game_world[WIN][WIN] = WINNER;	
  	
    // Call the function to print the game board
  	setup(fin_wall,fin_power,game_world);
	// Printing the instructions
    out.writeLine("Escape the Goose! " + monster.get_location_string());
	out.writeLine("Use the arrow keys to move");
	out.writeLine("If the goose catches you, you lose!");
	out.writeLine("Be careful! Sometimes the goose can jump walls!");

/*
This is the main game loop.  It continues to let the player give input
as long as they do not press escape or close, they are not captured by
the goose, and they didn't reach the win tile
*/
/*
All key presses start with "TK_" then the character.  So "TK_A" is the "a"
key being pressed.
*/
    int keyEntered = TK_A; 
    int previous_step = TK_A;
	// can be any valid value that is not ESCAPE or CLOSE
    
    while(keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE
	&& !captured(player,monster) &&
	game_world[player.get_x()][player.get_y()]!=WINNER)
	{
	    // get player key press
	    keyEntered = terminal_read();

        if (keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE)
        {
        	if (keyEntered==TK_P && player.power_up())
        	{
				s_power(previous_step,player,game_world);
  			}
			else
        	{
            // move the player, you can modify this function
    	    	movePlayer(keyEntered,player,game_world);
			}
            // call the goose's chase function
            move_the_Goose(player,monster,game_world);
            // call other functions to do stuff?
			if (!player.power_up())
				power_point_checker(player,monster,game_world);	    
        }
        
        if (keyEntered == TK_UP || keyEntered == TK_DOWN||keyEntered == TK_LEFT||keyEntered == TK_RIGHT)
        previous_step=keyEntered;
  	}

    if (keyEntered != TK_ESCAPE)
    {
      	//once we're out of the loop, the game is over
      	out.writeLine("Game Ended");
      	
      	if(captured(player,monster))
      		out.writeLine("The Goose have caught you!...Attempt Failed !!!");
      	else if (game_world[player.get_x()][player.get_y()]==WINNER)
      		out.writeLine("You have Out smarted the goose and reached a safe spot!!! Congratulations!!!");
        //out.writeLine("Game has ended");
    	 while (terminal_read() != TK_CLOSE);
    	 
// output why:  did the goose get us, or did we get to the win location?
    }	// Wait until user closes the window
       
    

	//game is done, close it  
    terminal_close();
}
