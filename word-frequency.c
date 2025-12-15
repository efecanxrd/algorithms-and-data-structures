#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 100

typedef struct words_s {
    char word[max];
    int freq;
    struct words_s *next;
} words_t;

words_t *new_element() {
    words_t *eptr = malloc(sizeof(words_t));
    if (eptr == NULL) exit(-1);
    return eptr;
}

words_t *add(FILE *fptr, words_t *head) {
    char word[max];
    while (fscanf(fptr, "%s", word) == 1) {
        for (int i=0; word[i] != '\0'; i++) { //Lower the string as a rule
            word[i] = tolower((unsigned char)word[i]);
        }
        if (head == NULL) { //First initialization
            words_t *node = new_element();
            strcpy(node->word, word);
            node->freq = 1;
            node->next = NULL;
            head = node;
        }
        else {
            words_t *iter = head;
            int found = 0;

            while (iter != NULL) {
                if (strcmp(iter->word, word) == 0) {
                    iter->freq++;
                    found = 1;
                    break;
                } iter = iter->next;
            }
                 if (found == 0) {
                    words_t *node = new_element();
                    strcpy(node->word, word);
                    node->freq = 1;
                    node->next = head;
                    head = node;
            }
        }

    }
    return head;
}

void mostra(words_t *head) {
    words_t *p = head;
    while (p!=NULL) {
        fprintf(stdout, "%s - %d\n", p->word, p->freq);
        p = p->next;
    }
}

int main() {
    char word[max], word2[max];
    FILE * fptr = fopen("file1.txt", "r+");
    if (fptr == NULL) exit(-1);

    words_t *head = NULL;
    head = add(fptr, head);
    mostra(head);

    return 0;
}
