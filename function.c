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

void showMenuStudent() 
{
	system(CLEAR_SCREEN);
    printf("\n============================\n");
    printf("%19s\n", "STUDENT MENU");
    printf("============================\n");
    printf("[1]. Add a new student.\n");
    printf("[2]. Show all students.\n");
    printf("[3]. Edit a student.\n");
    printf("[4]. Delete a student.\n");
    printf("[5]. Search a student.\n");
    printf("[6]. Back to main Menu.\n");
    printf("[7]. Exit.\n");
    printf("Enter your choice: ");
}

void showMenuMain() 
{
	system(CLEAR_SCREEN);
    printf("\n============================\n");
    printf("%20s\n", "MENU");
    printf("============================\n");
    printf("[1]. Student Menu.\n");
    printf("[2]. Teacher Menu.\n");
    printf("[3]. Classroom Menu.\n");
    printf("[4]. Delete a student.\n");
    printf("[5]. Back to main Menu.\n");
    printf("[6]. Exit.\n");
    printf("Enter your choice: ");
}


int getMaxStudentId() {
    FILE *file = fopen("student.txt", "r"); 
    if (file == NULL) {
        return 0; 
    }

    Student s;
    int maxId = 0;

    while (fscanf(file, "%d,%49[^,],%d,%49[^,],%14[^\n]\n",
                  &s.studentId, s.name, &s.age, s.email, s.phone) == 5) {
        if (s.studentId > maxId) {
            maxId = s.studentId;
        }
    }

    fclose(file);
    return maxId;
}

void pressAnyKeyToExit() {
	 printf("\nNhan phim bat ky de quay lai");
	
    #ifdef _WIN32
        getch(); // Windows
    #else
        printf("\n");
        getchar(); // Linux/macOS: d?c ký t? Enter còn sót
        getchar(); // Ð?i ngu?i dùng nh?p phím b?t k?
    #endif
}

void addStudent() {
	system(CLEAR_SCREEN);
    int newId = getMaxStudentId() + 1;

    FILE *file = fopen("student.txt", "a"); 
    if (file == NULL) {
        perror("Loi mo file");
        exit(1);
    }

    Student s;
    s.studentId = newId;

    printf("ID : %d\n", s.studentId);
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

    
    fprintf(file, "%d,%s,%d,%s,%s\n", s.studentId, s.name, s.age, s.email, s.phone);
    
    printf("Them sinh vien thanh cong!\n");

    fclose(file);
    pressAnyKeyToExit();
}


void displayStudents()  
{
	system(CLEAR_SCREEN);
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
    pressAnyKeyToExit();
}

void editStudent() {
	system(CLEAR_SCREEN);
    FILE *file = fopen("student.txt", "r");
    if (file == NULL) {
        printf("Khong co du lieu sinh vien!\n");
        return;
    }

    int id;
    printf("Nhap ID sinh vien can sua: ");
    scanf("%d", &id);
    getchar();

    Student s;
    int found = 0;

    FILE *tempFile = fopen("temp.txt", "w"); 
    if (tempFile == NULL) {
        printf("Loi mo file tam thoi!\n");
        fclose(file);
        return;
    }

    while (fscanf(file, "%d,%49[^,],%d,%49[^,],%14[^\n]\n",
                  &s.studentId, s.name, &s.age, s.email, s.phone) == 5) {
        if (s.studentId == id) {
            found = 1;
            printf("Nhap ho va ten sinh vien moi: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = '\0';

            printf("Nhap tuoi moi: ");
            scanf("%d", &s.age);
            getchar();

            printf("Nhap email moi: ");
            fgets(s.email, sizeof(s.email), stdin);
            s.email[strcspn(s.email, "\n")] = '\0';

            printf("Nhap so dien thoai moi: ");
            fgets(s.phone, sizeof(s.phone), stdin);
            s.phone[strcspn(s.phone, "\n")] = '\0';
        }

    
        fprintf(tempFile, "%d,%s,%d,%s,%s\n", s.studentId, s.name, s.age, s.email, s.phone);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("student.txt");
        rename("temp.txt", "student.txt");
        printf("Sua thong tin thanh cong!\n"); 
    } else {
        printf("Khong tim thay sinh vien co ID %d!\n", id);
        remove("temp.txt"); 
    }
    pressAnyKeyToExit();
}


void deleteStudent() {
	system(CLEAR_SCREEN);
    FILE *file = fopen("student.txt", "r");
    if (file == NULL) {
        printf("Khong co du lieu sinh vien!\n");
        return;
    }

    int id;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);
    getchar();

    Student s;
    int found = 0;

    FILE *tempFile = fopen("temp.txt", "w"); // ?? M? file t?m
    if (tempFile == NULL) {
        printf("Loi mo file tam thoi!\n");
        fclose(file);
        return;
    }

    while (fscanf(file, "%d,%49[^,],%d,%49[^,],%14[^\n]\n",
                  &s.studentId, s.name, &s.age, s.email, s.phone) == 5) {
        if (s.studentId == id) {
            found = 1;
            printf("\n?? Ban co chac chan muon xoa sinh vien nay? (Y/N): ");
            char confirm;
            scanf(" %c", &confirm);
            getchar(); 

            if (confirm == 'y' || confirm == 'Y') {
                printf("Sinh vien co ID %d da duoc xoa thanh cong!\n", id);
                continue; 
            } else {
                printf("Huy xoa sinh vien.\n");
            }
        }

        fprintf(tempFile, "%d,%s,%d,%s,%s\n", s.studentId, s.name, s.age, s.email, s.phone);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("student.txt");
        rename("temp.txt", "student.txt");
    } else {
        printf("Khong tim thay sinh vien co ID %d!\n", id);
        remove("temp.txt"); 
    }
    pressAnyKeyToExit();
}

void searchStudentByName() 
{
	system(CLEAR_SCREEN);
    FILE *file = fopen("student.txt", "r");
    if (file == NULL) {
        printf("Khong co du lieu sinh vien!\n");
        return;
    }

    char searchName[50];
    printf("Nhap ten sinh vien can tim: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; 

    Student s;
    int found = 0;

    printf("\n|-----|--------------------|----------|--------------------|--------------------|");
    printf("\n|%-5s|%-20s|%-10s|%-20s|%-20s|", "ID", "Ho va Ten", "Tuoi", "Email", "SDT");
    printf("\n|-----|--------------------|----------|--------------------|--------------------|");

    while (fscanf(file, "%d,%49[^,],%d,%49[^,],%14[^\n]\n", 
                  &s.studentId, s.name, &s.age, s.email, s.phone) == 5) {
        if (strstr(s.name, searchName) != NULL) { 
            found = 1;
            printf("\n|%-5d|%-20s|%-10d|%-20s|%-20s|", s.studentId, s.name, s.age, s.email, s.phone);
            printf("\n|-----|--------------------|----------|--------------------|--------------------|");
        }
    }

    if (!found) {
        printf("\nKhong tim thay sinh vien nao voi ten chua \"%s\"!\n", searchName);
    }

    fclose(file);
    pressAnyKeyToExit();
}

void swap(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}


