#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "function.h"
#include "datatype.h"

int main() 
{
	int choice;
	do
	{
	showMenuStudent();
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			addStudent();
			break;
		case 2:
			displayStudents();
			break;
	}
	} while(choice!=5);
	return 0;
}
