#include "headers.h"

cell_t map[ MAP_MAX_NCOLS ][ MAP_MAX_NROWS ];

void set_cell_uninit( int col, int row )
{
   map[ col ][ row ].type = type_uninit;
   map[ col ][ row ].location.col = col;
   map[ col ][ row ].location.row = row;
   map[ col ][ row ].passable = true;
}

void set_cell_passable( int col, int row, bool passable )
{
   map[ col ][ row ].passable = passable;
}

void set_cell_static( int col, int row, char cell, bool passable )
{
   map[ col ][ row ].type = type_static;
   map[ col ][ row ].location.col = col;
   map[ col ][ row ].location.row = row;
   map[ col ][ row ].u.static_map.cell = cell;
   map[ col ][ row ].passable = passable;
}

void set_cell_dynamic( int col, int row, int state_cnt, char *states, int delay, bool passable )
{
   map[ col ][ row ].type = type_dynamic;
   map[ col ][ row ].location.col = col;
   map[ col ][ row ].location.row = row;
   map[ col ][ row ].u.dynamic_map.delay = delay;
   map[ col ][ row ].u.dynamic_map.cur_delay = 0;
   map[ col ][ row ].u.dynamic_map.state = 0;
   map[ col ][ row ].u.dynamic_map.max_state = state_cnt;
   map[ col ][ row ].passable = passable;

   for ( int i = 0 ; i < state_cnt ; i++ )
   {
      map[ col ][ row ].u.dynamic_map.cells[ i ] = states[ i ];
   }

   return;
}

bool passable( int col, int row )
{
   return map[ col ][ row ].passable;
}

char get_cell( int col, int row )
{
   if ( col < 0 || row < 0 ||
        col >= MAP_MAX_NCOLS  || row >= MAP_MAX_NROWS )
   {
      // Void space (outside of the map).
      return '~';
   }
   else if ( map[ col ][ row ].type == type_static )
   {
      return map[ col ][ row ].u.static_map.cell;
   }
   else if ( map[ col ][ row ].type == type_dynamic )
   {
      if ( map[ col ][ row ].u.dynamic_map.cur_delay < map[ col ][ row ].u.dynamic_map.delay )
      {
         map[ col ][ row ].u.dynamic_map.cur_delay++;
      }
      else
      {
         map[ col ][ row ].u.dynamic_map.cur_delay = 0;
         if ( ++map[ col ][ row ].u.dynamic_map.state >= map[ col ][ row ].u.dynamic_map.max_state )
         {
            map[ col ][ row ].u.dynamic_map.state = 0;
         }
      }
      return map[ col ][ row ].u.dynamic_map.cells[ map[ col ][ row ].u.dynamic_map.state ];
   }
   else if ( map[ col ][ row ].type == type_uninit )
   {
      return ' ';
   }
   else
   {
      assert(0);
   }
   
   return '!';
}

void place_wreck( int col, int row )
{
   do 
   {
      col += getRand( MAPWIN_COL_SIZE );
      row += getRand( MAPWIN_ROW_SIZE );
   } 
   while ( !map[ col ][ row ].type == type_uninit );

   set_cell_static( col, row, '%', false );

   return;
}

void init_map_assets( void )
{
   //int row, col;
   int count = 0;

   for ( int sector_row = 0 ; sector_row < MAP_MAX_NROWS ; sector_row += MAPWIN_ROW_SIZE )
   {
      for ( int sector_col = 0 ; sector_col < MAP_MAX_NCOLS ; sector_col += MAPWIN_COL_SIZE )
      {
         // Place wrecks
         if ( getSRand( ) > 0.6 )
         {
            place_wreck( sector_col, sector_row );
            count++;
         }

      }

   }

   add_message("Added %d wrecks.", count);

}

void init_map( void )
{
   memset( map, 0, sizeof( map ) );

   for ( int row = 0 ; row < MAP_MAX_NROWS ; row++ )
   {
      for ( int col = 0 ; col < MAP_MAX_NCOLS ; col++ )
      {
         set_cell_uninit( col, row );
      }
   }

   init_map_assets( );

   set_cell_dynamic( 12, 12, 4, "|/-\\", 20, false );

   set_cell_dynamic( 10, 10, 4, "^>v<", 87, false );

   set_cell_dynamic( 14, 18, 5, ">    ", 30, false );
   set_cell_dynamic( 16, 18, 5, " >   ", 30, false );
   set_cell_dynamic( 18, 18, 5, "  >  ", 30, false );
   set_cell_dynamic( 20, 18, 5, "   > ", 30, false );
   set_cell_dynamic( 22, 18, 5, "    >", 30, false );
}

