#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "datatype.h"
#include "function.h"	


#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif


void showMenuTeacher() 	{
    system(CLEAR_SCREEN);
    printf("\n============================\n");
    printf("%19s\n", "Teacher MENU");
    printf("============================\n");
    printf("[1]. Add a new teacher.\n");
    printf("[2]. Show all teachers.\n");
    printf("[3]. Edit a teacher.\n");
    printf("[4]. Delete a teacher.\n");
    printf("[5]. Search a teacher.\n");
    printf("[6]. Sort teacher by name.\n");
    printf("[7]. Add class for teacher.\n");
    printf("[8]. Exit.\n");
    printf("Enter your choice: ");
}

void inputTeacherInfo(Teacher *t, FILE *file){
    int check;
    Teacher temp;
		
	// Nhap ten
        do
        {
        printf("Nhap ten: ");
        fgets(t->name, sizeof(t->name), stdin);
        t->name[strcspn(t->name, "\n")] = '\0'; 
        if (strlen(t->name) == 0) {
            printf("Khong de thong tin trong.\n");
        }

    	}while (strlen(t->name) == 0); 

        // Nhap tuoi
        do {
        check=1;
        char input[10];
        printf("Nhap tuoi: ");
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) {
            printf("Khong duoc de trong thong tin.\n");
            check=0;
            continue;
        }

        //chuyen chuoi thanh so nguyen
        if (sscanf(input, "%d", &t->age) != 1 || t->age <= 0) {
            printf("Vui long nhap lai.\n");
            check=0;
            continue;
        }

        break; 

    } while (!check);
		
		do
		{
		check=1;
       	//nhap email va ktra email
        printf("Nhap email: ");
        fgets(t->email, sizeof(t->email), stdin);
        t->email[strcspn(t->email, "\n")] = '\0';
        if (strlen(t->email) == 0 || strlen(t->email) <13 ||strstr(t->email,"@gmail.com") == NULL)
		{
            printf("Email khong hop le?!\n");
            check = 0;
        }
        if (strcmp(t->email + strlen(t->email) - 10, "@gmail.com") != 0) {
            printf("Email phai ket thuc bang @gmail.com .\n");
            check = 0;
            continue;
        }

        // Kiem tra email co trung khong
        rewind(file);
        while (fread(&temp, sizeof(Teacher), 1, file)) 
		{
            if (strcmp(temp.email, t->email) == 0) 
			{
                printf("Email da ton tai!\n");
                check = 0;
                break;
            }
        }
    	}while(!check);

        //Nhap so dien thoat va ktra co hop le k
        do
        {
        check=1;
        printf("Nhap so dien thoai: ");
        fgets(t->phone, sizeof(t->phone), stdin);
        t->phone[strcspn(t->phone, "\n")] = '\0';
        
        int length = strlen(t->phone);
        if (length !=10) {
            printf("So dien thoai khong hop le\n");
            check = 0;
        }
        int i;	
        for (i = 0; i < length; i++) {
        if (!isdigit(t->phone[i])) {
            printf("So dien thoai chi duoc chua cac chu so (0-9).\n");
            check=0;
            break;
        }
    	}
		
       //ktra xem SDT có trùng không
        rewind(file);
        while (fread(&temp, sizeof(Teacher), 1, file))
		 {
            if (strcmp(temp.phone, t->phone) == 0) 
			{
                printf("So dien thoat da ton tai!\n");
                check = 0;
                break;
            }
        }
        }while(!check);
	
}


