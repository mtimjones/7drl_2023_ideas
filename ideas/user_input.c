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
   }
   else if ( c == KEY_MOUSE )
   {
      // Handle mouse event.
      if ( getmouse( &event ) == OK )
      {
         exit(0);
      }
   }
   else
   {
      // Handle keyboard input.
      if ( c == 'x' ) end_game( );
   }

   return;
}

