#include "headers.h"

void map_button_press( int col, int row, int state )
{
   int col_selected, row_selected;

   if ( col > 0 && row > 0 )
   {
      col_selected = col-1;
      row_selected = row-1;

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


