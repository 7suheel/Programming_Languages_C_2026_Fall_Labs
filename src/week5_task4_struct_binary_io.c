/*
 * Name: Suheyl Baghban Sahebkar
 * Student ID: 251ADB192
 *
 * Week 5 - Bonus Task 4: Binary file version
 */
#include <stdio.h>
#include <string.h>

typedef struct Student {
    char name[50];
    int age;
    float gpa;
} Student;

/* Writes the whole struct to a binary file.
   Returns 0 on success, -1 on error. */
int save_student_binary(const Student *s, const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("Error opening binary file for writing");
        return -1;
    }

    if (fwrite(s, sizeof(Student), 1, fp) != 1) {
        fclose(fp);
        return -1;
    }

    if (fclose(fp) != 0) {
        return -1;
    }
    return 0;
}

/* Reads the whole struct back from a binary file.
   Returns 0 on success, -1 on error. */
int load_student_binary(const char *filename, Student *out) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Error opening binary file for reading");
        return -1;
    }

    if (fread(out, sizeof(Student), 1, fp) != 1) {
        fclose(fp);
        return -1;
    }

    fclose(fp);
    return 0;
}

/* Returns the file size in bytes, or -1 on error */
long file_size(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }

    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return -1;
    }

    long size = ftell(fp);
    fclose(fp);
    return size;
}

/* Saves the same record as text, so the two sizes can be compared */
static int save_student_text(const Student *s, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening text file for writing");
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

int main(void) {
    Student s;
    Student loaded;

    /* Zero everything first so no leftover memory is written to disk */
    memset(&s, 0, sizeof(s));
    memset(&loaded, 0, sizeof(loaded));
    strcpy(s.name, "Alice");
    s.age = 21;
    s.gpa = 3.75f;

    printf("Saving student in binary format...\n");
    if (save_student_binary(&s, "student.bin") != 0) {
        return 1;
    }

    printf("Loading student from binary file...\n");
    if (load_student_binary("student.bin", &loaded) != 0) {
        fprintf(stderr, "Failed to load student.\n");
        return 1;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);

    if (save_student_text(&s, "student.txt") != 0) {
        return 1;
    }

    printf("Text file size: %ld bytes\n", file_size("student.txt"));
    printf("Binary file size: %ld bytes\n", file_size("student.bin"));
    return 0;
}