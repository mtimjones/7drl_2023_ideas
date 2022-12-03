#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

void menu( void )
{
   WINDOW *menu = newwin( 10, 10, 1, 1 );
   box( menu, 0, 0 );
   mvwprintw( menu, 1, 1, "Exit" );

   wgetch(menu);

   werase(menu);

   delwin( menu );
}

void menu2( void )
{
   WINDOW *menu = newwin( 10, 10, 1, 7 );
   box( menu, 0, 0 );
   mvwprintw( menu, 1, 1, "Exit" );

   wgetch(menu);

   werase(menu);

   delwin( menu );
}

int main( int argc, char *argv[] )
{
   initscr();
   noecho();
   curs_set(0);

   int ymax, xmax;

   getmaxyx( stdscr, ymax, xmax );

   WINDOW *win = newwin( 20, 30, 0, 0);
   box(win, 0, 0);

   mvwprintw( win, 0, 2, "File" );
   mvwprintw( win, 0, 7, "Edit" );
   mvwprintw( win, 0, 12, "Options" );

   wgetch(win);

   mvwprintw( win, 12, 5, "menu" );
   wrefresh(win);
   menu( );
   redrawwin(win);
   wrefresh(win);

   wgetch(win);

   mvwprintw( win, 12, 5, "menu2" );
   wrefresh(win);
   menu2();
   redrawwin(win);
   wrefresh(win);

   wgetch(win);

   endwin();

   return 0;
}
