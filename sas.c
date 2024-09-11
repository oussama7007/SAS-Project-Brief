#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define MAX_NAME 100
#define MAX_ID_LENGTH 20
#define NUM_DEPARTMENTS 11

struct DateOfBirth {
    int day;
    int month;
    int year;
};

struct Student {
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME];
    char first_name[MAX_NAME];
    struct DateOfBirth dob;  // Date of birth
    char department[MAX_NAME];
    float gpa; // General note
};

struct Student students[MAX_STUDENTS];
int student_count = 0;

void edit_student() {
    char id[MAX_ID_LENGTH];
    printf("Enter student ID to edit: ");
    scanf(" %[^\n]", id);

    int found = -1;
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Student with ID %s not found.\n", id);
        return;
    }

    printf("Editing student %s:\n", id);

    char buffer[MAX_NAME];
    int temp_int;
    float temp_float;

    // Edit name
    printf("Enter new name (or press Enter to keep current: %s): ", students[found].name);
    scanf(" %[^\n]", buffer);
    if (strlen(buffer) > 0) {
        strcpy(students[found].name, buffer);
        for (int i = 0; students[found].name[i]; i++) {
            students[found].name[i] = tolower((unsigned char)students[found].name[i]);
        }
    }

    // Edit first name
    printf("Enter new first name (or press Enter to keep current: %s): ", students[found].first_name);
    scanf(" %[^\n]", buffer);
    if (strlen(buffer) > 0) {
        strcpy(students[found].first_name, buffer);
        for (int i = 0; students[found].first_name[i]; i++) {
            students[found].first_name[i] = tolower((unsigned char)students[found].first_name[i]);
        }
    }

    // Edit date of birth
    printf("Enter new date of birth (day month year) or press Enter to keep current: %02d/%02d/%04d:\n",
           students[found].dob.day, students[found].dob.month, students[found].dob.year);
    if (scanf("%d %d %d", &temp_int, &temp_int, &temp_int) == 3) {
        students[found].dob.day = temp_int;
        students[found].dob.month = temp_int;
        students[found].dob.year = temp_int;
    } else {
        // Clear invalid input
        while (getchar() != '\n');
    }

    // Edit department
    printf("Enter new department (or press Enter to keep current: %s): ", students[found].department);
    scanf(" %[^\n]", buffer);
    if (strlen(buffer) > 0) {
        strcpy(students[found].department, buffer);
        for (int i = 0; students[found].department[i]; i++) {
            students[found].department[i] = tolower((unsigned char)students[found].department[i]);
        }
    }

    // Edit GPA
    printf("Enter new GPA (or press Enter to keep current: %.2f): ", students[found].gpa);
    if (scanf("%f", &temp_float) == 1) {
        students[found].gpa = temp_float;
    } else {
        // Clear invalid input
        while (getchar() != '\n');
    }

    printf("Student information updated successfully.\n");
}

void delete_student() {
    char id[MAX_ID_LENGTH];
    printf("Enter student ID to delete: ");
    scanf(" %[^\n]", id);

    int found = -1;
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Student with ID %s not found.\n", id);
        return;
    }

    // Display student details and ask for confirmation
    printf("Student ID: %s\n", students[found].id);
    printf("Name: %s\n", students[found].name);
    printf("First Name: %s\n", students[found].first_name);
    printf("Date of Birth: %02d/%02d/%04d\n", students[found].dob.day, students[found].dob.month, students[found].dob.year);
    printf("Department: %s\n", students[found].department);
    printf("GPA (grade point average) ../20: %.2f\n", students[found].gpa);

    char confirmation;
    printf("\nAre you sure you want to delete this student? (y/n): ");
    scanf(" %c", &confirmation); // Ensure there's a space before %c to handle previous input

    if (confirmation == 'y' || confirmation == 'Y') {
        // Shift all elements to remove the student from the array
        for (int i = found; i < student_count - 1; i++) {
            students[i] = students[i + 1];
        }
        student_count--;

        printf("Student deleted successfully.\n");
    } else {
        printf("Deletion cancelled.\n");
    }
}

