#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
	int choice_2;
	int choice_3;
	do
	{
	showMenuMain();
	
	scanf("%d",&choice_2);
	getchar();
	system(CLEAR_SCREEN);
	switch (choice_2)
	{
		case 1:
		showMenuTeacher();
		scanf("%d",&choice);
		getchar();
		system(CLEAR_SCREEN);
		switch(choice_3)
		{
			case 1:
			break;
			case 2:
			break;
			case 3:
			break;
		}
		break;
		case 2:
		do
		{
			
			showMenuStudent();
			scanf("%d",&choice);
			getchar();
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
			
				case 6:
					{
			
						char choice_1;
						printf("[A].Sort names from a-z\n");
						printf("[B].Sort names from z-a\n");
						printf("Your choice: ");
						scanf("%c",&choice_1);
						getchar(); 
						if (choice_1 == 'A' || choice_1 == 'a') 
							{
                    			sortsAZ();
               				 } 
						else if (choice_1 == 'B' || choice_1 == 'b') 
							{
                   				 sortsZA();
                			} else {
                   		 printf("Sai lua chon!\n");
              				  }
								break;
						}
			}
		} while(choice!=7);
		break;
		case 3:
		break;
	}
	}while(choice_2!=4);

	return 0;
}
