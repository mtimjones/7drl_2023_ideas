#include <ncurses.h>

int main( void )
{
  initscr();
  noecho();

  printw("Main window");

  WINDOW *subwindow = newwin(10, 20, 5, 15);

  refresh();

  getch();

  box(subwindow, 0, 0);
  mvwprintw(subwindow, 1, 1, "[Esc] Exit");
  mvwprintw(subwindow, 2, 2, "Welcome to xxx.");
  mvwprintw(subwindow, 3, 2, "Enjoy");

  refresh();
  wrefresh(subwindow);

  while ( getch() != 27 );
  delwin(subwindow);

  redrawwin(stdscr);
  refresh();
  getch();

  endwin();

  return 0;
}

