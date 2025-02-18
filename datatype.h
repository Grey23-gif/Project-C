#ifndef DATATYPE_H
#define DATATYPE_H

#include <stdio.h>
#include <stdbool.h>

typedef struct  
{
	int studentId;
	char classroom[10];
	char name[25];
	int age;
	char email[40];
	char password[30];
	char phone[12];
} Student;

typedef struct  
{
	int teacherId;
	char classroomId[10];
	char name[25];
	int age;
	bool gender;
	char email[40];
	char phone[12];
	char password[30];
} Teacher;

typedef struct 
{
    char username[50];
    char password[50];
} AdminData;

#endif

