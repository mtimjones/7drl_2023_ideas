#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>

// Time API
#define MS_PER_FRAME   10

unsigned long long getTimestamp( void );
void increment_gametime( void );
unsigned int get_gametime( void );

// Window API
void win_startup( );
void win_update( );
void win_refresh( );
char win_wait( );
void win_shutdown( );

// Messages API
#define MAX_MESSAGES 4
#define MAX_MSG_SIZE 70

void init_msg_log( void );
void add_message( char *msg );
char *get_message( int pos );


