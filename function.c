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
    printf("\n============================\n");
    printf("%17s\n", "MENU");
    printf("============================\n");
    printf("[1]. Teacher Menu.\n");
    printf("[2]. Student Menu.\n");
    printf("[3]. Classroom Menu.\n");
    printf("[4]. Exit.\n");
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
    printf("Enter your choice: ");
}

void showMenuTeacher() 	{
    system(CLEAR_SCREEN);
    printf("\n============================\n");
    printf("%19s\n", "Teacher MENU");
    printf("============================\n");
    printf("[1]. Add a new student.\n");
    printf("[2]. Show all students.\n");
    printf("[3]. Edit a student.\n");
    printf("[4]. Delete a student.\n");
    printf("[5]. Search a student.\n");
    printf("[6]. Sort students by name.\n");
    printf("[7]. Exit.\n");
    printf("Enter your choice: ");
}

void pressBToExit() {
    char ch;
    printf("\nPress 'B' to go back to the menu...");
    while ((ch = getchar()) != 'B' && ch != 'b' && ch != '\n');
}

void addStudent() {
    system(CLEAR_SCREEN);
    FILE *file = fopen("student.bin", "ab+"); // M? file d?c v� ghi
    if (!file) {
        perror("Error opening file");
        exit(1);
    }
    
    Student s;
    int check;
    Student temp;

    do {
        check = 1; //Vi du la du lieu hop le
        // Nhap ID
        printf("Nhap ID: ");
        if (scanf("%d", &s.studentId) != 1 || s.studentId <= 0) 
		{
            printf("ID khong hop le.\n");
            check = 0;
            while (getchar() != '\n');
            continue;
        }
        getchar(); // X�a bo no dem
        
        //ktra ID co lap k
        
        rewind(file); //Dua con tro file ve dau
        while (fread(&temp, sizeof(Student), 1, file)) 
		{
            if (temp.studentId == s.studentId) 
			{
                printf("ID da ton tai.\n");
                check = 0;
            }
		}
		}while(!check);
        // Nhap ten
        printf("Nhap ten: ");
        fgets(s.name, sizeof(s.name), stdin);
        s.name[strcspn(s.name, "\n")] = '\0'; 

        // Nhap tuoi
        do
		{
		check=1;
        printf("Nhap tuoi: ");
        if (scanf("%d", &s.age) != 1 || s.age <= 0) {
            printf("Tuoi khong hop le.\n");
            check = 0;
        }
        getchar();
    	}while(!check);
		
		do
		{
		check=1;
       //nhap email va ktra email
        printf("Nhap email: ");
        fgets(s.email, sizeof(s.email), stdin);
        s.email[strcspn(s.email, "\n")] = '\0';
        if (strlen(s.email) == 0 || strstr(s.email,"@gmail.com") == NULL) {
            printf("Email kh�ng hop le?!\n");
            check = 0;
        }

        // Kiem tra email co trung khong
        rewind(file);
        while (fread(&temp, sizeof(Student), 1, file)) 
		{
            if (strcmp(temp.email, s.email) == 0) 
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
        printf("Nhap so dien thoai: ");
        fgets(s.phone, sizeof(s.phone), stdin);
        s.phone[strcspn(s.phone, "\n")] = '\0';
        int length = strlen(s.phone);
        if (length < 9 || length > 11) {
            printf("So dien thoai khong hop le\n");
            check = 0;
        }
        int i;	
        for (i = 0; i < length; i++) {
        if (!isdigit(s.phone[i])) {
            printf("So dien thoai chi duoc chua cac chu so (0-9).\n");
            check=0;
            break;
        }
    	}
		
       //ktra xem S�T c� tr�ng kh�ng
        rewind(file);
        while (fread(&temp, sizeof(Student), 1, file))
		 {
            if (strcmp(temp.phone, s.phone) == 0) 
			{
                printf("So dien thoat da ton tai!\n");
                check = 0;
                break;
            }
        }
        }while(!check);

   
    // Luu th�ng tin hop le v�o file
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

    printf("\n|-----|--------------------|----------|--------------------|--------------------|");
    printf("\n|%-5s|%-20s|%-10s|%-20s|%-20s|", "ID", "Ho va Ten", "Tuoi", "Email", "SDT");
    printf("\n|-----|--------------------|----------|--------------------|--------------------|");

    while (fread(&s, sizeof(Student), 1, file) == 1) { 
        hasData = 1;
        printf("\n|%-5d|%-20s|%-10d|%-20s|%-20s|",
               s.studentId, s.name, s.age, s.email, s.phone);
        printf("\n|-----|--------------------|----------|--------------------|--------------------|");
    }
    
    fclose(file);
    
    if (!hasData) {
        printf("\nKh�ng c� sinh vi�n n�o trong danh s�ch.\n");
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
            printf("Nhap ten: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = '\0';

            printf("Nhap tuoi: ");
            scanf("%d", &s.age);
            getchar();

            printf("Nhap email: ");
            fgets(s.email, sizeof(s.email), stdin);
            s.email[strcspn(s.email, "\n")] = '\0';

            printf("Nhap SDT: ");
            fgets(s.phone, sizeof(s.phone), stdin);
            s.phone[strcspn(s.phone, "\n")] = '\0';
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

    printf("\n|-----|--------------------|----------|--------------------|--------------------|");
    printf("\n|%-5s|%-20s|%-10s|%-20s|%-20s|", "ID", "Ho va Ten", "Tuoi", "Email", "S�T");
    printf("\n|-----|--------------------|----------|--------------------|--------------------|");

    while (fread(&s, sizeof(Student), 1, file) == 1) {  
        if (strstr(s.name, searchName) != NULL) { 
            found = 1;
            printf("\n|%-5d|%-20s|%-10d|%-20s|%-20s|", s.studentId, s.name, s.age, s.email, s.phone);
            printf("\n|-----|--------------------|----------|--------------------|--------------------|");
        }
    }

    if (!found) {
        printf("\nKh�ng t�m thay sinh vien nao co ten \"%s\"!\n", searchName);
    }

    fclose(file);
    pressBToExit();
}

int compareAZ(const void *a, const void *b) {
    Student *s1 = (Student *)a;
    Student *s2 = (Student *)b;
    return strcmp(s1->name, s2->name);
}


int compareZA(const void *a, const void *b) {
    return compareAZ(b, a);
}


void sortsAZ() {
    system(CLEAR_SCREEN);
    FILE *file = fopen("student.bin", "rb");
    if (!file) {
        printf("Khomg co du lieu sinh vien!\n");
        pressBToExit();
        return;
    }

    Student students[100]; // Khai b�o m?ng
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

    qsort(students, count, sizeof(Student), compareAZ);

    printf("\n|-----|--------------------|----------|--------------------|--------------------|");
    printf("\n|%-5s|%-20s|%-10s|%-20s|%-20s|", "ID", "Ho va Ten", "Tuoi", "Email", "SDT");
    printf("\n|-----|--------------------|----------|--------------------|--------------------|");
	int i=0;
    for ( i = 0; i < count; i++) {
        printf("\n|%-5d|%-20s|%-10d|%-20s|%-20s|",
               students[i].studentId, students[i].name, students[i].age, students[i].email, students[i].phone);
        printf("\n|-----|--------------------|----------|--------------------|--------------------|");
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

    qsort(students, count, sizeof(Student), compareZA);

    printf("\n|-----|--------------------|----------|--------------------|--------------------|");
    printf("\n|%-5s|%-20s|%-10s|%-20s|%-20s|", "ID", "H? v� T�n", "Tu?i", "Email", "S�T");
    printf("\n|-----|--------------------|----------|--------------------|--------------------|");
	int i;
    for ( i = 0; i < count; i++) {
        printf("\n|%-5d|%-20s|%-10d|%-20s|%-20s|",
               students[i].studentId, students[i].name, students[i].age, students[i].email, students[i].phone);
        printf("\n|-----|--------------------|----------|--------------------|--------------------|");
    }

    pressBToExit();
}





void addTeacher() {
    system(CLEAR_SCREEN);
    FILE *file = fopen("teacher.bin", "ab+"); // Mo file doc v� ghi
    if (!file) {
        perror("Error opening file");
        exit(1);
    }
    
    Teacher t;
    int check;
    Teacher temp;

    do {
        check = 1; //Vi du la du lieu hop le
        // Nhap ID
        printf("Nhap ID: ");
        if (scanf("%d", &t.teacherId) != 1 || t.teacherId <= 0) 
		{
            printf("ID khong hop le.\n");
            check = 0;
            while (getchar() != '\n');
            continue;
        }
        getchar(); // X�a bo no dem
        
        //ktra ID co lap k
        
        rewind(file); //Dua con tro file ve dau
        while (fread(&temp, sizeof(Teacher), 1, file)) 
		{
            if (temp.teacherId == t.teacherId) 
			{
                printf("ID da ton tai.\n");
                check = 0;
            }
		}
		}while(!check);
        // Nhap ten
        printf("Nhap ten: ");
        fgets(t.name, sizeof(t.name), stdin);
        t.name[strcspn(t.name, "\n")] = '\0'; 

        // Nhap tuoi
        do
		{
		check=1;
        printf("Nhap tuoi: ");
        if (scanf("%d", &t.age) != 1 || t.age <= 0) {
            printf("Tuoi khong hop le.\n");
            check = 0;
        }
        getchar();
    	}while(!check);
		
		do
		{
		check=1;
       //nhap email va ktra email
        printf("Nhap email: ");
        fgets(t.email, sizeof(t.email), stdin);
        t.email[strcspn(t.email, "\n")] = '\0';
        if (strlen(t.email) == 0 || strstr(t.email,"@gmail.com") == NULL) {
            printf("Email kh�ng hop le?!\n");
            check = 0;
        }

        // Kiem tra email co trung khong
        rewind(file);
        while (fread(&temp, sizeof(Teacher), 1, file)) 
		{
            if (strcmp(temp.email, t.email) == 0) 
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
        printf("Nhap so dien thoai: ");
        fgets(t.phone, sizeof(t.phone), stdin);
        t.phone[strcspn(t.phone, "\n")] = '\0';
        int length = strlen(t.phone);
        if (length < 9 || length > 11) {
            printf("So dien thoai khong hop le\n");
            check = 0;
        }
        int i;	
        for (i = 0; i < length; i++) {
        if (!isdigit(t.phone[i])) {
            printf("So dien thoai chi duoc chua cac chu so (0-9).\n");
            check=0;
            break;
        }
    	}
		
       //ktra xem S�T c� tr�ng kh�ng
        rewind(file);
        while (fread(&temp, sizeof(Teacher), 1, file))
		 {
            if (strcmp(temp.phone, t.phone) == 0) 
			{
                printf("So dien thoat da ton tai!\n");
                check = 0;
                break;
            }
        }
        }while(!check);

   
    // Luu th�ng tin hop le v�o file
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

    printf("\n|-----|--------------------|----------|--------------------|--------------------|");
    printf("\n|%-5s|%-20s|%-10s|%-20s|%-20s|", "ID", "Ho va Ten", "Tuoi", "Email", "SDT");
    printf("\n|-----|--------------------|----------|--------------------|--------------------|");

    while (fread(&t, sizeof(Teacher), 1, file) == 1) { 
        hasData = 1;
        printf("\n|%-5d|%-20s|%-10d|%-20s|%-20s|",
               t.teacherId, t.name, t.age, t.email, t.phone);
        printf("\n|-----|--------------------|----------|--------------------|--------------------|");
    }
    
    fclose(file);
    
    if (!hasData) {
        printf("\nKh�ng c� giao vien n�o trong danh s�ch.\n");
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
            printf("Nhap ten: ");
            fgets(t.name, sizeof(t.name), stdin);
            t.name[strcspn(t.name, "\n")] = '\0';

            printf("Nhap tuoi: ");
            scanf("%d", &t.age);
            getchar();

            printf("Nhap email: ");
            fgets(t.email, sizeof(t.email), stdin);
            t.email[strcspn(t.email, "\n")] = '\0';

            printf("Nhap SDT: ");
            fgets(t.phone, sizeof(t.phone), stdin);
            t.phone[strcspn(t.phone, "\n")] = '\0';
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

    printf("\n|-----|--------------------|----------|--------------------|--------------------|");
    printf("\n|%-5s|%-20s|%-10s|%-20s|%-20s|", "ID", "Ho va Ten", "Tuoi", "Email", "S�T");
    printf("\n|-----|--------------------|----------|--------------------|--------------------|");

    while (fread(&t, sizeof(Teacher), 1, file) == 1) {  
        if (strstr(t.name, searchName) != NULL) { 
            found = 1;
            printf("\n|%-5d|%-20s|%-10d|%-20s|%-20s|", t.teacherId, t.name, t.age, t.email, t.phone);
            printf("\n|-----|--------------------|----------|--------------------|--------------------|");
        }
    }

    if (!found) {
        printf("\nKh�ng t�m thay giao vien nao co ten \"%s\"!\n", searchName);
    }

    fclose(file);
    pressBToExit();
}

int compareTeacherAZ(const void *a, const void *b) {
    Teacher *s1 = (Teacher *)a;
    Teacher *s2 = (Teacher *)b;
    return strcmp(s1->name, s2->name);
}


int compareTeacherZA(const void *a, const void *b) {
    return compareAZ(b, a);
}


void sortsTeacherAZ() {
    system(CLEAR_SCREEN);
    FILE *file = fopen("teacher.bin", "rb");
    if (!file) {
        printf("Khomg co du lieu giao vien!\n");
        pressBToExit();
        return;
    }

    Teacher teachers[100]; // Khai b�o m?ng
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

    qsort(teachers, count, sizeof(Teacher), compareAZ);

    printf("\n|-----|--------------------|----------|--------------------|--------------------|");
    printf("\n|%-5s|%-20s|%-10s|%-20s|%-20s|", "ID", "H? v� T�n", "Tu?i", "Email", "S�T");
    printf("\n|-----|--------------------|----------|--------------------|--------------------|");
	int i=0;
    for ( i = 0; i < count; i++) {
        printf("\n|%-5d|%-20s|%-10d|%-20s|%-20s|",
               teachers[i].teacherId, teachers[i].name, teachers[i].age, teachers[i].email, teachers[i].phone);
        printf("\n|-----|--------------------|----------|--------------------|--------------------|");
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

    qsort(teachers, count, sizeof(Teacher), compareZA);

    printf("\n|-----|--------------------|----------|--------------------|--------------------|");
    printf("\n|%-5s|%-20s|%-10s|%-20s|%-20s|", "ID", "Ho va Ten", "Tuoi", "Email", "S�T");
    printf("\n|-----|--------------------|----------|--------------------|--------------------|");
	int i;
    for ( i = 0; i < count; i++) {
        printf("\n|%-5d|%-20s|%-10d|%-20s|%-20s|",
               teachers[i].teacherId, teachers[i].name, teachers[i].age, teachers[i].email, teachers[i].phone);
        printf("\n|-----|--------------------|----------|--------------------|--------------------|");
    }

    pressBToExit();
}


