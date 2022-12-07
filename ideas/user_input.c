#include "headers.h"

void handle_user_input( void )
{
   int c;
   MEVENT event;

   // Check keyboard input.
   c = get_user_char( );

   if ( c == 0 )
   {
      // No character received.
      return;
   }
   else if ( c == KEY_MOUSE )
   {
      // Handle mouse event.
      if ( getmouse( &event ) == OK )
      {
          add_message( "Mouse at %d, %d, %d", event.x, event.y, event.z );
          if ( event.x >= 0 && event.x < 100 && event.y >=34 && event.y < 40 )
          {
              set_context( "Log window..." );
          }
          else
          {
              clear_context( );
          }
      }
   }
   else
   {
      // Handle keyboard input.
      if ( c == 'x' ) end_game( );
   }

   return;
}

