#include "headers.h"

location_t player_loc;

void init_player( void )
{
   player_loc.col = MAP_MAX_NCOLS >> 1;
   player_loc.row = MAP_MAX_NROWS >> 1;
}

int get_player_col( void )
{
   return player_loc.col;
}

int get_player_row( void )
{
   return player_loc.row;
}

void player_move( int rowd, int cold )
{
   player_loc.row -= rowd;
   player_loc.col -= cold;

   if ( player_loc.row < 0 )
   {
      player_loc.row = 0;
   }
   else if ( player_loc.col < 0 )
   {
      player_loc.col = 0;
   }
   else if ( player_loc.row >= MAP_MAX_NROWS )
   {
      player_loc.row = MAP_MAX_NROWS - 1;
   }
   else if ( player_loc.col >= MAP_MAX_NCOLS )
   {
      player_loc.col = MAP_MAX_NCOLS - 1;
   }

   return;
}
