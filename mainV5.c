#include "main2.h"




int main(void)
{
   /* variable field */
   WINDOW *win_c;
   WINDOW *menu_c;
   PANEL *my_panels[size]; // panels for win_c, menu_c
   //PANEL *stack_top;
   PANEL *paninterest; //myp_panels[1]
   ITEM **my_items;
   MENU *my_menu;
   int n_choices, i,c;
   int ymax, xmax;
   int row=0, col=1;
  // char *command;
   //command = malloc(sizeof(char *));
   char *choices[] = {
					    "Interest Cal",
					    "Fahren to Celc",
					    "Choices 3",
					    "Exit",	
					 };			
   
   WIN winb, menub; //typedef struct data type

  
  //start of ncurses  
  initscr();
  refresh();
  raw();
  noecho();
  start_color();
  init_pair(1,COLOR_RED,COLOR_BLACK);
  init_pair(2,COLOR_GREEN,COLOR_BLACK);
  init_pair(3,COLOR_BLUE,COLOR_WHITE);
  
  //get size dimension of stdscr screen 
  getmaxyx(stdscr, ymax, xmax);   //ymax is 24, xmax is 80		
  
  //create items
  n_choices = ARRAY_SIZE(choices); //gives me 4 
  my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *)); //my_items is array of pointers
  for(i=0; i<n_choices; i++)
		my_items[i]=new_item(choices[i],choices[i]); //part where literal strings associated with items from choices
  
  //create menu
  my_menu = new_menu((ITEM **)my_items);		
  
  //set menu option not to show the description
  menu_opts_off(my_menu, O_SHOWDESC);

  //stdscr 
  attron(COLOR_PAIR(1) | A_BLINK);  
  mvaddstr(row++,col,"This program contains library of calculators");
  mvprintw(row,col,"row is %d, col is %d", ymax, xmax);
  attroff(COLOR_PAIR(1) | A_BLINK);
  
  //for init_wparam
  winb.flag = 1; // calculator window STRUCT var
  menub.flag = 2; //  menu choices window  STRUCT var
  
  init_wparam(&winb,ymax,xmax); //setup dimensions of winb
  init_wparam(&menub,ymax,xmax); //setup dimensions of menub
  
 //create window  
 menu_c = create_wind(&menub, my_menu);  
 win_c = create_wind(&winb, my_menu);
 
 //set menu window  and sub window
 set_menu_win(my_menu, menu_c);
 set_menu_sub(my_menu, derwin(menu_c, 6, 20, 2, 1));

 
 //set menu mark
 set_menu_mark(my_menu, "*");
 
 set_menu_fore(my_menu, COLOR_PAIR(3)); //blue,white; hightlight text will be blue and background hightlight is white 
 set_menu_back(my_menu, COLOR_PAIR(2));  //green,black; background of window will be black and text and borders are green
 
 //post a menu
 post_menu(my_menu);
 wrefresh(menu_c);
 
 wbkgd(menu_c,COLOR_PAIR(2));
 
 //attach a panel to window
 my_panels[1] = new_panel(win_c);  //push 1: ordder: stdscr-win
 my_panels[0] = new_panel(menu_c); //push 0; order: stdscr-win-menu
 
 
 set_panel_userptr(my_panels[1], my_panels[0]);
 //set_panel_userptr(my_panels[2], my_panels[0]); for additional formula
 
 update_panels();
 doupdate();
 
 paninterest = my_panels[1]; //user_ptr is my_panels[0]
 
 keypad(menu_c, TRUE);
 while((c = wgetch(menu_c)) !=KEY_F(4))
 {
	 switch(c)
	 {
	    case KEY_DOWN:
					menu_driver(my_menu, REQ_DOWN_ITEM);
					break;
		case KEY_UP:
					menu_driver(my_menu, REQ_UP_ITEM);
					break;	
		case 10: //Enter	
			{	if(choices[0]==item_name(current_item(my_menu))) //Interest_Cal
				{	
					//wclrtoeol(win_c);
					win_c = create_wind(&winb, my_menu);
					show_panel(my_panels[1]);
					update_panels();
					wbkgd(win_c,COLOR_PAIR(1)); //background and font color of win_c
					//call function to fill up the interest calculator window
					row = 1; 
					//keypad(win_c, TRUE);
					interest_calc_win(win_c, row, col, paninterest); //row is 1, col is 1
					//hide_panel(my_panels[1]);
					update_panels();
					break;
				}	
				else if(choices[3]==item_name(current_item(my_menu)))
				{
					exit(0);
				  
				}
			}
     }	 
	 wrefresh(menu_c);
 }	 
 
  unpost_menu(my_menu);
  for(i=0; i<n_choices; i++)
		free_item(my_items[i]);
  free_menu(my_menu);		
 
 
  refresh(); 
  getch(); 
  endwin();
  
  
  return 0;
  
 }
 


  	    