void addTeacher() {
    system(CLEAR_SCREEN);
    FILE *file = fopen("teacher.bin", "ab+"); // Mo file doc va ghi
    if (!file) {
        perror("Error opening file");
        exit(1);
    }
    
    Teacher t;
    int check;
    Teacher temp;	
    do {
    char input[10]; //luu du lieu
    check = 1; // Gia su du lieu hop li

    // Nhap ID
    printf("Nhap ID: ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = 0;

    // Kiem tra xem nguoi dung co nhap ID
    if (strlen(input) == 0) {
        printf("Khong duoc de thong tin trong.\n");
        check = 0;
        continue;
    }

    //Chuyen input thanh so nguyen
    if (sscanf(input, "%d", &t.teacherId) != 1 || t.teacherId <= 0) 
	{
        printf("Vui long nhap lai ID.\n");
        check = 0;
        continue;
    }

    //Check xem ID co trung khong
    rewind(file); //dua con tro file ve dau
    while (fread(&temp, sizeof(Teacher), 1, file)) {
        if (temp.teacherId == t.teacherId) {
            printf("ID da ton tai.\n");
            check = 0;
            break;
        }
    }

	} while (!check);
	
	inputTeacherInfo(&t, file);
	
    // Luu thông tin hop le vào file
    fwrite(&t, sizeof(Teacher), 1, file);
    fclose(file);
    
    printf("Giao vien duoc them thanh cong.\n");
    pressBToExit();
}



void displayTeachers() {
    system(CLEAR_SCREEN);
    FILE *file = fopen("teacher.bin", "rb"); 
    if (file == NULL) {
        printf("Khong co du lieu giao vien!\n");
        pressBToExit();
        return;
    }

    Teacher t;
    int hasData = 0;

    printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");
    printf("\n|%-5s|%-20s|%-10s|%-40s|%-20s|", "ID", "Ho va Ten", "Tuoi", "Email", "SDT");
    printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");

    while (fread(&t, sizeof(Teacher), 1, file) == 1) { 
        hasData = 1;
        printf("\n|%-5d|%-20s|%-10d|%-40s|%-20s|",
               t.teacherId, t.name, t.age, t.email, t.phone);
        printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");
    }
    
    fclose(file);
    
    if (!hasData) {
        printf("\nKhong co giao vien nao trong danh sach.\n");
    }

    pressBToExit();
}


void editTeacher() {
	 system(CLEAR_SCREEN);
    FILE *file = fopen("teacher.bin", "rb");
    if (!file) {
        printf("Khong co du lieu giao vien!\n");
        return;
    }
    
    FILE *tempFile = fopen("temp.bin", "wb");
    if (!tempFile) {
        fclose(file);
        perror("Loi tao file moi");
        return;
    }

    int id, found = 0;
    printf("Nhap ID giao vien can sua: ");
    scanf("%d", &id);
    getchar();

    Teacher t;	
    while (fread(&t, sizeof(Teacher), 1, file)) {
        if (t.teacherId == id) {
            found = 1;
            inputTeacherInfo(&t,file);
        }
        fwrite(&t, sizeof(Teacher), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    remove("teacher.bin");
    rename("temp.bin", "teacher.bin");

    if (found) {
        printf("Da thay doi thong tinh giao vien!\n");
    } else {
        printf("ID giao vien khong tim thay!\n");
    }
    pressBToExit();
}

void deleteTeacher() {
	 system(CLEAR_SCREEN);
    FILE *file = fopen("teacher.bin", "rb");
    if (!file) {
        printf("Khong co du lieu giao vien!\n");
        return;
    }

    FILE *tempFile = fopen("temp.bin", "wb");
    if (!tempFile) {
        fclose(file);
        perror("Loi tao file moi");
        return;
    }

    int id, found = 0;
    printf("Nhap ID giao vien can xoa: ");
    scanf("%d", &id);
    getchar();

    Teacher t;
    while (fread(&t, sizeof(Teacher), 1, file)) {
        if (t.teacherId == id) {
            found = 1;
            printf("Da xoa ID %d thanh cong!\n", id);
            continue;
        }
        fwrite(&t, sizeof(Teacher), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    remove("teacher.bin");
    rename("temp.bin", "teacher.bin");

    if (!found) {
        printf("Khong tim thay ID giao vien!\n");
    }
    pressBToExit();
}

void searchTeacherByName() {
    system(CLEAR_SCREEN);
    FILE *file = fopen("teacher.bin", "rb");
	if (file == NULL) {
    printf("Loi khong the mo file!\n");
    pressBToExit();
    return;
}


    char searchName[50];
    printf("Nhap ten giao vien can tim: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';  

    Teacher t;
    int found = 0;

    printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");
    printf("\n|%-5s|%-20s|%-10s|%-40s|%-20s|", "ID", "Ho va Ten", "Tuoi", "Email", "SDT");
    printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");
    while (fread(&t, sizeof(Teacher), 1, file) == 1) {  
        if (strstr(t.name, searchName) != NULL) { 
            found = 1;
            printf("\n|%-5d|%-20s|%-10d|%-40s|%-20s|", t.teacherId, t.name, t.age, t.email, t.phone);
            printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");
        }
    }

    if (!found) {
        printf("\nKhông tìm thay giao vien nao co ten \"%s\"!\n", searchName);
    }

    fclose(file);
    pressBToExit();
}


	int compareTeacherAZ(Teacher arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (strcmp(getLastName(arr[j].name), getLastName(arr[j + 1].name)) > 0) {
                Teacher temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


	int compareTeacherZA(Teacher arr[], int n) {
  	int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (strcmp(getLastName(arr[j].name), getLastName(arr[j + 1].name)) < 0) {
                Teacher temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void sortsTeacherAZ() {
    system(CLEAR_SCREEN);
    FILE *file = fopen("teacher.bin", "rb");
    if (!file) {
        printf("Khomg co du lieu giao vien!\n");
        pressBToExit();
        return;
    }

    Teacher teachers[100]; // Khai báo mang
    int count = 0;

    while (fread(&teachers[count], sizeof(Teacher), 1, file)) {
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("Danh sach giao vien truong!\n");
        pressBToExit();
        return;
    }

    compareTeacherAZ(teachers,count);

    printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");
    printf("\n|%-5s|%-20s|%-10s|%-40s|%-20s|", "ID", "Ho va Ten", "Tuoi", "Email", "SDT");
    printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");
	int i=0;
    for ( i = 0; i < count; i++) {
        printf("\n|%-5d|%-20s|%-10d|%-40s|%-20s|",
               teachers[i].teacherId, teachers[i].name, teachers[i].age, teachers[i].email, teachers[i].phone);
        printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");
    }

    pressBToExit();
}



void sortsTeacherZA() {
    system(CLEAR_SCREEN);
    FILE *file = fopen("teacher.bin", "rb");
    if (!file) {
        printf("Khong co du lieu giao vien!\n");
        pressBToExit();
        return;
    }

    Teacher teachers[100]; 
    int count = 0;

    while (fread(&teachers[count], sizeof(Teacher), 1, file)) {
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("Danh sach giao vien truong\n");
        pressBToExit();
        return;
    }

   compareTeacherZA(teachers,count);

    printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");
    printf("\n|%-5s|%-20s|%-10s|%-40s|%-20s|", "ID", "Ho va Ten", "Tuoi", "Email", "SDT");
    printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");
	int i;
    for ( i = 0; i < count; i++) {
        printf("\n|%-5d|%-20s|%-10d|%-40s|%-20s|",
               teachers[i].teacherId, teachers[i].name, teachers[i].age, teachers[i].email, teachers[i].phone);
        printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");
    }

    pressBToExit();

}

