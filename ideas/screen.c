#include "headers.h"
#include "ces.h"

WINDOW *mapwin, *invwin, *statswin, *actionswin, *contextwin, *logwin;

#define win_redisplay( win ) { touchwin( win ); wrefresh( win ); }

void render_map( void );
void render_inv( void );

char context[ CONTEXTWIN_COL_SIZE+1 ];

static void init_colors( void )
{
   if ( !has_colors( ) ) exit(-1);

   start_color( );

   init_pair( COLOR_ENERGY, COLOR_RED, COLOR_BLACK );
   init_pair( COLOR_PLASMA, COLOR_BLUE, COLOR_BLACK );
   init_pair( COLOR_KINETIC, COLOR_GREEN, COLOR_BLACK );
   init_pair( COLOR_LABEL, COLOR_CYAN, COLOR_BLACK );
   init_pair( COLOR_BORG, COLOR_WHITE, COLOR_BLACK );
   init_pair( COLOR_WRECK, COLOR_YELLOW, COLOR_BLACK );
   init_pair( COLOR_PLANET, COLOR_MAGENTA, COLOR_BLACK );

   return;
}

void win_startup( )
{
   initscr( );
   clear( );
   noecho( );
   curs_set( 0 );
   nonl( );
   cbreak( );
   keypad( stdscr, TRUE );
   init_colors( );

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
   wattron( mapwin, A_BOLD | COLOR_PAIR(COLOR_LABEL) );
   mvwprintw( mapwin, 0, 2, " Map " );
   wattroff( mapwin, A_BOLD | COLOR_PAIR(COLOR_LABEL) );

   invwin = newwin( INVWIN_ROW_SIZE, INVWIN_COL_SIZE,
                       INVWIN_ROW_START, INVWIN_COL_START );
   box( invwin, 0, 0 );
   wattron( invwin, A_BOLD | COLOR_PAIR(COLOR_LABEL) );
   mvwprintw( invwin, 0, 2, " Inventory (dock) " );
   wattroff( invwin, A_BOLD | COLOR_PAIR(COLOR_LABEL) );
   mvwprintw( invwin, 1, 2, "Object.... State..... Lvl HP Max " );

   statswin = newwin( STATSWIN_ROW_SIZE, STATSWIN_COL_SIZE,
                       STATSWIN_ROW_START, STATSWIN_COL_START );
   box( statswin, 0, 0 );
   wattron( statswin, A_BOLD | COLOR_PAIR(COLOR_LABEL) );
   mvwprintw( statswin, 0, 2, " Stats " );
   wattroff( statswin, A_BOLD | COLOR_PAIR(COLOR_LABEL) );
   mvwprintw( statswin, 1, 2, "Attack: *** " );
   mvwprintw( statswin, 2, 2, "Armor : *** " );
   mvwprintw( statswin, 1, 17, "Mining    : *** " );
   mvwprintw( statswin, 2, 17, "Scavenging: *** " );
   mvwprintw( statswin, 5, 17, "Resources : *** " );

   actionswin = newwin( ACTIONSWIN_ROW_SIZE, ACTIONSWIN_COL_SIZE, 
                         ACTIONSWIN_ROW_START, ACTIONSWIN_COL_START );
   box( actionswin, 0, 0 );
   wattron( actionswin, A_BOLD | COLOR_PAIR(COLOR_LABEL) );
   mvwprintw( actionswin, 0, 2, " Actions " );
   wattroff( actionswin, A_BOLD | COLOR_PAIR(COLOR_LABEL) );
   mvwprintw( actionswin, 1, 3, "p - pause/unpause | Select docked drone and [ h - heal / r - recycle / select object in map ]." );
   mvwprintw( actionswin, 2, 3, "? - help          | Select enemy and [ a - assimilate ]. Select undocked drone and [ d - dock ]." );

   contextwin = newwin( CONTEXTWIN_ROW_SIZE, CONTEXTWIN_COL_SIZE, 
                         CONTEXTWIN_ROW_START, CONTEXTWIN_COL_START );
   box( contextwin, 0, 0 );
   wattron( contextwin, A_BOLD | COLOR_PAIR(COLOR_LABEL) );
   mvwprintw( contextwin, 0, 2, " Context " );
   wattroff( contextwin, A_BOLD | COLOR_PAIR(COLOR_LABEL) );

   logwin = newwin( LOGWIN_ROW_SIZE, LOGWIN_COL_SIZE,
                     LOGWIN_ROW_START, LOGWIN_COL_START );
   box( logwin, 0, 0 );
   wattron( logwin, A_BOLD | COLOR_PAIR(COLOR_LABEL) );
   mvwprintw( logwin, 0, 2, " Log " );
   wattroff( logwin, A_BOLD | COLOR_PAIR(COLOR_LABEL) );
   add_message( "Press '?' for help." );

   refresh( );

   WINDOW *introwin = newwin( INTROWIN_ROW_SIZE, INTROWIN_COL_SIZE,
                               INTROWIN_ROW_START, INTROWIN_COL_START );
   box( introwin, 0, 0 );
   wattron( introwin, A_BOLD | COLOR_PAIR(COLOR_LABEL) );
   mvwprintw( introwin, 0, 2, " Introduction " );
   wattroff( introwin, A_BOLD | COLOR_PAIR(COLOR_LABEL) );
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

   render_map( );
   win_redisplay( mapwin );

   render_inv( );
   win_redisplay( invwin );

   if ( get_pause_state( ) )
   {
      wattron( statswin, A_STANDOUT );
      mvwprintw( statswin, 3, 2, "Game paused." );
      wattroff( statswin, A_STANDOUT );
   }
   else
   {
      mvwprintw( statswin, 3, 2, "            " );
   }

   mvwprintw( statswin, 3, 17, "Mouse  %3d, %3d", get_mouse_col( ), get_mouse_row( ) );
   mvwprintw( statswin, 4, 17, "Player %3d, %3d", get_player_col( ), get_player_row( ) );

   mvwprintw( statswin, 4, 2, "Level : %4d ", get_level( ) );
   mvwprintw( statswin, 5, 2, "Time  : %4d ", ( get_gametime( ) / 50 ) );

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

void emit_help( void )
{
   WINDOW *helpwin = newwin( 10, 70, 10, 15 );
   box( helpwin, 0, 0 );
   wattron( helpwin, A_BOLD | COLOR_PAIR(COLOR_LABEL) );
   mvwprintw( helpwin, 0, 2, " Help " );
   wattroff( helpwin, A_BOLD | COLOR_PAIR(COLOR_LABEL) );
   mvwprintw( helpwin, 2, 2, "Make your way through each sector, escaping through the gate." );
   mvwprintw( helpwin, 3, 2, "Fight, mine, scavange, heal, recycle, and upgrade your drones." );
   mvwprintw( helpwin, 4, 2, "Move with the arrow keys. Select a drone from the map or inventory" );
   mvwprintw( helpwin, 5, 2, "window and a target in the map window to begin.  Select an enemy" );
   mvwprintw( helpwin, 6, 2, "and 'a' to assimilate.  Select a docked drone and 'h' to heal it" );
   mvwprintw( helpwin, 7, 2, "or 'r' to recycle it for resources.  Press any key to continue." );
   nodelay( stdscr, FALSE );
   wrefresh( helpwin );
   win_wait( );
   nodelay( stdscr, TRUE );
   wrefresh( stdscr );
}

int get_user_char( void )
{
   int c = wgetch( stdscr );

   if ( c != ERR ) return c;

   return 0;
}

void put_char( int col, int row, char cell, unsigned int attr )
{
   mvwaddch( mapwin, row+1, col+1, cell | attr );
}

void render_map( void )
{
   int row, col;
   const int map_col_midpoint = ( ( MAPWIN_COL_SIZE-2 ) >> 1 );
   const int map_row_midpoint = ( ( MAPWIN_ROW_SIZE-2 ) >> 1 );
   int prow = get_player_row( );
   int pcol = get_player_col( );

   for ( int r = 0 ; r < ( MAPWIN_ROW_SIZE-2 ) ; r++ )
   {
      row = prow - map_row_midpoint + r;

      for ( int c = 0 ; c < ( MAPWIN_COL_SIZE-2 ) ; c++ )
      {
         col = pcol - map_col_midpoint + c;
         mvwaddch( mapwin, r+1, c+1, get_cell( col, row ) );
      }

   }

   return;
}

void render_inv( void )
{
   char object[11];
   char state [11];
   int  level, hp, max_hp;

   for ( int i = 0 ; i < INVWIN_ROW_SIZE-2 ; i++ )
   {
      bool result = get_player_inv( i, object, state, &level, &hp, &max_hp );

      if ( result ) 
      {
         mvwprintw( invwin, 2+i, 2, "%10s %10s %3d %2d %3d", object, state, level, hp, max_hp );

      }
   }

   return;
}

