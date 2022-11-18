#include "mc_combat.h"

#define MAX_ITERS   1000000


// Assume d10
enemy_t enemies[] = 
{
  { "Drone", 3,  2, Energy,  7.0 },
  { "Tank" , 6,  5, Kinetic, 5.0 },
  { "Raven", 2,  6, Plasma,  3.0 },
  { "Monk",  4,  2, Energy,  7.0 },
  { "Scout", 2,  3, Kinetic, 9.0 },
  { "Krone", 7,  4, Plasma,  5.0 },
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

char *rstring( int resistance )
{
  switch( resistance )
  {
    case 0: return "Energy"; break;
    case 1: return "Plasma"; break;
    case 2: return "Kinetic"; break;
  }

  return "Unknown";
}

#define stats( a, b, c ) ( ((float)a * 2.0 ) + ( (float)b * 1.5 ) + ( c * 1.0) )

void print_stats( void )
{
   int max_types = sizeof( enemies ) / sizeof( enemy_t );

   for ( int i = 0 ; i < max_types ; i++ )
   {
      printf("%9s %2d/%2d/%3.2f = %f\n", enemies[i].name,
                enemies[i].attack, enemies[i].armor, enemies[i].hp,
                stats( enemies[i].attack, enemies[i].armor, enemies[i].hp ) );
   }

   return;
}

void main( void )
{
   enemy_t player1, player2;
   int p1, p2;
   int max_types = sizeof( enemies ) / sizeof( enemy_t );
   int winner;
   int wins[2]={0,0};

   print_stats();

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

   printf("Wins: %s (%s) %d | %s (%s) %d\n", player1.name, rstring(player1.resistance), wins[0], 
            player2.name, rstring(player2.resistance), wins[1]);
   return;
}
