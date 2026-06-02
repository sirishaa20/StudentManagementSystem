# Student Management System in C

A beginner-friendly console application written in C that manages student records using **Structures**, **Arrays**, and **File Handling**.

---

## Features

| Feature          | Description                                      |
|------------------|--------------------------------------------------|
| Add Student      | Register a new student with ID, name, age, grade |
| Delete Student   | Remove a student by ID                           |
| Search Student   | Find and display a student's details by ID       |
| Update Student   | Edit a student's name, age, or grade             |
| Display All      | List every student in a formatted table          |
| Save & Exit      | Save all data to a file and quit                 |

---

## Concepts Covered

### 1. Structures
A `struct` groups related data under one name. Instead of using separate variables for each student, we bundle everything together:

```c
struct Student {
    int   id;
    char  name[50];
    int   age;
    float grade;
};
```

### 2. Arrays
We use an array of structures to store multiple students in memory:

```c
struct Student students[MAX_STUDENTS];  // holds up to 100 students
int count = 0;                          // tracks how many are stored
```

### 3. File Handling
Data is saved to `students.dat` so it persists between program runs.

| Function  | Mode | Purpose                    |
|-----------|------|----------------------------|
| `fopen`   | "wb" | Open file for writing      |
| `fwrite`  | —    | Write data to file         |
| `fopen`   | "rb" | Open file for reading      |
| `fread`   | —    | Read data from file        |
| `fclose`  | —    | Close the file             |

```c
// Saving
FILE *fp = fopen("students.dat", "wb");
fwrite(&count, sizeof(int), 1, fp);
fwrite(students, sizeof(struct Student), count, fp);
fclose(fp);

// Loading
FILE *fp = fopen("students.dat", "rb");
fread(&count, sizeof(int), 1, fp);
fread(students, sizeof(struct Student), count, fp);
fclose(fp);
```

---

## How to Compile and Run

```bash
gcc -o student_mgmt Main.c
./student_mgmt
```

---

## Program Flow

```
Start
  └── loadFromFile()         ← load saved data
        └── Main Menu Loop
              ├── 1. addStudent()
              ├── 2. deleteStudent()
              ├── 3. searchStudent()
              ├── 4. updateStudent()
              ├── 5. displayAll()
              └── 6. saveToFile() → Exit
```

---

## Sample Output

```
  STUDENT MANAGEMENT SYSTEM
  ----------------------------------------
  1. Add Student
  2. Delete Student
  3. Search Student
  4. Update Student
  5. Display All Students
  6. Save & Exit
  ----------------------------------------

--- All Students ---
  ----------------------------------------
  ID    Name                 Age   Grade
  ----------------------------------------
  101   Alice Smith          20    89.50
  102   Bob Jones            22    76.00
  ----------------------------------------
  Total Students: 2
```

---

## File Structure

```
Desktop/sai/
├── Main.c           ← Source code
├── students.dat     ← Auto-created data file
└── README_Student.md
```

---

## Key Functions Explained

| Function          | What it does                                           |
|-------------------|--------------------------------------------------------|
| `addStudent()`    | Reads input, checks for duplicate ID, adds to array   |
| `deleteStudent()` | Finds by ID, shifts array left to fill the gap         |
| `searchStudent()` | Linear search through array, prints details            |
| `updateStudent()` | Finds by ID, overwrites name/age/grade fields          |
| `displayAll()`    | Loops through array and prints formatted table         |
| `saveToFile()`    | Writes entire array to binary file                     |
| `loadFromFile()`  | Reads binary file into array at startup                |
