#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct
{
   char c;
   int  count;
} dir_t;

#define MAX_SYMBOLS 64

typedef enum
{
  North=0,
  South,
  West,
  East
} direction_t;

#define MAX_DIRECTION 4

typedef struct
{
   char  c;
   dir_t dirs[MAX_DIRECTION][MAX_SYMBOLS];
   int   len[MAX_DIRECTION];
} char_t;