int id_exists(const char *id) {
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            return 1; // ID exists
        }
    }
    return 0; // ID does not exist
}

void calculate_overall_average() {
    if (student_count == 0) {
        printf("No students available to calculate.\n");
        return;
    }

    // Departments
    char *departments[NUM_DEPARTMENTS] = {
        "Science and Technology",
        "Engineering",
        "Medicine and Pharmacy",
        "Law",
        "Economics and Management",
        "Humanities and Social Sciences",
        "Education",
        "Literature",
        "Languages",
        "Arts and Design",
        "Agricultural Sciences"
    };

    float department_gpa_sum[NUM_DEPARTMENTS] = {0};
    int department_count[NUM_DEPARTMENTS] = {0};

    float total_gpa = 0.0;
    int total_students = 0;

    // Calculate sums and counts
    for (int i = 0; i < student_count; i++) {
        total_gpa += students[i].gpa;
        total_students++;

        for (int j = 0; j < NUM_DEPARTMENTS; j++) {
            if (strcmp(students[i].department, departments[j]) == 0) {
                department_gpa_sum[j] += students[i].gpa;
                department_count[j]++;
                break;
            }
        }
    }

    // Display overall average for the university
    if (total_students > 0) {
        float overall_avg = total_gpa / total_students;
        printf("Overall GPA for the entire university: %.2f\n", overall_avg);
    }

    // Display average GPA for each department
    for (int i = 0; i < NUM_DEPARTMENTS; i++) {
        if (department_count[i] > 0) {
            float department_avg = department_gpa_sum[i] / department_count[i];
            printf("Department: %s, Average GPA: %.2f\n", departments[i], department_avg);
        } else {
            printf("Department: %s, No students enrolled.\n", departments[i]);
        }
    }
}

void show_statistics() {
    if (student_count == 0) {
        printf("No students available to display statistics.\n");
        return;
    }

    char *departments[NUM_DEPARTMENTS] = {
        "Science and Technology", "Engineering", "Medicine and Pharmacy",
        "Law", "Economics and Management", "Humanities and Social Sciences",
        "Education", "Literature", "Languages", "Arts and Design",
        "Agricultural Sciences"
    };

    int department_counts[NUM_DEPARTMENTS] = {0};
    int department_successful_counts[NUM_DEPARTMENTS] = {0};
    int total_students = student_count;
    float threshold = 10.0;

    // Count number of students in each department and successful students
    for (int i = 0; i < student_count; i++) {
        for (int j = 0; j < NUM_DEPARTMENTS; j++) {
            if (strcmp(students[i].department, departments[j]) == 0) {
                department_counts[j]++;
                if (students[i].gpa >= threshold) {
                    department_successful_counts[j]++;
                }
                break;
            }
        }
    }

    // Print total number of students
    printf("Total number of students enrolled: %d\n", total_students);

    // Print number of students in each department and percentage of successful students
    for (int i = 0; i < NUM_DEPARTMENTS; i++) {
        if (department_counts[i] > 0) {
            float percentage_successful = (float)department_successful_counts[i] / department_counts[i] * 100;
            printf("Department: %s\n", departments[i]);
            printf("Number of students: %d\n", department_counts[i]);
            printf("Number of successful students (GPA >= %.2f): %d\n", threshold, department_successful_counts[i]);
            printf("Percentage of successful students: %.2f%%\n", percentage_successful);
        } else {
            printf("Department: %s has no students enrolled.\n", departments[i]);
        }
    }
}

