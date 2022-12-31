#include "headers.h"

void map_button_press( int col, int row, int state )
{
   int col_selected, row_selected;
   const int map_col_midpoint = ( ( MAPWIN_COL_SIZE-2 ) >> 1 );
   const int map_row_midpoint = ( ( MAPWIN_ROW_SIZE-2 ) >> 1 );

   col_selected = get_player_col( ) - map_col_midpoint + col-1;
   row_selected = get_player_row( ) - map_row_midpoint + row-1;

   if ( valid_map_location( col_selected, row_selected ) )
   {
      if ( state == BUTTON1_PRESSED )
      {
         add_message( "Left-click select of map object at %d,%d", col_selected, row_selected );

      }
      else if ( state == BUTTON3_PRESSED )
      {
         add_message( "Right-click select of map object at %d,%d", col_selected, row_selected );
      }
   }
}

void inv_button_press( int col, int row, int state )
{
   (void)col;

   if ( state == BUTTON1_PRESSED )
   {
      if ( row >= 2 )
      {
         int row_selected = row - 2;
         add_message( "Left-click select of inv item %d", row_selected );
      }
   }

}


