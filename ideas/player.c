#include "headers.h"

location_t player_loc;

void init_player( void )
{
   player_loc.col = 0;
   player_loc.row = MAP_MAX_NROWS / 2;

}

int get_player_col( void )
{
   return player_loc.col;
}

int get_player_row( void )
{
   return player_loc.row;
}


