#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_length 100

struct string {
    char str[max_length];
};

void bubbleSort(struct string *arr, int n) {
    int i, j;
    struct string temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (strcmp((arr[j].str), (arr[j + 1].str)) > 0) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    char word[max_length];
    int length;

    FILE * fptr = fopen("file1.txt", "r+");
    if (fptr == NULL) exit(-1);

    fscanf(fptr, "%d", &length);

    struct string *list = malloc(sizeof(struct string) * length);
    if (list == NULL) exit(-1);


    int count = 0;
    while (fscanf(fptr, "%s", word) == 1) {
        strcpy(list[count].str, word);
        count++;
    }

    bubbleSort(list, count);

    for (int i = 0; i<length; i++) {

        printf("%s\n", list[i].str);
    }

    free(list);
    return 0;
}

