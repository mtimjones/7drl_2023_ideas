#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef enum
{
   Energy,
   Plasma,
   Kinetic,
   Player
} resistence_t;

typedef struct 
{
   char *name;
   int attack;
   int armor;
   resistence_t resistence;
   float hp;
} enemy_t;

// Random functions
#define seed()       ( srand( time( NULL ) ) )
#define getSRand()   ( ( float ) rand( ) / ( float ) RAND_MAX )
#define getRand( x ) ( int ) ( ( x ) * getSRand( ) )

