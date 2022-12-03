#include <ncurses.h>

int main( void )
{
  initscr();
  printw("Main window");

  WINDOW *subwindow = newwin(10, 20, 5, 15);

  refresh();

  getch();

  box(subwindow, 0, 0);
  mvwprintw(subwindow, 1, 1, "subwindow");

  refresh();
  wrefresh(subwindow);

  getch();
  delwin(subwindow);

  redrawwin(stdscr);
  refresh();
  getch();

  endwin();

  return 0;
}

