//import ham. khai bao struct
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
	char phone[10];
}Student;
 
struct classroom
{
	char classroomId[10];
	char teacherId[10];
	char classroomName[10];
	
};

struct Teacher
{
	char teacherId[10];
	char classroomId[10];
	char name[25];
	int age;
	bool gender;
	char email[40];
	char phone[10];
	char password[30];
	struct classroom classrooms[];
};

