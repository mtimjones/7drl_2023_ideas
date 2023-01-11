#include "headers.h"
#include "ces.h"

int main( int argc, char *argv[] )
{
//   static int cur_level = 0;
   (void)argc;
   (void)argv;

   seedRand( );

printf("init_msg_log\n");
   init_msg_log( );

printf("init_map\n");
   init_map( );

printf("init_entities\n");
   init_entities( );

printf("win_startup\n");
   win_startup( );

   win_update( );

   start_game( );

   // Game loop, runs at 20ms frames.
   while ( get_game_state( ) )
   {
      unsigned long long start = getTimestamp( );

#if 0
      // Does this serve a purpose any longer?
      if ( cur_level != get_level( ) )
      {
          cur_level = get_level( );
      }
#endif

      win_refresh( );

      handle_user_input( );

      if ( get_pause_state( ) == 0 )
      {
         increment_gametime( );

         // Invoke systems
      }

      while( getTimestamp( ) < ( start + MS_PER_FRAME ) );
   }

   win_shutdown( );

   return 0;
}
