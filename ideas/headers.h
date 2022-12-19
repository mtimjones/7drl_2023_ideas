//---------------------------------------------------------------------------
// File: headers.h
//
//   Contains all symbols used in the application.
//
//---------------------------------------------------------------------------

#ifndef __HEADERS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>
#include <assert.h>

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
void emit_help( );

//---------------------------------------------------------------
// User Input API
//---------------------------------------------------------------

void handle_user_input( void );
int  get_mouse_posx( void );
int  get_mouse_posy( void );

//---------------------------------------------------------------
// Game API
//---------------------------------------------------------------

void start_game( void );
void end_game( void );
int get_game_state( void );
void pause_toggle( void );
int get_pause_state( void );

//---------------------------------------------------------------
// Window constants
//---------------------------------------------------------------

#define MAPWIN_COL_START       0
#define MAPWIN_ROW_START       0
#define MAPWIN_COL_SIZE       67
#define MAPWIN_ROW_SIZE       29

#define INVWIN_COL_START      67
#define INVWIN_ROW_START       0
#define INVWIN_COL_SIZE       40
#define INVWIN_ROW_SIZE       22

#define STATSWIN_COL_START    67
#define STATSWIN_ROW_START    22
#define STATSWIN_COL_SIZE     40
#define STATSWIN_ROW_SIZE      7

#define ACTIONSWIN_COL_START   0
#define ACTIONSWIN_ROW_START  29
#define ACTIONSWIN_COL_SIZE  107
#define ACTIONSWIN_ROW_SIZE    4

#define CONTEXTWIN_COL_START   0
#define CONTEXTWIN_ROW_START  33
#define CONTEXTWIN_COL_SIZE  107
#define CONTEXTWIN_ROW_SIZE    3

#define LOGWIN_COL_START       0
#define LOGWIN_ROW_START      36
#define LOGWIN_COL_SIZE      107
#define LOGWIN_ROW_SIZE        6

#define INTROWIN_COL_START    24
#define INTROWIN_ROW_START     9
#define INTROWIN_COL_SIZE     54
#define INTROWIN_ROW_SIZE     12

//---------------------------------------------------------------
// Messages API
//---------------------------------------------------------------

#define MAX_MESSAGES 4
#define MAX_MSG_SIZE LOGWIN_COL_SIZE-2

void init_msg_log( void );
void add_message( char *fmt, ... );
char *get_message( int pos );

//---------------------------------------------------------------
// Map API
//---------------------------------------------------------------

#define MAP_MAX_NCOLS ( MAPWIN_COL_SIZE * 9 )
#define MAP_MAX_NROWS ( MAPWIN_ROW_SIZE * 3 )

void init_map( void );

#define COLOR_PLASMA    1
#define COLOR_ENERGY    2
#define COLOR_KINETIC   3
#define COLOR_LABEL     4
#define COLOR_BORG      5

char get_cell( int col, int row );

void render_map( void );

void player_move( int row, int col );

#define MAX_STATES 8

typedef enum
{
   type_static,
   type_dynamic,
} type_t;

typedef struct
{
   char cell;
} static_map_t;

typedef struct
{
   int state;
   int max_state;
   int cells[ MAX_STATES ];
} dynamic_map_t;

typedef struct
{
   int col;
   int row;
} location_t;

typedef struct
{
   type_t type;

   union {
      static_map_t static_map;
      dynamic_map_t dynamic_map;
   } u;

   location_t location;

   bool visited;
   bool passable;
   // bool visible; // Computed dynamically

   // entity_id_t entity; // handled dynamically with a rendering order.

} cell_t;

//---------------------------------------------------------------
// Select API
//---------------------------------------------------------------

void map_button_press( int col, int row, int state );
void inv_button_press( int col, int row, int state );

//---------------------------------------------------------------
// Player API
//---------------------------------------------------------------

void init_player( void );
int get_player_col( void );
int get_player_row( void );

#endif // __HEADERS_H__
