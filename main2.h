#include <ncurses.h>
#include <menu.h>
#include <panel.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define len 50
#define size 2
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

typedef struct _WIN_struct{
    int startx,starty;
    int HEIGHT, WIDTH;
    int flag;
}WIN;


void init_wparam(WIN *pwin, int ymax, int xmax); //setup window dimensions
WINDOW *create_wind(WIN *pwin, MENU *menu);
void win_border(WINDOW *win, MENU *menu, int flag);
void interest_calc_win(WINDOW *win_dow, int row, int col, PANEL *paninterest);
float compute(float P, float Rpct, int N);
float InputF(WINDOW *, char array[], PANEL *paninterest); 


void init_wparam(WIN *pwin, int ymax, int xmax) //if 1 calculator window; if 2 menu window
{
  pwin->HEIGHT=(pwin->flag == 1) ? ymax/2+5 : ymax/2;	
  pwin->WIDTH=(pwin->flag ==1) ? xmax*0.70-3 : xmax*0.30-3;
  pwin->startx=(pwin->flag ==1) ? xmax-pwin->WIDTH : xmax-COLS;
  pwin->starty=3;
  
}	


WINDOW *create_wind(WIN *pwin, MENU *menu)
{
  WINDOW *local_win;

  local_win = newwin(pwin->HEIGHT,pwin->WIDTH,pwin->starty,pwin->startx);
  	
  if(pwin->flag==1)
	win_border(local_win, menu, 1);
  else
    win_border(local_win, menu, 2);
   
  refresh();
  wrefresh(local_win);
 
  return local_win;
} 

void win_border(WINDOW *win, MENU *menu, int flag)
{
   int startx, starty, height, width, length;	
   char *winname;
   
   getbegyx(win, starty, startx);
   getmaxyx(win, height, width);
   mvwprintw(stdscr, LINES-3, 0, "starty %d, startx %d", starty, startx	);	
   mvwprintw(stdscr, LINES-2, 0, "height %d, width %d", height, width);			
	
   mvwaddch(win, 0,0, ACS_BULLET); //upper left side corner
   mvwhline(win, 0,1, ACS_HLINE, width-2); //line upper side 
   mvwaddch(win, 0,width-1, ACS_BULLET); //upper right side corner
   mvwvline(win, 1, 0, ACS_VLINE, height-2); //	left vertical line
   mvwaddch(win, height-1, 0, ACS_BULLET); //left bottom corner
   mvwhline(win, height-1, 1, ACS_HLINE, width-2); //lower side
   mvwvline(win, 1,width-1, ACS_VLINE, height-2);  //right side corner line
   mvwaddch(win, height-1, width-1, ACS_BULLET);
   
   winname = (char *)item_name(current_item(menu));
   length = strlen(winname);
   
   if(flag != 1)
		mvwprintw(win,0,(width - 4)/2, "MENU");
   else	
		mvwprintw(win,0,(width - length)/2, "%s", winname);    
   
   
}

void interest_calc_win(WINDOW *local_win, int row, int col, PANEL *paninterest)
{
  char charlocal_buff[len];
  float P,R=0.0,M;
  int N=0; 	
	
  mvwaddstr(local_win,row++,col,"Please dont leave a blank on the fields.");
  mvwaddstr(local_win,row++,col,"principal:5000,Rate;15.5%%No. of years: 5. monthly 125.77");
  row=4; col=2;
  mvwaddstr(local_win,row++,col,"Enter Principal:");
  P=InputF(local_win, charlocal_buff, paninterest );
  wrefresh(local_win); 
  mvwprintw(local_win,row++,col,"%.2f", P); 
  wrefresh(local_win); 
  mvwaddstr(local_win,row++,col,"Enter Rate:     ");
  wrefresh(local_win); 
  R=InputF(local_win,charlocal_buff, paninterest);
  mvwprintw(local_win,row++,col,"%.2f", R); 
  wrefresh(local_win); 
  mvwaddstr(local_win,row++,col,"Enter No. years:");
  wrefresh(local_win); 
  N=InputF(local_win,charlocal_buff, paninterest);
  mvwprintw(local_win,row++,col,"%d", N); 
  wrefresh(local_win); 
  //this is for formula.c 
  M=compute(P,R,N);
  wrefresh(local_win); 
  
  mvwprintw(local_win,row++,col,"Principal: %.2f", P);  
  mvwprintw(local_win,row++,col,"Rate(%%): %.2f", R);
  mvwprintw(local_win,row++,col,"Number of years: %d", N);
  mvwprintw(local_win,row++,2,"Monthly Payments: %.2f", M);
  wrefresh(local_win); 
}		
 
float InputF(WINDOW *win_c, char pchar[], PANEL *paninterest)
{
  int s=0; 
  int row=0,col=0;
  int point = 0; // 0 means not yet encountered; 1 means encountered once.
 
  float conv;
  
  getyx(win_c,row,col); //row 6 col 17

 
  while((pchar[s] = wgetch(win_c)) != '\n' && s < 50)
	{    
		if(isspace(pchar[s]))
			continue;			
			
	    if(!isdigit	(pchar[s]) && pchar[s] != 127 && pchar[s] != 46) //skip item and collect a character again	
			{continue;}
		else if(pchar[s] == 46 ) // encountered a point for the first time 
			{  	if(point == 0)
					point = 1;
				else
					continue;
			}
		
		
		if(pchar[s]==127) //127 is backspace or delete
			{   
				if(col<=17)
				{   col=17;
			    	move(row,col);
			    }
				else
				{ 	waddstr(win_c,"\b \b");
				    --col;
					}
				     
				
				if(s!=0)
					pchar[--s] ='\0';
				else
					pchar[s]='\0';	
			}
		else
			{ waddch(win_c,pchar[s++]);
			 col++;
		    }		
     }
     pchar[s]='\0';
     conv = atof(pchar);
     return conv;
 }   
