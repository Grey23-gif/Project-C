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

void showMenuMain() 	{
    system(CLEAR_SCREEN);
    printf("\n\033[32m============================\n");
    printf("%17s\n", "MENU");
    printf("============================\n");
    printf("[1]. Teacher Menu.\n");
    printf("[2]. Student Menu.\n");
    printf("[3]. Classroom Menu.\n");
    printf("[4]. Exit.\n");
    printf("============================\n");
    printf("Enter your choice: ");
}

void showMenuStudent() 	{
    system(CLEAR_SCREEN);
    printf("\n============================\n");
    printf("%19s\n", "STUDENT MENU");
    printf("============================\n");
    printf("[1]. Add a new student.\n");
    printf("[2]. Show all students.\n");
    printf("[3]. Edit a student.\n");
    printf("[4]. Delete a student.\n");
    printf("[5]. Search a student.\n");
    printf("[6]. Sort students by name.\n");
    printf("[7]. Exit.\n");
    printf("============================\n");
    printf("Enter your choice: ");
}


void pressBToExit() {
    char ch;
    printf("\nPress 'B' to continue...");
    while ((ch = getchar()) != 'B' && ch != 'b' && ch != '\n');
}

void inputStudentInfo(Student *s, FILE *file){
    int check;
    Student temp;
		
	// Nhap ten
        do
        {
        printf("Nhap ten: ");
        fgets(s->name, sizeof(s->name), stdin);
        s->name[strcspn(s->name, "\n")] = '\0'; 
        if (strlen(s->name) == 0) {
            printf("Khong de thong tin trong.\n");
        }

    	}while (strlen(s->name) == 0); 

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
        if (sscanf(input, "%d", &s->age) != 1 || s->age <= 0) {
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
        fgets(s->email, sizeof(s->email), stdin);
        s->email[strcspn(s->email, "\n")] = '\0';
        if (strlen(s->email) == 0 || strlen(s->email) <13 ||strstr(s->email,"@gmail.com") == NULL)
		{
            printf("Email khong hop le?!\n");
            check = 0;
        }
        if (strcmp(s->email + strlen(s->email) - 10, "@gmail.com") != 0) {
            printf("Email phai ket thuc bang @gmail.com .\n");
            check = 0;
            continue;
        }

        // Kiem tra email co trung khong
        rewind(file);
        while (fread(&temp, sizeof(Student), 1, file)) 
		{
            if (strcmp(temp.email, s->email) == 0) 
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
        fgets(s->phone, sizeof(s->phone), stdin);
        s->phone[strcspn(s->phone, "\n")] = '\0';
        
        int length = strlen(s->phone);
        if (length !=10) {
            printf("So dien thoai khong hop le\n");
            check = 0;
        }
        int i;	
        for (i = 0; i < length; i++) {
        if (!isdigit(s->phone[i])) {
            printf("So dien thoai chi duoc chua cac chu so (0-9).\n");
            check=0;
            break;
        }
    	}
		
       //ktra xem SDT có trùng không
        rewind(file);
        while (fread(&temp, sizeof(Student), 1, file))
		 {
            if (strcmp(temp.phone, s->phone) == 0) 
			{
                printf("So dien thoat da ton tai!\n");
                check = 0;
                break;
            }
        }
        }while(!check);
	
}


void addStudent() {
    system(CLEAR_SCREEN);
    FILE *file = fopen("student.bin", "ab+"); // Mo file doc va ghi
    if (!file) {
        perror("Error opening file");
        exit(1);
    }
    
    Student s;
    int check;
    Student temp;	
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
    if (sscanf(input, "%d", &s.studentId) != 1 || s.studentId <= 0) 
	{
        printf("Vui long nhap lai ID.\n");
        check = 0;
        continue;
    }

    //Check xem ID co trung khong
    rewind(file); //dua con tro file ve dau
    while (fread(&temp, sizeof(Student), 1, file)) {
        if (temp.studentId == s.studentId) {
            printf("ID da ton tai.\n");
            check = 0;
            break;
        }
    }

	} while (!check);
	
	inputStudentInfo(&s, file);
	
    // Luu thông tin hop le vào file
    fwrite(&s, sizeof(Student), 1, file);
    fclose(file);
    
    printf("Sinh vien duoc them thanh cong.\n");
    pressBToExit();
}
        
        
void displayStudents() {
    system(CLEAR_SCREEN);
    FILE *file = fopen("student.bin", "rb"); 
    if (file == NULL) {
        printf("Khong co du lieu sinh vien!\n");
        pressBToExit();
        return;
    }

    Student s;
    int hasData = 0;

    printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");
    printf("\n|%-5s|%-20s|%-10s|%-40s|%-20s|", "ID", "Ho va Ten", "Tuoi", "Email", "SDT");
    printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");

    while (fread(&s, sizeof(Student), 1, file) == 1) { 
        hasData = 1;
        printf("\n|%-5d|%-20s|%-10d|%-40s|%-20s|",
               s.studentId, s.name, s.age, s.email, s.phone);
        printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");
    }
    
    fclose(file);
    
    if (!hasData) {
        printf("\nKhong co sinh vien nao trong danh sach.\n");
    }

    pressBToExit();
}


