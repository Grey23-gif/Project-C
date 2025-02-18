//khai bao nguyen mau ham
#ifndef DATATYPE_H
#define DATATYPE_H
#include "datatype.h"
#include <stdio.h>
#include <stdbool.h>

void getPassword();
void write_admin_data();
bool read_admin_data();
void showMenuLogin();
void registerAccount();
void login();

void showMenuLogin();
void showMenuStudent();
void showMenuMain();

void inputStudentInfo();
void addStudent();
void displayStudents();
void deleteStudent();
void editStudent();
void searchStudentByName();
void pressBToExit();
void sortsAZ();
void sortsZA();
int compareAZ();
int compareZA();
const char* getLastName();

void showMenuMain();
void addTeacher();
void displayTeachers();
void deleteTeacher();
void editTeacher();
void searchTeacherByName();
void sortsTeacherAZ();
void sortsTeacherZA();
int compareTeacherAZ();
int compareTeacherZA();



#endif
