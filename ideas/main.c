#include "headers.h"

int main( int argc, char *argv[] )
{
   srand( time( NULL ) );

   init_msg_log( );

   win_startup( );

   win_update( );

   start_game( );

   while ( get_game_state( ) )
   {
      unsigned long long start = getTimestamp( );

      win_refresh( );

      handle_user_input( );

      while( getTimestamp( ) < ( start + MS_PER_FRAME ) );

      increment_gametime( );

   }

   win_shutdown( );

   return 0;
}
