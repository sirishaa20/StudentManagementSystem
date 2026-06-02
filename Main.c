/*
 * =====================================================
 *          STUDENT MANAGEMENT SYSTEM
 *          Concepts: Structures, Arrays, File Handling
 * =====================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -------------------------------------------------------
 * STRUCTURE DEFINITION
 * A structure groups related data under one name.
 * Here, each student has an ID, name, age, and grade.
 * ------------------------------------------------------- */
struct Student {
    int   id;
    char  name[50];
    int   age;
    float grade;
};

/* Maximum number of students we can hold in memory */
#define MAX_STUDENTS 100

/* The filename where we save student data */
#define FILE_NAME "students.dat"

/* -------------------------------------------------------
 * GLOBAL ARRAY
 * We store all students in this array.
 * 'count' keeps track of how many students are stored.
 * ------------------------------------------------------- */
struct Student students[MAX_STUDENTS];
int count = 0;

/* -------------------------------------------------------
 * FUNCTION DECLARATIONS (prototypes)
 * We declare functions before main() so C knows about them.
 * ------------------------------------------------------- */
void loadFromFile();
void saveToFile();
void addStudent();
void deleteStudent();
void searchStudent();
void updateStudent();
void displayAll();
void printMenu();
void printLine();

/* -------------------------------------------------------
 * MAIN FUNCTION — program starts here
 * ------------------------------------------------------- */
int main() {
    int choice;

    printf("\n  Welcome to Student Management System\n");

    /* Load any existing students from the file at startup */
    loadFromFile();

    /* Keep showing the menu until the user chooses to exit */
    while (1) {
        printMenu();
        printf("  Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent();    break;
            case 2: deleteStudent(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: displayAll();    break;
            case 6:
                saveToFile();
                printf("\n  Data saved. Goodbye!\n\n");
                return 0;
            default:
                printf("\n  Invalid choice. Please enter 1-6.\n");
        }
    }
}

/* -------------------------------------------------------
 * PRINT MENU
 * Shows the list of options to the user.
 * ------------------------------------------------------- */
void printMenu() {
    printLine();
    printf("  STUDENT MANAGEMENT SYSTEM\n");
    printLine();
    printf("  1. Add Student\n");
    printf("  2. Delete Student\n");
    printf("  3. Search Student\n");
    printf("  4. Update Student\n");
    printf("  5. Display All Students\n");
    printf("  6. Save & Exit\n");
    printLine();
}

/* -------------------------------------------------------
 * PRINT LINE — just a visual separator
 * ------------------------------------------------------- */
void printLine() {
    printf("  ----------------------------------------\n");
}

/* -------------------------------------------------------
 * ADD STUDENT
 * Takes input from user and adds a new student to the array.
 * ------------------------------------------------------- */
void addStudent() {
    if (count >= MAX_STUDENTS) {
        printf("\n  Error: Student list is full!\n");
        return;
    }

    struct Student s;

    printf("\n--- Add New Student ---\n");
    printf("  Enter ID    : ");
    scanf("%d", &s.id);

    /* Check if ID already exists */
    for (int i = 0; i < count; i++) {
        if (students[i].id == s.id) {
            printf("\n  Error: A student with ID %d already exists.\n", s.id);
            return;
        }
    }

    printf("  Enter Name  : ");
    scanf(" %[^\n]", s.name);   /* reads full name including spaces */

    printf("  Enter Age   : ");
    scanf("%d", &s.age);

    printf("  Enter Grade : ");
    scanf("%f", &s.grade);

    /* Add the new student to the array */
    students[count] = s;
    count++;

    printf("\n  Student added successfully!\n");
}

/* -------------------------------------------------------
 * DISPLAY ALL STUDENTS
 * Loops through the array and prints every student.
 * ------------------------------------------------------- */
void displayAll() {
    printf("\n--- All Students ---\n");

    if (count == 0) {
        printf("  No students found.\n");
        return;
    }

    printLine();
    printf("  %-5s %-20s %-5s %-6s\n", "ID", "Name", "Age", "Grade");
    printLine();

    for (int i = 0; i < count; i++) {
        printf("  %-5d %-20s %-5d %.2f\n",
               students[i].id,
               students[i].name,
               students[i].age,
               students[i].grade);
    }

    printLine();
    printf("  Total Students: %d\n", count);
}

/* -------------------------------------------------------
 * SEARCH STUDENT
 * Asks for an ID, then searches the array for a match.
 * ------------------------------------------------------- */
void searchStudent() {
    int id;
    printf("\n--- Search Student ---\n");
    printf("  Enter Student ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("\n  Student Found!\n");
            printLine();
            printf("  ID    : %d\n",   students[i].id);
            printf("  Name  : %s\n",   students[i].name);
            printf("  Age   : %d\n",   students[i].age);
            printf("  Grade : %.2f\n", students[i].grade);
            printLine();
            return;
        }
    }

    printf("\n  Student with ID %d not found.\n", id);
}

/* -------------------------------------------------------
 * DELETE STUDENT
 * Finds the student by ID and removes them from the array
 * by shifting all elements after it one position left.
 * ------------------------------------------------------- */
void deleteStudent() {
    int id;
    printf("\n--- Delete Student ---\n");
    printf("  Enter Student ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            /* Shift elements left to fill the gap */
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }
            count--;
            printf("\n  Student with ID %d deleted successfully.\n", id);
            return;
        }
    }

    printf("\n  Student with ID %d not found.\n", id);
}

/* -------------------------------------------------------
 * UPDATE STUDENT
 * Finds the student by ID and allows the user to change
 * their name, age, and grade.
 * ------------------------------------------------------- */
void updateStudent() {
    int id;
    printf("\n--- Update Student ---\n");
    printf("  Enter Student ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("\n  Student found: %s\n", students[i].name);
            printf("  Enter new Name  : ");
            scanf(" %[^\n]", students[i].name);

            printf("  Enter new Age   : ");
            scanf("%d", &students[i].age);

            printf("  Enter new Grade : ");
            scanf("%f", &students[i].grade);

            printf("\n  Student updated successfully!\n");
            return;
        }
    }

    printf("\n  Student with ID %d not found.\n", id);
}

/* -------------------------------------------------------
 * SAVE TO FILE
 * Writes all student records into a binary file.
 * FILE HANDLING: fopen, fwrite, fclose
 * ------------------------------------------------------- */
void saveToFile() {
    FILE *fp = fopen(FILE_NAME, "wb");  /* "wb" = write binary */

    if (fp == NULL) {
        printf("\n  Error: Could not open file for writing.\n");
        return;
    }

    /* Write the count first, then write each student */
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(students, sizeof(struct Student), count, fp);

    fclose(fp);
    printf("\n  Data saved to '%s'.\n", FILE_NAME);
}

/* -------------------------------------------------------
 * LOAD FROM FILE
 * Reads student records from the binary file at startup.
 * FILE HANDLING: fopen, fread, fclose
 * ------------------------------------------------------- */
void loadFromFile() {
    FILE *fp = fopen(FILE_NAME, "rb");  /* "rb" = read binary */

    if (fp == NULL) {
        /* File doesn't exist yet — that's okay on first run */
        printf("\n  No existing data found. Starting fresh.\n");
        return;
    }

    fread(&count, sizeof(int), 1, fp);
    fread(students, sizeof(struct Student), count, fp);

    fclose(fp);
    printf("\n  Loaded %d student(s) from file.\n", count);
}
