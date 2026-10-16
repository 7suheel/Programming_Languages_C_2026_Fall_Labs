/*
 * Name: Suheyl Baghban Sahebkar
 * Student ID: 251ADB192
 *
 * Week 5 - Task 2: Save and load structured records
 */
#include <stdio.h>

typedef struct Student {
    char name[50];
    int age;
    float gpa;
} Student;

/* Saves one student as a single line "name age gpa".
   Returns 0 on success, -1 on error. */
int save_student(const Student *s, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return -1;
    }

    if (fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa) < 0) {
        fclose(fp);
        return -1;
    }

    if (fclose(fp) != 0) {
        return -1;
    }
    return 0;
}

/* Loads one student from the file into *out.
   Returns 0 on success, -1 on error. */
int load_student(const char *filename, Student *out) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return -1;
    }

    /* %49s stops the name from overflowing the 50-byte array */
    if (fscanf(fp, "%49s %d %f", out->name, &out->age, &out->gpa) != 3) {
        fclose(fp);
        return -1;
    }

    fclose(fp);
    return 0;
}

int main(void) {
    Student original = {"Alice", 21, 3.75f};
    Student loaded = {0};

    printf("Saving student to file...\n");
    if (save_student(&original, "student.txt") != 0) {
        return 1;
    }

    printf("Loading student from file...\n");
    if (load_student("student.txt", &loaded) != 0) {
        fprintf(stderr, "Failed to load student.\n");
        return 1;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);
    return 0;
}