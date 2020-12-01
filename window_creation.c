#include "main_with_form.h"


void init_wparam(WIN *pwin, int ymax, int xmax) //if 1 calculator window; if 2 menu window
{	
		pwin->HEIGHT=(pwin->flag == 1) ? ymax/2+5 : ymax/2;	
		pwin->WIDTH=(pwin->flag ==1) ? xmax*0.70 : xmax*0.30-3;
		pwin->startx=(pwin->flag ==1) ? xmax-pwin->WIDTH : xmax-COLS;
		pwin->starty=3;
}	


WINDOW *create_wind(WIN *pwin, MENU *menu)
{
  WINDOW *local_win;

  local_win = newwin(pwin->HEIGHT,pwin->WIDTH,pwin->starty,pwin->startx);
  	
  if(pwin->flag==1)
	win_border(local_win, menu, 1);
  else if(pwin->flag==2)
    win_border(local_win, menu, 2);
  else
	box(local_win,0,0);
   
  refresh();
  wrefresh(local_win);
 
  return local_win;
} 

void win_border(WINDOW *win, MENU *menu, int flag)
{    
   int height, width;	
 
   getmaxyx(win, height, width);
	
   //draw a border around the windows -start	
   mvwaddch(win, 0,0, ACS_BULLET); //upper left side corner
   mvwhline(win, 0,1, ACS_HLINE, width-2); //line upper side 
   mvwaddch(win, 0,width-1, ACS_BULLET); //upper right side corner
   mvwvline(win, 1, 0, ACS_VLINE, height-2); //	left vertical line
   mvwaddch(win, height-1, 0, ACS_BULLET); //left bottom corner
   mvwhline(win, height-1, 1, ACS_HLINE, width-2); //lower side
   mvwvline(win, 1,width-1, ACS_VLINE, height-2);  //right side corner line
   mvwaddch(win, height-1, width-1, ACS_BULLET);
   //draw a border around the windows -end
   
   if(flag == 2)
	mvwprintw(win,0,(width - 4)/2, "MENU");
	
}
