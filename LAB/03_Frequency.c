#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct list_s {
    char word[MAX];
    int freq;
    struct list_s *next;
} list_t;

list_t *new_element() {
    list_t *eptr = malloc(sizeof(list_t));
    if (eptr == NULL) {
        fprintf(stderr, "Memory error");
        exit(EXIT_FAILURE);
    }
    return eptr;
}

list_t *add(list_t *head, FILE *fptr) {
    char word[MAX];

    while (fscanf(fptr, "%s", word) == 1) {
        for (int i = 0; word[i] != '\0'; i++) {
            word[i] = tolower((unsigned char) word[i]);
        }


        if (head == NULL) { //first initialization
            list_t *new_node = new_element();
            strcpy(new_node->word, word);
            new_node->freq = 1;
            new_node->next = head;
            head = new_node;
        } else { //if already initialized

            list_t *itr = head;
            int found = 0;
            while (itr != NULL) {
                if (strcmp(itr->word, word) == 0) {
                    itr->freq++;
                    found++;

                }
                itr = itr->next;
            }
                if (found == 0) {
                    list_t *new_node = new_element();
                    strcpy(new_node->word, word);
                    new_node->freq = 1;
                    new_node->next = head;
                    head = new_node;
                }
            }
    }
    return head;
}

void printx(list_t *head, FILE * fptr) {
    list_t *p = head;
    while (p != NULL) {
        fprintf(stdout, "%s %d\n", p->word, p->freq);
        fprintf(fptr, "%s %d\n", p->word, p->freq);
        p = p->next;
    }
}

int main(int argc, char *argv[]) {

    char word[MAX];
    if (argc < 3) {
        fprintf(stderr, "Error");
        exit(EXIT_FAILURE);
    }

    FILE * fptr = fopen(argv[1], "r+");
    if (fptr == NULL) exit(-1);

    FILE * fptr2 = fopen(argv[2], "w");
    if (fptr2 == NULL) exit(-1);

    list_t *head = NULL;
    head = add(head, fptr);
    printx(head, fptr2);
    return 0;
}
