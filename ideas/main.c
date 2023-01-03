#include "headers.h"
#include "ces.h"

int main( int argc, char *argv[] )
{
   (void)argc;
   (void)argv;

   seedRand( );

   init_msg_log( );

   win_startup( );

   init_map( );

   init_entities( );

   win_update( );

   start_game( );

   // Game loop, runs at 10ms frames.
   while ( get_game_state( ) )
   {
      unsigned long long start = getTimestamp( );

      win_refresh( );

      handle_user_input( );

      while( getTimestamp( ) < ( start + MS_PER_FRAME ) );

      if ( get_pause_state( ) == 0 )
      {
         increment_gametime( );

         // Invoke systems
      }

   }

   win_shutdown( );

   return 0;
}
