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
	char classroomId[10];
	char teacherId[10];
	char classroomName[10];
} Classroom;

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
	Classroom classrooms[5];
} Teacher;

#endif

