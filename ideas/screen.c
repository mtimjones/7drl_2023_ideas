#include "headers.h"

int main( int argc, char *argv[] )
{
   initscr();
   noecho();
   curs_set(0);

   WINDOW *mapwin = newwin( 27, 65, 0, 0 );
   box( mapwin, 0, 0 );
   mvwprintw( mapwin, 0, 2, " Map " );

   WINDOW *dronewin = newwin( 21, 35, 0, 65 );
   box( dronewin, 0, 0 );
   mvwprintw( dronewin, 0, 2, " Inventory " );
   mvwprintw( dronewin, 1, 2, "Object....  State.....  Lvl  HP " );

   WINDOW *statswin = newwin( 6, 35, 21, 65 );
   box( statswin, 0, 0 );
   mvwprintw( statswin, 0, 2, " Stats " );
   mvwprintw( statswin, 1, 2, "Attack: *** " );
   mvwprintw( statswin, 2, 2, "Armor : *** " );
   mvwprintw( statswin, 4, 2, "Time  : **** " );
   mvwprintw( statswin, 1, 17, "Mining    : *** " );
   mvwprintw( statswin, 2, 17, "Scavenging: *** " );
   mvwprintw( statswin, 4, 17, "Resources : *** " );

   WINDOW *actionswin = newwin( 4, 100, 27, 0 );
   box( actionswin, 0, 0 );
   mvwprintw( actionswin, 0, 2, " Actions " );
   mvwprintw( actionswin, 1, 2, "1" );
   mvwprintw( actionswin, 2, 2, "2" );

   WINDOW *contextwin = newwin( 3, 100, 31, 0 );
   box( contextwin, 0, 0 );
   mvwprintw( contextwin, 0, 2, " Context " );

   WINDOW *logwin = newwin( 6, 100, 34, 0 );
   box( logwin, 0, 0 );
   mvwprintw( logwin, 0, 2, " Log " );

   WINDOW *introwin = newwin( 9, 42, 10, 30 );
   box( introwin, 0, 0 );
   mvwprintw( introwin, 0, 2, " Intro " );
   mvwprintw( introwin, 2, 2, "Welcome to BorgRL, a submission to the" );
   mvwprintw( introwin, 3, 2, "2023 7DRL.  You'll assimilate drones," );
   mvwprintw( introwin, 4, 2, "scavange wrecks, mine planets, and" );
   mvwprintw( introwin, 5, 2, "increase their stats to reach the end." );
   mvwprintw( introwin, 6, 2, "Press any key to begin the game." );
   wrefresh( introwin );

   wgetch( introwin );

   wrefresh( mapwin );
   wrefresh( dronewin );
   wrefresh( statswin );
   wrefresh( actionswin );
   wrefresh( contextwin );
   wrefresh( logwin );

   wgetch( mapwin );

   delwin( introwin );

   endwin();
}

#if 0   
           1         2         3         4         5         6         7         8         9         1
  1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
 1+----------------------------------------------------------------+---------------------------------+
 2|                                                                | Object....  State.....  Lvl  HP |
 3|                                                            A   | Borg        @             1   2 |
 4|                                                                | Drone       Docked        1   2 |
 5|                                                  ###           | Scout       Docked        1   3 |
 6|                                                #######         | Digger      Docked        1   1 |
 7|                       %                      #########         | Vagrant     Undocked      1   1 |
 8|                                             ###########        |                                 |
 9|                                               ###########      |                                 |
10|                                                #########       |                                 |
11|                           V                     #######        |                                 |
12|                                                   ####         |                                 |
13|                                                    ##          |                                 |
14|                               @                                |                                 |
15|      ####                                                      |                                 |
16|   ##########                                                   |                                 |
17|  ##########                                                    |                                 |
18|   ########                                                ?    |                                 |
19|    ######                                                      |                                 |
20|     ####                                                       |                                 |
21|      ##                                                        |                                 |
22|            R                                                 ##+---------------------------------+
23|                                                           #####|  Attack: ***   Mining    : ***  |
24|                                           P             #######|  Armor : ***   Scavanging: ***  |
25|                                                       #########|                Stealth   : ***  |
26|                                                     ###########|  Time: ****    Resources: ****  |
27+----------------------------------------------------------------+---------------------------------+
28|         |    (?)help   |   (p)ause    |   ( )step    | (a)ssimilate |    (d)ock    |             |
29| Actions +--------------+--------------+--------------+--------------+--------------+-------------+
30|         |    (k)ill    |  (r)ecycle   |   (m)ine     |  (s)cavange  |    (h)eal    |             |
31+--------------------------------------------------------------------------------------------------+
32| Context: <mouse-over context info>                                  | <<< Paused >>>             |


#endif
