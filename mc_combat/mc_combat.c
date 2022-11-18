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

float damage( int attacker, int attackee )
{
   float damage = 0.0;
   float potential;
   const int resist[3][3] = 
      { {  0,  1, -1 },  // Energy
        { -1,  0,  1 },  // Plasma
        {  1, -1,  0 }   // Kinetic
      };

//printf("player1 attack %d player 2 armor %d\n", enemies[attacker].attack, enemies[attackee].armor);

   potential = ( ( 1.0 / (float)( enemies[attacker].attack + enemies[attackee].armor ) ) * 
                (float)enemies[attacker].attack );

//printf("potential %f\n", potential);

   if ( getSRand() < potential )
   {
      // Hit!  Compute damage.
      damage = (float)enemies[attacker].attack * getSRand();

      // Add in status effects.
      damage += (float)resist[enemies[attacker].resistance][enemies[attackee].resistance];

      if ( damage < 0.0 ) damage = 0.0;
   }

   return damage;
}

int fight( int player1, int player2 )
{
   enemy_t p1, p2;

   p1 = enemies[player1];
   p2 = enemies[player2];

   while (1)
   {
      p2.hp -= damage( player1, player2 );
      if ( p2.hp <= 0.0 )
      {
         return player1;
      }
      else
      {
         p1.hp -= damage( player2, player1 );
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
