#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "datatype.h"  // Ð?m b?o include datatype.h tru?c khi s? d?ng AdminData

#define FILE_NAME "admin.bin"
#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif


void showMenuLogin() {
	system(CLEAR_SCREEN);
    printf("\n\033[32m============================\n");
    printf("%17s\n", "MENU");
    printf("============================\n");
    printf("[1]. Login.\n");
    printf("[2]. Register.\n");
    printf("[3]. Exit\n");
    printf("============================\n");
    printf("Enter your choice: ");
}

void getPassword(char *password) {
    int i = 0;
    char ch;
    while ((ch = getch()) != 13) { 
        if (ch == 8 && i > 0) { printf("\b \b"); i--; }
        else if (i < 49) { password[i++] = ch; printf("*"); }
    }
    password[i] = '\0';
}


bool read_admin_data(AdminData *admin) {
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) return false;
    fread(admin, sizeof(AdminData), 1, file);
    fclose(file);
    return true;
}

void registerAccount() {
	system(CLEAR_SCREEN);
    AdminData newAdmin;

    // Nh?p thông tin tài kho?n
    printf("\nDang ky tai khoan moi\n");
    printf("Nhap tai khoan: "); 
    scanf("%s", newAdmin.username);
    printf("Nhap mat khau: "); 
    getPassword(newAdmin.password); 
    printf("\n");
	
    // Ghi vào file
    FILE *file = fopen(FILE_NAME, "wb");
    if (file) {
        fwrite(&newAdmin, sizeof(AdminData), 1, file);
        fclose(file);
        printf("Tao tai khoan thanh cong!\n");
    } else {
        printf("Loi mo file de ghi!\n");
    }
    getchar();
    pressBToExit();
}

void login() {
	system(CLEAR_SCREEN);
    AdminData admin;
    char user[50], pass[50];
    if (!read_admin_data(&admin)) {
        printf("Tai khoan khong ton tai!\n");
        return;
    }

    while (1) {
        printf("Tai khoan: "); scanf("%s", user);
        printf("Mat khau: "); getPassword(pass); printf("\n");

        if (!strcmp(user, admin.username) && !strcmp(pass, admin.password)) {
            printf("Dang nhap thanh cong!\n");
            break;
        }
        printf("Sai tai khoan hoac mat khau!\n");
    }
    getchar();
    pressBToExit();
}
#endif
