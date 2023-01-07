#include "headers.h"

// Migrate this into systems for general use...

void player_move( int cold, int rowd )
{
   location_t player_loc;

   player_loc.col = get_player_col( );
   player_loc.row = get_player_row( );

   if ( !passable( player_loc.col - cold, player_loc.row - rowd ) )
   {
      return;
   }

   clear_cell_entity( player_loc.col, player_loc.row );

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

   set_player_col( player_loc.col );
   set_player_row( player_loc.row );

   set_cell_entity( player_loc.col, player_loc.row, 0 );

   return;
}

