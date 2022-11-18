#include "mc_combat.h"

#define MAX_ITERS   1000000


// Assume d10
enemy_t enemies[] = 
{
  { "Drone", 5,  2, Energy,  4.0 },
  { "Tank" , 7,  5, Kinetic, 7.0 },
  { "Raven", 2,  6, Plasma,  3.0 },
  { "Monk",  4,  1, Energy,  2.0 },
  { "Scout", 2,  3, Kinetic, 3.0 }
};

float damage( enemy_t attacker, enemy_t attackee )
{
   float damage = 0.0;
   float potential;
   const int resist[3][3] = 
      { {  0,  1, -1 },  // Energy
        { -1,  0,  1 },  // Plasma
        {  1, -1,  0 }   // Kinetic
      };

   potential = ( ( 1.0 / (float)( attacker.attack + attackee.armor ) ) * (float)attacker.attack );

   if ( getSRand() < potential )
   {
      // Hit!  Compute damage.
      damage = (float)attacker.attack * getSRand();

      // Add in status effects.
      damage += (float)resist[attacker.resistance][attackee.resistance];

      if ( damage < 0.0 ) damage = 0.0;
   }

   return damage;
}

int fight( enemy_t p1, enemy_t p2 )
{
   while (1)
   {
      p2.hp -= damage( p1, p2 );
      if ( p2.hp <= 0.0 )
      {
         return 0;
      }
      else
      {
         p1.hp -= damage( p2, p1 );
         if ( p1.hp <= 0.0 )
         {
            return 1;
         }
      }

   }

}

void main( void )
{
   enemy_t player1, player2;
   int p1, p2;
   int max_types = sizeof( enemies ) / sizeof( enemy_t );
   int winner;
   int wins[2]={0,0};

   seed();

   p1 = getRand( max_types );
   p2 = getRand( max_types );

   printf( "%s vs. %s\n", enemies[p1].name, enemies[p2].name );

   for ( int i = 0 ; i < MAX_ITERS ; i++ )
   {
      player1 = enemies[p1];
      player2 = enemies[p2];

      winner = fight( player1, player2 );

      wins[winner]++;
   }

   printf("Wins: %s %d | %s %d\n", player1.name, wins[0], player2.name, wins[1]);
   return;
}
