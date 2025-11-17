#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORD 20
#define MAX_LINE 100
#define MAX_INDEX 10

typedef struct {
    char word[MAX_WORD+1];
    int occurences;
    int positions[MAX_INDEX];
} Words;

Words *opr(FILE * fptr, FILE * fptr2, int assets);

int main() {
    int f2r;
    char string[MAX_WORD], string2[1024];
    FILE * fptr = fopen("del.txt", "r+");
    FILE * fptr2 = fopen("del2.txt", "r+");

    if (fptr == NULL || fptr2 == NULL) {
        fprintf(stderr, "Couldn't read the files.");
        exit(-1);
    }

    fscanf(fptr2,"%d", &f2r);

    Words *words = opr(fptr, fptr2, f2r);

    for(int i = 0; i<f2r; i++) {
        fprintf(stdout, "%s - %d occurence(s) - word(s):", words[i].word, words[i].occurences);
        for(int j=0; j<words[i].occurences; j++) {
            fprintf(stdout, " %d", words[i].positions[j]);
            }
        fprintf(stdout, "\n");
        }


    return 0;
}

Words *opr(FILE * fptr, FILE * fptr2, int assets) {
    int count1 = 0;
    char string[MAX_WORD+1], string2[1024];

    Words *words = malloc(sizeof(Words) * assets);

    if(words == NULL) {
        fprintf(stderr, "Failed to reallocate memory");
        exit(-1);
     }

    for (int i=0; i<assets; i++) {
        fscanf(fptr2, "%s", string);
        strcpy(words[count1].word, string);
        words[count1].occurences = 0;
        int position_index = 0, current_word_pos = 0;
        int count = 0;

        do {
            for (int j = 0; string[j] != '\0'; j++) {
                string[j] = tolower(string[j]);
            }
            for (int j = 0; string2[j] != '\0'; j++) {
                string2[j] = tolower(string2[j]);
            }

            if(strcmp(string, string2) == 0) {
                words[count1].occurences++;
                if(words[count1].occurences < MAX_INDEX) words[count1].positions[words[count1].occurences - 1] = count;
            } count++;

        } while(fscanf(fptr, "%s", string2) != EOF);

        count1++;
        rewind(fptr);
    }

    return words;
}
