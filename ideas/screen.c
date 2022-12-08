#include "headers.h"

WINDOW *mapwin, *invwin, *statswin, *actionswin, *contextwin, *logwin;

#define win_redisplay( win ) { touchwin( win ); wrefresh( win ); }

char context[ CONTEXTWIN_COL_SIZE+1 ];

void win_startup( )
{
   initscr( );
   clear( );
   noecho( );
   curs_set( 0 );
   nonl( );
   cbreak( );
   keypad( stdscr, TRUE );

   mouseinterval(0);
   printf("\033[?1003h\n");

   mousemask( ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL );

   return;
}

void win_update( )
{
   mapwin = newwin( MAPWIN_ROW_SIZE, MAPWIN_COL_SIZE, 
                     MAPWIN_ROW_START, MAPWIN_COL_START );
   box( mapwin, 0, 0 );
   mvwprintw( mapwin, 0, 2, " Map " );

   invwin = newwin( INVWIN_ROW_SIZE, INVWIN_COL_SIZE,
                       INVWIN_ROW_START, INVWIN_COL_START );
   box( invwin, 0, 0 );
   mvwprintw( invwin, 0, 2, " Inventory " );
   mvwprintw( invwin, 1, 2, "Object....  State.....  Lvl  HP " );

   statswin = newwin( STATSWIN_ROW_SIZE, STATSWIN_COL_SIZE,
                       STATSWIN_ROW_START, STATSWIN_COL_START );
   box( statswin, 0, 0 );
   mvwprintw( statswin, 0, 2, " Stats " );
   mvwprintw( statswin, 1, 2, "Attack: *** " );
   mvwprintw( statswin, 2, 2, "Armor : *** " );
   mvwprintw( statswin, 1, 17, "Mining    : *** " );
   mvwprintw( statswin, 2, 17, "Scavenging: *** " );
   mvwprintw( statswin, 4, 17, "Resources : *** " );

   actionswin = newwin( ACTIONSWIN_ROW_SIZE, ACTIONSWIN_COL_SIZE, 
                         ACTIONSWIN_ROW_START, ACTIONSWIN_COL_START );
   box( actionswin, 0, 0 );
   mvwprintw( actionswin, 0, 2, " Actions " );
   mvwprintw( actionswin, 1, 6, "[...(?) help...]  [..(p) pause...]  [...( ) step...]  [.(a)ssimilate.]  [....(d)ock....]" );
   mvwprintw( actionswin, 2, 6, "[....(k)ill....]  [..(r)ecycle...]  [....(m)ine....]  [..(s)cavenge..]  ]....(h)eal....]" );

   contextwin = newwin( CONTEXTWIN_ROW_SIZE, CONTEXTWIN_COL_SIZE, 
                         CONTEXTWIN_ROW_START, CONTEXTWIN_COL_START );
   box( contextwin, 0, 0 );
   mvwprintw( contextwin, 0, 2, " Context " );

   logwin = newwin( LOGWIN_ROW_SIZE, LOGWIN_COL_SIZE,
                     LOGWIN_ROW_START, LOGWIN_COL_START );
   box( logwin, 0, 0 );
   mvwprintw( logwin, 0, 2, " Log " );
   add_message( "Press '?' for help." );

   refresh( );

   WINDOW *introwin = newwin( INTROWIN_ROW_SIZE, INTROWIN_COL_SIZE,
                               INTROWIN_ROW_START, INTROWIN_COL_START );
   box( introwin, 0, 0 );
   mvwprintw( introwin, 0, 2, " Intro " );
   mvwprintw( introwin, 2, 2, "Welcome to BorgRL, a submission to the" );
   mvwprintw( introwin, 3, 2, "2023 7DRL.  You'll assimilate drones," );
   mvwprintw( introwin, 4, 2, "scavenge wrecks, mine planets, and" );
   mvwprintw( introwin, 5, 2, "increase their stats to reach the end." );
   mvwprintw( introwin, 6, 2, "Press any key to begin the game." );

   mvwprintw( introwin, 2, 2, "Welcome to BorgRL, a submission to the 2023 7DRL." );
   mvwprintw( introwin, 3, 2, "As the Borg, you'll assimilate enemies or attack" );
   mvwprintw( introwin, 4, 2, "them as well as scavenge wrecks and mine planets" );
   mvwprintw( introwin, 5, 2, "for resources (to upgrade your drones and their" );
   mvwprintw( introwin, 6, 2, "abilities).  Manage your drones and resources" );
   mvwprintw( introwin, 7, 2, "in order to reach the end and defeat the boss." );
   mvwprintw( introwin, 9, 2, "Click the mouse to being the game." );

   wrefresh( mapwin );
   wrefresh( invwin );
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
   win_redisplay( invwin );

   mvwprintw( statswin, 4, 2, "Time  : %4d ", ( get_gametime( ) / 100 ) );
   wrefresh( statswin );

   mvwprintw( contextwin, 1, 2, "%s", context );
   wrefresh( contextwin );

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
   // Disable mouse events
   printf("\033[?1003l\n");

   delwin( logwin );
   delwin( contextwin );
   delwin( actionswin );
   delwin( statswin );
   delwin( invwin );
   delwin( mapwin );

   endwin();

   return;
}

void set_context( char *line )
{
   strncpy( context, line, CONTEXTWIN_COL_SIZE-4 );
   int len = strlen( context );
   while ( len < CONTEXTWIN_COL_SIZE-4 )
   {
      context[len++] = ' ';
   }
   context[len] = 0;
}

void clear_context( void )
{
   char line[CONTEXTWIN_COL_SIZE];
   memset( line, ' ', sizeof( line ) );
   line[CONTEXTWIN_COL_SIZE-2] = 0;
   set_context( line );
}

int get_user_char( void )
{
   int c = wgetch( stdscr );

   if ( c != ERR ) return c;

   return 0;
}


