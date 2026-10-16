/*
 * Name: Suheyl Baghban Sahebkar
 * Student ID: 251ADB192
 *
 * Week 5 - Task 1: Read and write text files
 */
#include <stdio.h>

int main(int argc, char *argv[]) {
    /* Use the file name from the command line if given, otherwise data.txt */
    const char *filename = (argc > 1) ? argv[1] : "data.txt";
    FILE *fp;
    char line[256];
    int count = 0;

    /* Open the file for writing (creates or overwrites it) */
    printf("Writing lines to %s...\n", filename);
    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return 1;
    }

    fprintf(fp, "Hello, file I/O in C!\n");
    fprintf(fp, "This is another line.\n");
    fclose(fp);

    /* Open the same file again, this time for reading */
    printf("Reading contents:\n");
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return 1;
    }

    /* Read and print the file line by line */
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
        count++;
    }
    fclose(fp);

    printf("Lines read: %d\n", count);
    return 0;
}