#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>

unsigned long long getTimestamp( void );
void increment_gametime( void );
unsigned int get_gametime( void );

#define MS_PER_FRAME   10

// Window functions...
void win_startup( );
void win_update( );
void win_refresh( );
char win_wait( );
void win_shutdown( );
