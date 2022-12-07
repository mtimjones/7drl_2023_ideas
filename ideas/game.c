#include "headers.h"

int GameRunning = 0;

void start_game( void )
{
   GameRunning = 1;
}

void end_game( void )
{
   GameRunning = 0;
}

int get_game_state( void )
{
   return GameRunning;
}