void search_by_name() {
    char name[MAX_NAME];
    printf("Enter name to search: ");
    scanf(" %[^\n]", name);

    int found = 0;
    for (int i = 0; i < student_count; i++) {
        if (strstr(students[i].name, name) != NULL) {
            printf("Student ID: %s\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("First Name: %s\n", students[i].first_name);
            printf("Date of Birth: %02d/%02d/%04d\n", students[i].dob.day, students[i].dob.month, students[i].dob.year);
            printf("Department: %s\n", students[i].department);
            printf("GPA: %.2f\n", students[i].gpa);
            printf("\n");
            found = 1;
        }
    }
    if (!found) {
        printf("No students found with the name %s.\n", name);
    }
}

void search_by_department() {
    char *departments[NUM_DEPARTMENTS] = {
        "Science and Technology", "Engineering", "Medicine and Pharmacy",
        "Law", "Economics and Management", "Humanities and Social Sciences",
        "Education", "Literature", "Languages", "Arts and Design",
        "Agricultural Sciences"
    };

    printf("Available departments:\n");
    for (int i = 0; i < NUM_DEPARTMENTS; i++) {
        printf("%d. %s\n", i + 1, departments[i]);
    }

    int choice;
    printf("Enter department number to search: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > NUM_DEPARTMENTS) {
        printf("Invalid choice.\n");
        return;
    }

    char *selected_department = departments[choice - 1];
    int found = 0;
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].department, selected_department) == 0) {
            printf("Student ID: %s\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("First Name: %s\n", students[i].first_name);
            printf("Date of Birth: %02d/%02d/%04d\n", students[i].dob.day, students[i].dob.month, students[i].dob.year);
            printf("Department: %s\n", students[i].department);
            printf("GPA: %.2f\n", students[i].gpa);
            printf("\n");
            found = 1;
        }
    }
    if (!found) {
        printf("No students found in the department %s.\n", selected_department);
    }
}

void search() {
    int choice;
    printf("Search by:\n");
    printf("1. Name\n");
    printf("2. Department\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            search_by_name();
            break;
        case 2:
            search_by_department();
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}

void view_student() {
    char id[MAX_ID_LENGTH];
    printf("Enter student ID to view: ");
    scanf(" %[^\n]", id);

    int found = -1;
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Student with ID %s not found.\n", id);
        return;
    }

    printf("Student ID: %s\n", students[found].id);
    printf("Name: %s\n", students[found].name);
    printf("First Name: %s\n", students[found].first_name);
    printf("Date of Birth: %02d/%02d/%04d\n", students[found].dob.day, students[found].dob.month, students[found].dob.year);
    printf("Department: %s\n", students[found].department);
    printf("GPA: %.2f\n", students[found].gpa);
}
void add_student() 
{
    if (student_count >= MAX_STUDENTS) {
        printf("Student list is full. Cannot add more students.\n");
        return;
    }

    struct Student new_student;

    printf("Enter student ID: ");
    scanf(" %[^\n]", new_student.id);

    // Check if the ID already exists
    if (id_exists(new_student.id)) {
        printf("Student ID %s already exists. Please choose a different ID.\n", new_student.id);
        return;
    }

    printf("Enter student name: ");
    scanf(" %[^\n]", new_student.name);
    for (int i = 0; new_student.name[i]; i++) {
        new_student.name[i] = tolower((unsigned char)new_student.name[i]);
    }

    printf("Enter student first name: ");
    scanf(" %[^\n]", new_student.first_name);
    for (int i = 0; new_student.first_name[i]; i++) {
        new_student.first_name[i] = tolower((unsigned char)new_student.first_name[i]);
    }

    printf("Enter date of birth (day month year): ");
    scanf("%d %d %d", &new_student.dob.day, &new_student.dob.month, &new_student.dob.year);

    printf("Enter department: ");
    scanf(" %[^\n]", new_student.department);
    for (int i = 0; new_student.department[i]; i++) {
        new_student.department[i] = tolower((unsigned char)new_student.department[i]);
    }

    printf("Enter GPA (0.0 - 20.0): ");
    scanf("%f", &new_student.gpa);

    // Add new student to the list
    students[student_count] = new_student;
    student_count++;

    printf("Student added successfully.\n");
}
int main() {
    int choice;
    do {
        printf("Student Management System\n");
        printf("1. Add Student\n");
        printf("2. Edit Student\n");
        printf("3. Delete Student\n");
        printf("4. View Student\n");
        printf("5. Calculate Overall Average\n");
        printf("6. Show Statistics\n");
        printf("7. Search\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                edit_student();
                break;
            case 3:
                delete_student();
                break;
            case 4:
                view_student();
                break;
            case 5:
                calculate_overall_average();
                break;
            case 6:
                show_statistics();
                break;
            case 7:
                search();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}