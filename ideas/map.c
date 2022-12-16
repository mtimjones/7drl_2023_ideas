#include <headers.h>
#include <map.h>

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
   (void)col;  (void)row;

   return ' ';
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

