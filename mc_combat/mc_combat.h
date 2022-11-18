#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum
{
   Energy,
   Plasma,
   Kinetic,
   Player
} resistance_t;

typedef struct 
{
   char *name;
   int attack;
   int armor;
   resistance_t resistance;
   float hp;
} enemy_t;

// Random functions
#define seed()       ( srand( time( NULL ) ) )
#define getSRand()   ( ( float ) rand( ) / ( float ) RAND_MAX )
#define getRand( x ) ( int ) ( ( x ) * getSRand( ) )

