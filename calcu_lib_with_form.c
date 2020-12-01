
#include "main_with_form.h"


void description_list(WINDOW *, char *);

int main(void)
{
   /* variable field */
   PANEL_DATA *item_ptrs; //pointer to array but will turn to pointer to arrays via calloc
   WINDOW *window_menu;
   WINDOW *windows_calc[4];// 0-menu, 1-Interest, 2-Fahren-C
   
   
   PANEL *panel_menu;
   PANEL *panels_calc[4]; // panels for menu, my_windows[1](intererst_calc), my_windows[2](Fahren-C)
 
   ITEM **my_items;
   MENU *my_menu;
   int n_choices, i,c;
   int ymax, xmax;
   int row=0, col=1;
   char *choices[] = {
					    "INTEREST CAL",		 //0
					    "Fahren to Celc",    //1
					    "Celc to Fahren",    //2
					    "Exit",	             //3; exit doesnt have panel
					 };		
  				 	
   WIN winb, menub; //typedef struct data type
   
   ITEM *cur; // holds current item
   char *cur_highlight;
   

  //start of ncurses  
  initscr();
  refresh();
  raw();
  noecho();
  start_color();
  init_pair(1,COLOR_RED,COLOR_BLACK);
  init_pair(2,COLOR_GREEN,COLOR_BLACK);
  init_pair(3,COLOR_WHITE,COLOR_BLUE);
  
  //get size dimension of stdscr screen 
  getmaxyx(stdscr, ymax, xmax);   //ymax is 24, xmax is 80		
  
  //gives number of items
  n_choices = ARRAY_SIZE(choices); //gives me 4 
  
  //allocate storage for PANEL_DATA  pointer arrays
  item_ptrs = (PANEL_DATA *)calloc(n_choices, sizeof(PANEL_DATA)); 
  
  //my_items is array of pointers; set aside storage
  my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *)); 
  //part where literal strings associated with items from choices
  for(i=0; i<(n_choices-1); i++)
	{	my_items[i]=new_item(choices[i],choices[i]); 
        set_item_userptr(my_items[i], &item_ptrs[i]);
    }
    my_items[i]=new_item(choices[i],choices[i]);
    set_item_userptr(my_items[i],func_exit);   
    
  //create menu; associating items to menu
  my_menu = new_menu((ITEM **)my_items);		
  
  //set menu option not to show the description
  menu_opts_off(my_menu, O_SHOWDESC);

  //stdscr 
  attron(COLOR_PAIR(1) | A_BLINK);  
  mvaddstr(row++,col,"This program contains library of calculators"); //row becomes 1
  mvprintw(row,col,"Press F4 in menu to exit the program");
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
 wbkgd(stdscr,COLOR_PAIR(1));
 wbkgd(windows_calc[1],COLOR_PAIR(1));
  wbkgd(windows_calc[2],COLOR_PAIR(1));
  
 //attach panel for window_menu
 panel_menu = new_panel(window_menu); //stdscr -panel_menu(window_menu) - 
 
 //attach a panel to each calculator windows... 
 for(i=0;i<size;i++)  //0-interest,1-fahrenheit,2-choice3
	panels_calc[i] = new_panel(windows_calc[i]); //stdscr-0-1-2... 2 is on the top
	
  //set item_panel to designated calculator panels
  for(i=0;i<n_choices;i++)
	{ 
		if(i==0) 
		 {	item_ptrs[i].item_panel = panels_calc[i];  //panels
			item_ptrs[i].p = interest_calc_win; 
			item_ptrs[i].desc_flag = i;
		 }	
		 else if(i == 1)
		 {	item_ptrs[i].item_panel = panels_calc[i];	
			item_ptrs[i].p = fah_to_celsius;
			item_ptrs[i].desc_flag = i; 
		 }	
		 else
		 {
			item_ptrs[i].item_panel = panels_calc[i];	
			item_ptrs[i].p = celc_to_fahrenheit; 
			item_ptrs[i].desc_flag = i;
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
					cur = current_item(my_menu);			
					cur_highlight = (char *)item_name(cur);
					move(LINES-1,1);
					clrtobot();
					mvprintw(LINES-1,1, "%s %s", cur_highlight,item_desc(cur));

					break;
		case KEY_UP:
					menu_driver(my_menu, REQ_UP_ITEM);
					cur = current_item(my_menu);			
					cur_highlight = (char *)item_name(cur);
					move(LINES-1,1);
					clrtobot();
					mvprintw(LINES-1,1, "%s %s", cur_highlight, item_desc(cur));

					break;	
		case 10: //Enter	
			{	
   	 		
				WINDOW *old_win, *latest_win;					
				PANEL *panel_cur;
				void(*func_p)(WINDOW *, int x,int y); // for exit function
				//char *winname;
				int width, height, length;
								
				PANEL_DATA *ptrs;	

				
				ptrs=(PANEL_DATA *)malloc(sizeof(PANEL_DATA));
				ptrs = (PANEL_DATA *)item_userptr(cur); // give panel data(panels_calci[i]) to panel_cur


				//get the associated windows of the current highlighted panel
				length = strlen(cur_highlight);
				
				panel_cur = (PANEL *)ptrs->item_panel;
				old_win = panel_window(panel_cur);
				latest_win = create_wind(&winb, my_menu);
				wbkgd(latest_win,COLOR_PAIR(3));
				wrefresh(latest_win);
				refresh();
				//replace_panel(panel_cur, latest_win); //problem: malloc(): memory corruption in 2nd try of the calculator	
				delwin(old_win); 
				
				//for the window label - OK
				getmaxyx(latest_win, height, width);
				mvwprintw(latest_win,0,(width - length)/2, "%s", cur_highlight); 		
						
				//call the calculator functions that display the content in the windows
				func_p=ptrs->p;	
				row = 1;
				func_p(latest_win, row, col);	//row is 1		
				
		     	
		     	//top_panel(panel_menu);
				refresh();					
				update_panels();
				doupdate();
				break;

			}
     }	 
	 wrefresh(window_menu);
	 refresh();				
	 update_panels();
	 doupdate();
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
 
  char *item_desc(ITEM *current_item)
{ 
	
	PANEL_DATA *desc_ptrs;
	int flag;
	char *desc_text;
	
	desc_text = (char *)malloc(sizeof(char *));
	
	desc_ptrs = (PANEL_DATA *)malloc(sizeof(PANEL_DATA)); 
	desc_ptrs = (PANEL_DATA *)item_userptr(current_item);
	flag = desc_ptrs->desc_flag;
	
	if(flag == 0){
		sprintf(desc_text, "This computes interest of loan");
		return desc_text;
	}
	else if(flag == 1){
		sprintf(desc_text, "This computes Fahrenheit convert it to Celsius");
		return desc_text;	
	}	
	else if(flag == 2){
		sprintf(desc_text, "This computes Celsius and convert it to FAhrenheit");
		return desc_text;
	}
	else{
		sprintf(desc_text, "no flag is recognized");
		return desc_text;
	}	
}	
 


  	    
