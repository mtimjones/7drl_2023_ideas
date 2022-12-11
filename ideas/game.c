#include "headers.h"

static int GameRunning = 0;
static int Paused = 0;

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

void pause_toggle( void )
{
   Paused = !Paused;
}

int get_pause_state( void )
{
   return Paused;
}

