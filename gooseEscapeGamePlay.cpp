#include<BearLibTerminal.h>
#include<cmath>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
using namespace std;
#include<BearLibTerminal.h>
#include"gooseEscapeUtil.hpp"
#include"gooseEscapeActors.hpp"
#include"gooseEscapeConsole.hpp"
#include"gooseEscapeGamePlay.hpp"

extern Console out;
/*
With graphics, screens are given an x,y coordinate system with the origin
in the upper left corner.  So it means the coordinate axes are:
---------------->   x direction
|
|
|
|
|
V

y direction 
*/

const int MAN_STEP=1;
const float GOOSE_STEP=1;
/*
    Print the game world
    
    The functions should draw characters to present features of the game
    board, e.g. win location, obstacles, power ups
*/

// print the game board function
void print_board(int x, int y, int feature, char featureChar,
					int game_world[NUM_BOARD_X][NUM_BOARD_Y])
{
	game_world[x][y]=feature;
	terminal_put(x,y,featureChar);
}


void setup (ifstream & fin_wall,ifstream & fin_power,
						int game_world[NUM_BOARD_X][NUM_BOARD_Y])
{
	int straight=0,num=0,first_line=0,last_line=0,power_x=0,power_y=0;
	while(fin_wall>>straight>>num>>first_line>>last_line)
	{
		for(int rowcol=first_line;rowcol<=last_line;rowcol++)
		{
			if(straight!=0)
			{
				print_board(rowcol,num,SHALL_NOT_PASS,
					WALL_CHAR,game_world);
			}
			else
			{
				print_board(num,rowcol,SHALL_NOT_PASS,
					WALL_CHAR,game_world);
			}
		}
	}
	print_board(WIN,WIN,WINNER,WIN_CHAR,game_world);
	while(fin_power>>power_x>>power_y)
	{
		print_board(power_x,power_y,POWER,POWER_CHAR,game_world);
	}
		
	
	terminal_refresh();
}

/*
Do something when the goose captures the player
    
If you want to attack or something else, this is the function you 
need to change.  For example, maybe the two touch each other and
then fight.  You could add a health to the Actor class that is
updated.  Run, use weapons, it's up to you!
*/

bool captured(Actor const & player, Actor const & monster)
{
    return (player.get_x() == monster.get_x() 
         && player.get_y() == monster.get_y());
}

/*
Move the player to a new location based on the user input.You may want
to modify this if there are extra controls you want to add.
    
All key presses start with "TK_" then the character.So "TK_A" is the a
key being pressed.
    
A look-up table might be useful.
You could decide to learn about switch statements and use them here.
*/

/*we have created a function that takes in the parameters where
the goose and the student pass through and if the goose goes through
any wall or passes the safe spot while catching the student then the
below function will replace that wall or the safe spot icon.*/
void wall_win_rebuilder(int x,int y,
					int game_world[NUM_BOARD_X][NUM_BOARD_Y])
{
	if(game_world[x][y]==SHALL_NOT_PASS)
	{
		terminal_put(x,y,WALL_CHAR);
	}
	else if(game_world[x][y]==WINNER)
	{
		terminal_put(x,y,WIN_CHAR);
	}
	
	terminal_refresh();
}

void power_point_checker(Actor & player, Actor & goose,
							int game_world[NUM_BOARD_X][NUM_BOARD_Y])
{
	if(game_world[player.get_x()][player.get_y()]==POWER)
	{
		goose.set_power(UP);
		player.set_power(UP);		
		out.writeLine("Extra Energy for you and the goose!");
		out.writeLine("The Goose's speed has increased!!");
		out.writeLine("You get to make a jump of 20 steps just once"
						" by pressing P");
		out.writeLine("Use it wisely buddy!!");
		
		game_world[player.get_x()][player.get_y()]==FREE;
	}
}


void movePlayer(int key, Actor & player,
				int game_world[NUM_BOARD_X][NUM_BOARD_Y])
{
    int yMove = 0, xMove = 0;
    if (key == TK_UP)
        yMove = -MAN_STEP;
    else if (key == TK_DOWN)
        yMove = MAN_STEP;
    else if (key == TK_LEFT)
        xMove = -MAN_STEP;
    else if (key == TK_RIGHT)
        xMove = MAN_STEP;
        
    int prev_X=player.get_x();
    int prev_Y=player.get_y();
    
    
    if (game_world[player.get_x()+xMove]
				[player.get_y()+yMove]!=SHALL_NOT_PASS)
    {
    	player.update_location(xMove, yMove);
	}
        
   wall_win_rebuilder(prev_X,prev_Y,game_world);
}


void move_the_Goose(Actor &player, Actor &goose,
					int game_world[NUM_BOARD_X][NUM_BOARD_Y])
{
	int x_move=0;
	int y_move=0;
	int big_step=1;
	if(!goose.power_up())
	{
		if(player.get_x()<goose.get_x())
		{
			x_move=-GOOSE_STEP;
		}
		else if(player.get_x()>goose.get_x())
		{
			x_move=GOOSE_STEP;
		}
		if(player.get_y()<goose.get_y())
		{
			y_move=-GOOSE_STEP;
		}
		else if(player.get_y()>goose.get_y())
		{
			y_move=GOOSE_STEP;
		}
		if (goose.can_move(x_move, y_move))
	    {
	    	int prev_x=goose.get_x();
			int prev_y=goose.get_y();
			
		    goose.update_location(x_move, y_move);
	        wall_win_rebuilder(prev_x,prev_y,game_world);
		}
	}
	
	else
	{
		if(goose.power_up())
		{
			big_step=3;
			
			if(player.get_x()<goose.get_x())
			{
				x_move=max(-big_step,player.get_x()-goose.get_x());
			}
			else if(player.get_x()>goose.get_x())
			{
				x_move=min(big_step,player.get_x()-goose.get_x());
			}
			
			if(player.get_y()<goose.get_y())
			{
				y_move=max(-big_step,player.get_y()-goose.get_y());
			}
			else if(player.get_y()>goose.get_y())
			{
				y_move=min(big_step,player.get_y()-goose.get_y());
			}
		}
	}
	int prev_x=goose.get_x();
	int prev_y=goose.get_y();
	goose.update_location(x_move, y_move);
	wall_win_rebuilder(prev_x,prev_y,game_world);

}



void s_power (int key, Actor & player,
					int game_board[NUM_BOARD_X][NUM_BOARD_Y])
{
	player.set_power(!POWER);
	int yMove=0, xMove=0;
	
	if(key==TK_RIGHT)
	{
		xMove=SUPE;
		
		if((xMove + player.get_x())>MAX_BOARD_X)
		{
			xMove=MAX_BOARD_X-player.get_x();
		}
	}
	
	else if (key==TK_LEFT)
	{
		xMove=-SUPE;
		
		if((xMove + player.get_x())<MIN_BOARD_X)
		{
			xMove=MIN_BOARD_X-player.get_x();
		}
	}
	else if (key==TK_UP)
	{
		yMove=-SUPE;
		if((yMove + player.get_y())<MIN_BOARD_Y)
		{
			yMove=MIN_BOARD_Y-player.get_y();
		}
	}
	
	else if (key==TK_DOWN)
	{
		yMove=SUPE;
		if((yMove + player.get_y())>MAX_BOARD_Y)
		{
			yMove=MAX_BOARD_Y-player.get_y();
		}
	}
	
	player.update_location(xMove,yMove);
}

/*
What other functions do you need to make the game work?  What can you
add to the basic functionality to make it more fun to play?
*/
