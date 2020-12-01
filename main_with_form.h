#include <ncurses.h>
#include <menu.h>
#include <panel.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define len 50
#define size 3
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

typedef struct _WIN_struct{
    int startx,starty;
    int HEIGHT, WIDTH;
    int flag;
    
}WIN;

typedef struct _PANEL_DATA{
  PANEL *item_panel; //panel for pointer to item. ex. is PANEL_DATA item_panel = panels_calc[i]
  void (*p)(WINDOW *, int x, int y); //pointer to function with arguments
  int desc_flag;

  	
}PANEL_DATA; // data type to connect with the items

//function prototype -start
void init_wparam(WIN *pwin, int ymax, int xmax); //setup window dimensions
WINDOW *create_wind(WIN *pwin, MENU *menu);
void win_border(WINDOW *win, MENU *menu, int flag);
void interest_calc_win(WINDOW *win_dow, int row, int col);
void fah_to_celsius(WINDOW *win_dow, int row, int col);
void celc_to_fahrenheit(WINDOW *local_win, int row, int col);
float compute(float P, float Rpct, int N);
float ComputeFahtoCel(float fahr);
float ComputeCeltoFah(float Celc);
float InputF(WINDOW *, char array[]); 
char *item_desc(ITEM *);
void func_exit(void);
//function prototype -end



