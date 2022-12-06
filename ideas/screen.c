#include "headers.h"

WINDOW *mapwin, *dronewin, *statswin, *actionswin, *contextwin, *logwin;

#define win_redisplay( win ) { touchwin( win ); wrefresh( win ); }

void win_startup( )
{
   initscr();
   noecho();
   curs_set(0);

   return;
}

void win_update( )
{
   mapwin = newwin( 27, 65, 0, 0 );
   box( mapwin, 0, 0 );
   mvwprintw( mapwin, 0, 2, " Map " );

   dronewin = newwin( 21, 35, 0, 65 );
   box( dronewin, 0, 0 );
   mvwprintw( dronewin, 0, 2, " Inventory " );
   mvwprintw( dronewin, 1, 2, "Object....  State.....  Lvl  HP " );

   statswin = newwin( 6, 35, 21, 65 );
   box( statswin, 0, 0 );
   mvwprintw( statswin, 0, 2, " Stats " );
   mvwprintw( statswin, 1, 2, "Attack: *** " );
   mvwprintw( statswin, 2, 2, "Armor : *** " );
   mvwprintw( statswin, 1, 17, "Mining    : *** " );
   mvwprintw( statswin, 2, 17, "Scavenging: *** " );
   mvwprintw( statswin, 4, 17, "Resources : *** " );

   actionswin = newwin( 4, 100, 27, 0 );
   box( actionswin, 0, 0 );
   mvwprintw( actionswin, 0, 2, " Actions " );
   mvwprintw( actionswin, 1, 2, "1" );
   mvwprintw( actionswin, 2, 2, "2" );

   contextwin = newwin( 3, 100, 31, 0 );
   box( contextwin, 0, 0 );
   mvwprintw( contextwin, 0, 2, " Context " );

   logwin = newwin( 6, 100, 34, 0 );
   box( logwin, 0, 0 );
   mvwprintw( logwin, 0, 2, " Log " );
   add_message( "Press '?' for help." );

   refresh( );

   WINDOW *introwin = newwin( 9, 42, 10, 30 );
   box( introwin, 0, 0 );
   mvwprintw( introwin, 0, 2, " Intro " );
   mvwprintw( introwin, 2, 2, "Welcome to BorgRL, a submission to the" );
   mvwprintw( introwin, 3, 2, "2023 7DRL.  You'll assimilate drones," );
   mvwprintw( introwin, 4, 2, "scavange wrecks, mine planets, and" );
   mvwprintw( introwin, 5, 2, "increase their stats to reach the end." );
   mvwprintw( introwin, 6, 2, "Press any key to begin the game." );

   wrefresh( mapwin );
   wrefresh( dronewin );
   wrefresh( statswin );
   wrefresh( actionswin );
   wrefresh( contextwin );
   wrefresh( logwin );
   wrefresh( introwin );

   win_wait( );

   delwin( introwin );
   wrefresh( stdscr );

   // Turn on nodelay here since the intro screen is done.
   nodelay( stdscr, TRUE );
}

void win_refresh( void )
{
   win_redisplay( mapwin );
   win_redisplay( dronewin );
   mvwprintw( statswin, 4, 2, "Time  : %4d ", ( get_gametime( ) / 100 ) );
   wrefresh( statswin );

   for ( int i = 0 ; i < MAX_MESSAGES ; i++ )
   {
      mvwprintw( logwin, (i+1), 2, "%s", get_message( i ) );
   }
   wrefresh( logwin );

   wrefresh( stdscr );
}

char win_wait( )
{
   return wgetch( stdscr );
}

void win_shutdown( )
{
   delwin( logwin );
   delwin( contextwin );
   delwin( actionswin );
   delwin( statswin );
   delwin( dronewin );
   delwin( mapwin );

   endwin();

   return;
}

