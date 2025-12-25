#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct films_s {
    char title[41];
    int length;
    struct films_s *next;
} films;

typedef struct Persona_s {
    char name[31];
    char profession[21];
    int age;
    int filmCount;
    films **filmList;
    struct Persona_s *next;
} Persona;

Persona *node_create() {
    Persona *eptr = malloc(sizeof(Persona));
    if (eptr == NULL) {
        fprintf(stderr, "Memory allocation error!");
        exit(EXIT_FAILURE);
    }

    return eptr;
}

films *node_create2() {
    films *eptr = malloc(sizeof(films));
    if (eptr == NULL) {
        fprintf(stderr, "Memory allocation error!");
        exit(EXIT_FAILURE);
    }

    return eptr;
}

void printAll(Persona *head) {
    Persona *p = head;

    while (p != NULL) {
        printf("Name: %s\n", p->name);
        printf("Profession: %s\n", p->profession);
        printf("Age: %d\n", p->age);

        printf("Films (%d):\n", p->filmCount);

        for (int i = 0; i < p->filmCount; i++) {
            films *f = p->filmList[i];
            printf("   - %s (%d min)\n", f->title, f->length);
        }

        printf("\n");
        p = p->next;
    }
}

int main(int argc, char *argv[]) {
    Persona *head = NULL;
    films *head2 = NULL;

    char name[31], profession[21], title[41];
    int age, length;

    FILE * member = fopen("file1.txt", "r");
    FILE * film = fopen("file2.txt", "r");
    FILE * rent = fopen("file3.txt", "r");

    if ((member == NULL) || (film == NULL) || (rent == NULL)) {
        fprintf(stderr, "Error while opening files");
        exit(EXIT_FAILURE);
    }

    while (fscanf(member, "%s %s %d", name, profession, &age) == 3) {
        Persona *node = node_create();
        strcpy(node->name, name);
        strcpy(node->profession, profession);
        node->age = age;
        node->filmList = NULL;
        node->filmCount = 0;
        node->next = head;
        head = node;
    }

    while (fscanf(film, "%s %d", title, &length) == 2) {
        films *node = node_create();
        strcpy(node->title, title);
        node->length = length;
        node->next = head2;
        head2 = node;
    }

    Persona *c1 = head;
    films *c2 = head2;

    while (fscanf(rent, "%s %s", name, title) == 2) {
        c1 = head;
        c2 = head2;
        while (c1 != NULL) {
            if (strcmp(c1->name, name) == 0) {
                break;
            }
            c1 = c1->next;
        }

        while (c2 != NULL) {
            if (strcmp(c2->title, title) == 0) {
                break;
            }
            c2 = c2->next;
        }

        if (c1 == NULL || c2 == NULL) {
            continue;
        }


        c1->filmCount++;
        c1->filmList = realloc(c1->filmList, c1->filmCount * sizeof(films*));
        c1->filmList[c1->filmCount - 1] = c2;
    }

    //printAll(head);

    films *c = head2;
    Persona *p = head;

    while (c != NULL) {
        p = head;
        int num = 0;
        int totalAge = 0;
        printf("%s %d - ", c->title, c->length);
        while (p != NULL) {
            for (int i = 0; i < p->filmCount; i++) {
                films *f = p->filmList[i];
                if (strcmp(c->title, f->title) == 0) {
                    num++;
                    totalAge += p->age;
                }
            }
            p = p->next;
        }

        if (num > 0)
            printf("%d %d\n", num, totalAge / num);
        else
            printf("0 0\n");

        c = c->next;
    }

    return 0;
}