void editStudent() {
	 system(CLEAR_SCREEN);
    FILE *file = fopen("student.bin", "rb");
    if (!file) {
        printf("Khong co du lieu sinh vien!\n");
        return;
    }
    
    FILE *tempFile = fopen("temp.bin", "wb");
    if (!tempFile) {
        fclose(file);
        perror("Loi tao file moi");
        return;
    }

    int id, found = 0;
    printf("Nhap ID sinh vien can sua: ");
    scanf("%d", &id);
    getchar();

    Student s;
    while (fread(&s, sizeof(Student), 1, file)) {
        if (s.studentId == id) {
            found = 1;
            inputStudentInfo(&s, file);
        }
        fwrite(&s, sizeof(Student), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    remove("student.bin");
    rename("temp.bin", "student.bin");

    if (found) {
        printf("Da thay doi thong tinh sinh vien!\n");
    } else {
        printf("ID sinh vien khong tim thay!\n");
    }
    pressBToExit();
}

void deleteStudent() {
	 system(CLEAR_SCREEN);
    FILE *file = fopen("student.bin", "rb");
    if (!file) {
        printf("Khong co du lieu sinh vien!\n");
        return;
    }

    FILE *tempFile = fopen("temp.bin", "wb");
    if (!tempFile) {
        fclose(file);
        perror("Loi tao file moi");
        return;
    }

    int id, found = 0;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);
    getchar();

    Student s;
    while (fread(&s, sizeof(Student), 1, file)) {
        if (s.studentId == id) {
            found = 1;
            printf("Da xoa ID %d thanh cong!\n", id);
            continue;
        }
        fwrite(&s, sizeof(Student), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    remove("student.bin");
    rename("temp.bin", "student.bin");

    if (!found) {
        printf("Khong tim thay ID sinh vien!\n");
    }
    pressBToExit();
}

void searchStudentByName() {
    system(CLEAR_SCREEN);
    FILE *file = fopen("student.bin", "rb");
	if (file == NULL) {
    printf("Loi khong the mo file!\n");
    pressBToExit();
    return;
}


    char searchName[50];
    printf("Nhap ten sinh vien can tim: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';  

    Student s;
    int found = 0;

    printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");
    printf("\n|%-5s|%-20s|%-10s|%-40s|%-20s|", "ID", "Ho va Ten", "Tuoi", "Email", "SDT");
    printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");

    while (fread(&s, sizeof(Student), 1, file) == 1) {  
        if (strstr(s.name, searchName) != NULL) { 
            found = 1;
            printf("\n|%-5d|%-20s|%-10d|%-40s|%-20s|", s.studentId, s.name, s.age, s.email, s.phone);
            printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");
        }
    }

    if (!found) {
        printf("\nKhông tìm thay sinh vien nao co ten \"%s\"!\n", searchName);
    }

    fclose(file);
    pressBToExit();
}
	//Ham lay ten rieng
	const char* getLastName(const char *fullName) {
    const char *lastSpace = strrchr(fullName, ' '); //Tim khoang trang cuoi cung
    return (lastSpace) ? lastSpace + 1 : fullName;  //Neu co lay phan sau khong thi ca chuoi
	}	

	int compareAZ(Student arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (strcmp(getLastName(arr[j].name), getLastName(arr[j + 1].name)) > 0) {
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


	int compareZA(Student arr[], int n) {
  	int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (strcmp(getLastName(arr[j].name), getLastName(arr[j + 1].name)) < 0) {
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void sortsAZ() {
    system(CLEAR_SCREEN);
    FILE *file = fopen("student.bin", "rb");
    if (!file) {
        printf("Khomg co du lieu sinh vien!\n");
        pressBToExit();
        return;
    }

    Student students[100]; // Khai báo mang
    int count = 0;

    while (fread(&students[count], sizeof(Student), 1, file)) {
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("Danh sach sinh vien truong!\n");
        pressBToExit();
        return;
    }

    compareAZ(students,count);

    printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");
    printf("\n|%-5s|%-20s|%-10s|%-40s|%-20s|", "ID", "Ho va Ten", "Tuoi", "Email", "SDT");
    printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");
	int i=0;
    for ( i = 0; i < count; i++) {
        printf("\n|%-5d|%-20s|%-10d|%-40s|%-20s|",
               students[i].studentId, students[i].name, students[i].age, students[i].email, students[i].phone);
        printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");
    }

    pressBToExit();
}



void sortsZA() {
    system(CLEAR_SCREEN);
    FILE *file = fopen("student.bin", "rb");
    if (!file) {
        printf("Khong co du lieu sinh vien!\n");
        pressBToExit();
        return;
    }

    Student students[100]; 
    int count = 0;

    while (fread(&students[count], sizeof(Student), 1, file)) {
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("Danh sach sinh vien truong\n");
        pressBToExit();
        return;
    }

   compareZA(students,count);

    printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");
    printf("\n|%-5s|%-20s|%-10s|%-40s|%-20s|", "ID", "Ho va Ten", "Tuoi", "Email", "SDT");
    printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");
	int i;
    for ( i = 0; i < count; i++) {
        printf("\n|%-5d|%-20s|%-10d|%-40s|%-20s|",
               students[i].studentId, students[i].name, students[i].age, students[i].email, students[i].phone);
        printf("\n|-----|--------------------|----------|----------------------------------------|--------------------|");
    }

    pressBToExit();

}







