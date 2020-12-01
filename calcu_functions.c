
#include "main_with_form.h"

void interest_calc_win(WINDOW *local_win, int row, int col) //row 0, col 1;
{
  char charlocal_buff[len];
  float P,R=0.0,M;
  int N=0; 	
  
  mvwaddstr(local_win,row++,col,"Input numbers only, decimal point is accepted"); //supposed to be 1
  mvwaddstr(local_win,row++,col,"principal:5000;Rate;15.5%%;Noofyears:5;monthly:125.77");
  row=4; col=2;
  mvwaddstr(local_win,row++,col,"Enter Principal:");
  P=InputF(local_win, charlocal_buff);
  wrefresh(local_win); 
  mvwprintw(local_win,row++,col,"%.2f", P); 
  wrefresh(local_win); 
  mvwaddstr(local_win,row++,col,"Enter Rate:     ");
  wrefresh(local_win); 
  R=InputF(local_win,charlocal_buff);
  mvwprintw(local_win,row++,col,"%.2f", R); 
  wrefresh(local_win); 
  mvwaddstr(local_win,row++,col,"Enter No. years:");
  wrefresh(local_win); 
  N=InputF(local_win,charlocal_buff);
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

void fah_to_celsius(WINDOW *local_win, int row, int col)
{
  char charlocal_buff[len];
  float fahr;
 
  getbegyx(local_win,row, col);
  //mvwprintw(local_win, row,col, "y is %d, x is %d", row,col); //row is 3 col is 27
  row = 2;
  col = 1;
  mvwprintw(local_win, row++,col, "Input fahrenheit to convert to celsus");
  mvwaddstr(local_win,row,col, "Enter Fahrenheit:"); //row is 3
  fahr=InputF(local_win, charlocal_buff); //input fahrenheit using function InputF then transfer to Celc
  row+=3; col+=20;
  mvwprintw(local_win,row,col,"Celsius Equivalent is: %.2f", ComputeFahtoCel(fahr));
  wrefresh(local_win); 
}		

void celc_to_fahrenheit(WINDOW *local_win, int row, int col)
{
  char charlocal_buff[len];
  float celc;
 
  
  getbegyx(local_win,row, col);

  row = 2;
  col = 1;
  mvwprintw(local_win, row++,col, "Input Celsius to convert to Fahrenheit");
  mvwaddstr(local_win,row,col, "Enter Celsius:"); //row is 3
  celc=InputF(local_win, charlocal_buff); //input fahrenheit using function InputF then transfer to Celc
  row+=3; col+=20;
  mvwprintw(local_win,row,col,"Fahrenheit Equivalent is: %.2f", ComputeCeltoFah(celc));
  wrefresh(local_win); 
}	
 
 /*InputF is not calculator function but use by other calculator functions for getting input as it 
	contains input checker for interestcal, fahtocel, celtofah. */ 
float InputF(WINDOW *win_c, char pchar[])
{
  int s=0; 
  int row=0,col=0;
  int point = 0; // 0 means not yet encountered; 1 means encountered once.
 
  float conv;
  
  getyx(win_c,row,col); //row 6 col 17

 
  while((pchar[s] = wgetch(win_c)) != '\n' && s < 50)
	{    
		if(isspace(pchar[s])) //skipped spaces
			continue;			
			
	    if(!isdigit(pchar[s]) && pchar[s] != 127 && pchar[s] != 46) //skip non integer and collect a character again	
			{continue;}
		else if(pchar[s] == 46 ) // encountered a point
			{  	if(point == 0)   //true, if encountered a point for the first time
					point = 1;   
				else
					continue;   //ignore a point(period) if already encountered once
			}
				
		if(pchar[s]==127) //127 is backspace or delete
			{   
				if(col<=17)
				{   col=17;
			    	move(row,col);
			    }
				else
				{ 	
					if(s!=0){
						waddstr(win_c,"\b \b"); //col 18 still being deleted
						--col;
					}	
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
 
 void func_exit(void)
 {
     exit(0);	 
 }	 

