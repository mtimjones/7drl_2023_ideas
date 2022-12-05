#include "headers.h"

unsigned int GameRunning = 1;

int main( int argc, char *argv[] )
{
   srand( time( NULL ) );

   win_startup( );

   win_update( );

   while ( GameRunning )
   {
      unsigned long long start = getTimestamp( );

      win_refresh( );

      while( getTimestamp( ) < ( start + MS_PER_FRAME ) );

      increment_gametime( );

      if ( win_wait( ) == 27 ) GameRunning = 0;
   }

   win_shutdown( );

   return 0;
}
