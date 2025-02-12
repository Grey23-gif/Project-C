#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "function.h"
#include "datatype.h"

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif 

int main() 
{
	int choice;
	do
	{
	showMenuStudent();
	scanf("%d",&choice);
	system(CLEAR_SCREEN);
	switch(choice)
	{
		case 1:
			addStudent();
			break;
		case 2:
			displayStudents();
			break;
		case 3:
			editStudent();
			break;
		case 4:
			deleteStudent();
			break;
		case 5:
			searchStudentByName();
			break;
			
		//case 6:
			//int choice_1;
			//printf("[A].Sort names from a-z");
			//printf("[B].Sort names from z-a");
			//scanf("%d",&choice_1);
			//switch(choice_1)
			//{
				//case 1:
				//break;
				//case 2:
				//break;
		//	}
			//break;
	}
	} while(choice!=7);
	return 0;
}
