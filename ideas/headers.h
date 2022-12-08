#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>

//---------------------------------------------------------------
// Time API
//---------------------------------------------------------------

#define MS_PER_FRAME   10

unsigned long long getTimestamp( void );
void increment_gametime( void );
unsigned int get_gametime( void );

//---------------------------------------------------------------
// Window API
//---------------------------------------------------------------

void win_startup( );
void win_update( );
void win_refresh( );
char win_wait( );
void win_shutdown( );
int  get_user_char( );
void get_mouse_pos( unsigned int *col, unsigned int *row );
void set_context( char *line );
void clear_context( void );

//---------------------------------------------------------------
// User Input API
//---------------------------------------------------------------

void handle_user_input( void );

//---------------------------------------------------------------
// Game API
//---------------------------------------------------------------

void start_game( void );
void end_game( void );
int get_game_state( void );

//---------------------------------------------------------------
// Window constants
//---------------------------------------------------------------

#define MAPWIN_COL_START   0
#define MAPWIN_ROW_START   0
#define MAPWIN_COL_SIZE   65
#define MAPWIN_ROW_SIZE   27

#define INVWIN_COL_START  65
#define INVWIN_ROW_START   0
#define INVWIN_COL_SIZE   35
#define INVWIN_ROW_SIZE   21

#define STATSWIN_COL_START  65
#define STATSWIN_ROW_START  21
#define STATSWIN_COL_SIZE   35
#define STATSWIN_ROW_SIZE    6

#define ACTIONSWIN_COL_START   0
#define ACTIONSWIN_ROW_START  27
#define ACTIONSWIN_COL_SIZE  100
#define ACTIONSWIN_ROW_SIZE    4

#define CONTEXTWIN_COL_START   0
#define CONTEXTWIN_ROW_START  31
#define CONTEXTWIN_COL_SIZE  100
#define CONTEXTWIN_ROW_SIZE    3

#define LOGWIN_COL_START       0
#define LOGWIN_ROW_START      34
#define LOGWIN_COL_SIZE      100
#define LOGWIN_ROW_SIZE        6

#define INTROWIN_COL_START    30
#define INTROWIN_ROW_START    10
#define INTROWIN_COL_SIZE     42
#define INTROWIN_ROW_SIZE      9

//---------------------------------------------------------------
// Messages API
//---------------------------------------------------------------

#define MAX_MESSAGES 4
#define MAX_MSG_SIZE LOGWIN_COL_SIZE

void init_msg_log( void );
void add_message( char *fmt, ... );
char *get_message( int pos );

