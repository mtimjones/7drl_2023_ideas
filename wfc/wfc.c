#include "wfc.h"

char_t symbols[ MAX_SYMBOLS ];
int num_symbols = 0;

void add( char symbol, char next, direction_t dir )
{
   int j;

   if ( !isprint(symbol) ) return;
   if ( ( next == 0x0a ) || ( next == 0x0d ) ) return;
   if ( next == 0 ) return;
   if ( !isprint(next) ) return;

   for ( int i = 0 ; i < num_symbols ; i++ )
   {
      if ( symbols[ i ].c == symbol )
      {
         for ( j = 0 ; j < symbols[i].len[dir] ; j++ )
         {
            if ( symbols[i].dirs[dir][j].c == next )
            {
               symbols[i].dirs[dir][j].count++;
               return;
            }
         
         }

         if ( j == symbols[i].len[dir] )
         {
            // Not found, add another next symbol.
            symbols[i].len[dir]++;
            symbols[i].dirs[dir][j].c = next;
            symbols[i].dirs[dir][j].count++;
            return;
         }
      }
   }

   // Not found, add a new one.
   symbols[num_symbols].c = symbol;
   num_symbols++;
   add( symbol, next, dir );

   return;
}

void readdata( char *filename )
{
   FILE *fptr;
   int cols, rows;
   int num;
   char line[80][80];
   int y, x;

   memset( symbols, 0, sizeof(symbols) );

   fptr = fopen( filename, "r" );

   num = fscanf( fptr, "DIM %d,%d", &cols, &rows );

   if ( num != 2 )
   {
      printf("Invalid dimension line.\n\n");
   }

   for ( num = 0 ; num < rows ; num++ )
   {
      fgets( &line[num][0], 80, fptr );
   }

   for ( y = 0 ; y < rows ; y++ )
   {
      for ( x = 0 ; x < cols ; x++ )
      {
         // North
         if ( y-1 >= 0 )
         {
             add( line[y][x], line[y-1][x], North );
         }

         // South
         if ( y+1 < rows )
         {
             add( line[y][x], line[y-1][x], South );
         }

         // West
         if ( x-1 >= 0 )
         {
             add( line[y][x], line[y][x-1], West );
         }
         // East
         if ( x+1 < cols )
         {
             add( line[y][x], line[y][x+1], East );
         }


      }
   }

   fclose( fptr );
}

void emit_dir( int i, direction_t dir )
{
   printf("\tDir %d: \n", dir);
   for ( int j = 0 ; j < symbols[i].len[dir] ; j++ )
   {
      printf("\t\t[%d] (%c)(%d) count %d\n", 
                j, symbols[i].dirs[dir][j].c, symbols[i].dirs[dir][j].c, 
                   symbols[i].dirs[dir][j].count);
   }

   return;
}

void printdata( void )
{
   for ( int i = 0 ; i < num_symbols ; i++ )
   {
      printf("[%d] Char (%c)(%d):\n", i, symbols[i].c, symbols[i].c);
      emit_dir( i, North );
      emit_dir( i, South );
      emit_dir( i, West );
      emit_dir( i, East );
      printf("\n\n");
   }

}

int main ( int argc, char* argv[] )
{
   if ( argc < 2 )
   {
      printf("\nUsage:\n\t%s <datafile>\n\n", argv[0]);
      exit(0);
   }

   readdata( argv[1] );
   
   printdata( );

   return 0;
}
