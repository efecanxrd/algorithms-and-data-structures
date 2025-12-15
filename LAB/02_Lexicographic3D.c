#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

int main(void) {
    int r, c;
    FILE *fptr = fopen("file1.txt", "r");
    if (fptr == NULL) {
        perror("File open failed");
        exit(EXIT_FAILURE);
    }

    fscanf(fptr, "%d %d", &r, &c);

    // Allocate one contiguous block: r * c strings of length MAX
    char (*arr)[c][MAX] = malloc(r * c * MAX * sizeof(char));
    if (arr == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    // Read strings
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            fscanf(fptr, "%19s", arr[i][j]);
        }
    }
    fclose(fptr);

    // Flatten into a single array for sorting
    int total = r * c;
    char **flat = malloc(total * sizeof(char *));
    for (int i = 0; i < total; i++) {
        flat[i] = malloc(MAX * sizeof(char));
    }

    int k = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            strcpy(flat[k++], arr[i][j]);
        }
    }

    // Sort alphabetically
    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            if (strcmp(flat[i], flat[j]) > 0) {
                char temp[MAX];
                strcpy(temp, flat[i]);
                strcpy(flat[i], flat[j]);
                strcpy(flat[j], temp);
            }
        }
    }

    // Print sorted matrix
    k = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%s ", flat[k++]);
        }
        printf("\n");
    }

    // Free memory
    for (int i = 0; i < total; i++) {
        free(flat[i]);
    }
    free(flat);
    free(arr);

    return 0;
}
