#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_length 100

typedef struct Persona_s {
    struct Persona_s *prev;
    char name[50+1];
    char id[16+1];
    char date[10+1];
    int salary;
    struct Persona_s *next;
} persona;

persona *new() { //Creating new nodes
    persona *eptr = malloc(sizeof(persona));
    if (eptr == NULL) {
        fprintf(stderr, "Memory Allocation Error");
        exit(EXIT_FAILURE);
    }
    return eptr;
}

persona *push(persona *head, FILE * fptr) { //Pushing persons data to list from file
    char name[50+1], id[16+1], date[10+1];
    int salary;

    while (fscanf(fptr, "%s %s %s %d", name, id, date, &salary) == 4) {
        //fprintf(stdout, "%s %s %s %d\n", name, id, date, salary);
        persona *new_node = new();
        strcpy(new_node->name, name);
        strcpy(new_node->id, id);
        strcpy(new_node->date, date);

        new_node->salary = salary;
        new_node->prev = NULL;
        new_node->next = head;
        if (head) head->prev = new_node;
        head = new_node;
    }
    return head;
}

void traversal(persona *head, char name[], char string[]) { //traverse in list according to string
    persona *p = head;
    persona *temp = NULL;
    while (p != NULL) {
        if (strcmp(p->name, name) == 0) {
            fprintf(stdout, "%s %s %s %d\n", p->name, p->id, p->date, p->salary);
            temp = p;
        }
        p = p->next;
    }

    if (temp == NULL) {
        fprintf(stdout, "Couldn't find %s", name);
        exit(0);
    }

    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == '-') {
            if (temp->prev != NULL) temp = temp->prev;
            fprintf(stdout, "%s %s %s %d\n", temp->name, temp->id, temp->date, temp->salary);
        }
        else if (string[i] == '+') {
            if (temp->next != NULL) temp = temp->next;
            fprintf(stdout, "%s %s %s %d\n", temp->name, temp->id, temp->date, temp->salary);
        }
    }
}


int main(int argc, char *argv[]) {

    if (argc < 4) {
        fprintf(stderr, "Wrong parameters. programname, filename, name, string");
        exit(EXIT_FAILURE);
    }

    persona *head = NULL;

    FILE *fptr = fopen(argv[1], "r");
    if (fptr == NULL) exit(-1);

    head = push(head, fptr);
    traversal(head, argv[2], argv[3]);

    return 0;
}

