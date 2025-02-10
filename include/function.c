#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "function.h"
#include "datatype.h"

void showMenuStudent() 
{
    printf("\n============================\n");
    printf("%19s\n", "STUDENT MENU");
    printf("============================\n");
    printf("[1]. Add a new student.\n");
    printf("[2]. Show all students.\n");
    printf("[3]. Edit a student.\n");
    printf("[4]. Delete a student.\n");
    printf("Enter your choice: ");
}

void addStudent() 
{
    FILE *file = fopen("student.txt", "a"); 
    if (file == NULL) {
        perror("Loi mo file");
        exit(1);
    }

    Student s;
    
    printf("Nhap ID: ");
    scanf("%d", &s.studentId);
    getchar();

    printf("Nhap ho va ten sinh vien: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Nhap tuoi: ");
    scanf("%d", &s.age);
    getchar();

    printf("Nhap email: ");
    fgets(s.email, sizeof(s.email), stdin);
    s.email[strcspn(s.email, "\n")] = '\0';

    printf("Nhap so dien thoai: ");
    fgets(s.phone, sizeof(s.phone), stdin);
    s.phone[strcspn(s.phone, "\n")] = '\0';

    // Ghi vào file van b?n
    fprintf(file, "%d,%s,%d,%s,%s\n", s.studentId, s.name, s.age, s.email, s.phone);

    printf("Them sinh vien thanh cong!\n");

    fclose(file);
}


void displayStudents()  
{
    FILE *file = fopen("student.txt", "r");
    if (file == NULL) 
    {
        printf("Khong co du lieu sinh vien!\n");
        return;
    }

    Student s;
    int hasData = 0;

    printf("\n|-----|--------------------|----------|--------------------|--------------------|");
    printf("\n|%-5s|%-20s|%-10s|%-20s|%-20s|", "ID", "Ho va Ten", "Tuoi", "Email", "SDT");
    printf("\n|-----|--------------------|----------|--------------------|--------------------|");

    while (fscanf(file, "%d,%49[^,],%d,%49[^,],%14[^\n]\n",
                  &s.studentId, s.name, &s.age, s.email, s.phone) == 5) 
    {
        hasData = 1;
        printf("\n|%-5d|%-20s|%-10d|%-20s|%-20s|",
               s.studentId, s.name, s.age, s.email, s.phone);
        printf("\n|-----|--------------------|----------|--------------------|--------------------|");
    }

    if (!hasData) 
    {
        printf("\nKhong co sinh vien nao trong danh sach.\n");
    }

    fclose(file);
}



