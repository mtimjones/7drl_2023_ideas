#include "mc_combat.h"

#define MAX_ITERS   1000000

int resist[3][3] = 
{ {  0,  1, -1 },  // Energy
  { -1,  0,  1 },  // Plasma
  {  1, -1,  0 }   // Kinetic
};

// Assume d10
enemy_t enemies[] = 
{
  { "Drone", 5,  2, Energy,  4.0 },
  { "Tank" , 7,  5, Kinetic, 7.0 },
  { "Raven", 2,  6, Plasma,  3.0 },
  { "Monk",  4,  1, Energy,  2.0 },
  { "Scout", 2,  3, Kinetic, 3.0 }
};

#if 0
float damage( int damage, int armor )
{
   float potential = ( damage - armor );

   if ( potential > 0.0 )
   {
      potential *= ( 0.5 * ( getSRand() / 2.0 ) );
   }
   else
   {
      potential = 0.0;
   }

   return potential;
}
#else
float damage( int attack, int armor )
{
   float potential = ( ( 1.0 / (float)( attack + armor ) ) * (float)attack );
   float damage = 0.0;

   if ( getSRand() < potential )
   {
      // Hit!  Compute damage.
      damage = (float)attack * getSRand();
   }

   return damage;
}
#endif

int fight( int player1, int player2 )
{
   enemy_t p1, p2;

   p1 = enemies[player1];
   p2 = enemies[player2];

   while (1)
   {
      p2.hp -= damage( p1.attack, p2.armor );

      if ( p2.hp <= 0.0 )
      {
         return player1;
      }
      else
      {
         p1.hp -= damage( p2.attack, p1.armor );
         if ( p1.hp <= 0.0 )
         {
            return player2;
         }
      }

   }

}

void main( void )
{
   int player1, player2, winner;
   int max_types = sizeof( enemies ) / sizeof( enemy_t );
   int wins[2]={0,0};

   seed();

   player1 = getRand( max_types );
   do
   {
      player2 = getRand( max_types );
   } while ( player2 == player1 );

   printf( "%s vs. %s\n", enemies[player1].name, enemies[player2].name );

   for ( int i = 0 ; i < MAX_ITERS ; i++ )
   {
      winner = fight( player1, player2 );

      if ( winner == player1 ) wins[0]++;
      else wins[1]++;
   }

   printf("Wins: %s %d | %s %d\n", enemies[player1].name, wins[0], enemies[player2].name, wins[1]);
   return;
}
