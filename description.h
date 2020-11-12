
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This header contains all the descriptions to each */

//passed the string descriptions back to main program 

char *description_list(char *label);


char *description_list(char *windowname)
{ 
	
	char label[20] = "INTEREST CAL";
	char *labelname;
	
	labelname = (char *)malloc(sizeof(char *));
	
	if(strcmp(label,windowname) == 0)
	{
		sprintf(labelname ,"This calculator computes interest of loan and produce monthly payments");
		return labelname;
	}
	else
	 {	sprintf(labelname,"labelname %s and windowname %s does not match", label, windowname);
		return labelname;
	  }	
	
	
	
}	
