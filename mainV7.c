#include "main3.h"
#include "description.h"




int main(void)
{
   /* variable field */
   PANEL_DATA *item_ptrs;
   WINDOW *window_menu;
   WINDOW *windows_calc[4];// 0-menu, 1-Interest, 2-Fahren-C
   PANEL *panel_menu;
   PANEL *panels_calc[4]; // panels for menu, my_windows[1](intererst_calc), my_windows[2](Fahren-C)
   //PANEL *stack_top;
   ITEM **my_items;
   MENU *my_menu;
   int n_choices, i,c;
   int ymax, xmax;
   int row=0, col=1;
   char *choices[] = {
					    "INTEREST CAL",		 //0
					    "Fahren to Celc",    //1
					    "Celc to Fahren",         //2
					    "Exit",	             //3; exit doesnt have panel
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

  
  //gives number of items
  n_choices = ARRAY_SIZE(choices); //gives me 4 
  
  //allocate storage for PANEL_DATA  pointer arrays
  item_ptrs = (PANEL_DATA *)calloc(n_choices, sizeof(PANEL_DATA)); 
  
  //my_items is array of pointers; set aside storage
  my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *)); 
  //part where literal strings associated with items from choices
  for(i=0; i<n_choices; i++)
	{	my_items[i]=new_item(choices[i],choices[i]); 
        set_item_userptr(my_items[i], &item_ptrs[i]);
    }
    set_item_userptr(my_items[n_choices-1],func_exit);   
    
  //create menu
  my_menu = new_menu((ITEM **)my_items);		
  
  //set menu option not to show the description
  menu_opts_off(my_menu, O_SHOWDESC);

  //stdscr 
  attron(COLOR_PAIR(1) | A_BLINK);  
  mvaddstr(row++,col,"This program contains library of calculators"); //row becomes 1
  mvprintw(row,col,"row is %d, col is %d", ymax, xmax);
  attroff(COLOR_PAIR(1) | A_BLINK);
  
  //for init_wparam
  winb.flag = 1; // calculator window STRUCT var
  menub.flag = 2; //  menu choices window  STRUCT var
  
  //setup dimensions
  init_wparam(&winb,ymax,xmax); //setup dimensions of winb
  init_wparam(&menub,ymax,xmax); //setup dimensions of menub
  
 //create window for menu  
 window_menu = create_wind(&menub, my_menu);
 //create windows for the calculators  
 for(i=0;i<size;i++)
	windows_calc[i] = create_wind(&winb, my_menu);

//background and font color of windows_calc[0](interest)	
 wbkgd(windows_calc[0],COLOR_PAIR(1)); 
 //call function to fill up the interest calculator window

 //set menu window  and sub window
 set_menu_win(my_menu, window_menu);
 set_menu_sub(my_menu, derwin(window_menu, 6, 20, 2, 1));

 //set menu mark
 set_menu_mark(my_menu, "*");
 
 //window colors
 set_menu_fore(my_menu, COLOR_PAIR(3)); //blue,white; hightlight text will be blue and background hightlight is white 
 set_menu_back(my_menu, COLOR_PAIR(2));  //green,black; background of window will be black and text and borders are green
 
 //post a menu
 post_menu(my_menu);
 wrefresh(window_menu);
 
 //set color background foreground for window menu
 wbkgd(window_menu,COLOR_PAIR(2));
 
 //attach panel for window_menu
 panel_menu = new_panel(window_menu);
 
 //attach a panel to each calculator windows... 
 for(i=0;i<size;i++)  //0-interest,1-fahrenheit,2-choice3
	panels_calc[i] = new_panel(windows_calc[i]); //stdscr-0-1-2... 2 is on the top
	
  //set item_panel to designated calculator panels
  for(i=0;i<n_choices;i++)
	{ 
		if(i==0) 
		 {	item_ptrs[i].item_panel = panels_calc[i];  //panels
			item_ptrs[i].p = interest_calc_win; 
		 }	
		 else if(i == 1)
		 {	item_ptrs[i].item_panel = panels_calc[i];	
			item_ptrs[i].p = fah_to_celcius; 
		 }	
		 else
		 {
			item_ptrs[i].item_panel = panels_calc[i];	
			item_ptrs[i].p = fah_to_celcius; 
		 }	 
	}		
	
 //make the panel_menu is in the top	
 top_panel(panel_menu);
 update_panels();
 doupdate();
 	

 keypad(window_menu, TRUE);
  while((c = wgetch(window_menu)) !=KEY_F(4))
  //while((c = 10) !=KEY_F(4))
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
			{	
	            PANEL_DATA *ptrs;		
	            WINDOW *win;	
				ITEM *cur; // holds current item
				//PANEL *panel_cur;
				void(*func_p)(WINDOW *, int x,int y); // for exit function
				char *winname;
				char *win_descrip;
				int length;
				int height, width;
				

				cur = current_item(my_menu);			
				winname = (char *)item_name(cur);
	            length = strlen(winname);
				  

				ptrs=(PANEL_DATA *)malloc(sizeof(PANEL_DATA));
				ptrs = (PANEL_DATA *)item_userptr(cur); // give panel data(panels_calci[i]) to panel_cur
				top_panel(ptrs->item_panel);
				
				//diplay the description of the calculator at the bottom of the screen
				win_descrip = description_list(winname);
				mvwprintw(stdscr, LINES-2, 0, "%s",win_descrip);	
				wrefresh(stdscr);

				
				//get the associated windows of the current highlighted panel
				win = panel_window(ptrs->item_panel);
				getmaxyx(win, height, width);
				mvwprintw(win,0,(width - length)/2, "%s", winname); 
				wrefresh(win); 
				doupdate();
						
				//call the calculator functions that display the content in the windows
				func_p=ptrs->p;	
				row = 1;
				func_p(win, row, col);	//row is 1		

				
				update_panels();
				doupdate();
				break;

			}
     }	 
	 wrefresh(window_menu);
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
 


  	    
