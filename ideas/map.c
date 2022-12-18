#include "headers.h"

cell_t map[ MAP_MAX_NCOLS ][ MAP_MAX_NROWS ];

void set_cell_static( int col, int row, char cell )
{
   map[ col ][ row ].type = type_static;
   map[ col ][ row ].u.static_map.cell = cell;
   map[ col ][ row ].location.col = col;
   map[ col ][ row ].location.row = row;
}

char get_cell( int col, int row )
{
   if ( col < 0 || row < 0 ||
        col >= MAP_MAX_NCOLS || row >= MAP_MAX_NROWS )
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
      // TBD
   }
   else
   {
      assert(0);
   }
   
   return '!';
}

void init_map( )
{
   memset( map, 0, sizeof( map ) );

   for ( int row = 0 ; row < MAP_MAX_NROWS ; row++ )
   {
      for ( int col = 0 ; col < MAP_MAX_NCOLS ; col++ )
      {
         set_cell_static( col, row, ' ' );
      }
   }
}

