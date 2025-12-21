#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct employees_s {
    char lastname[50];
    char name[50];
    char id[50];
    int workingWeeks;
    int total;
    struct weeks_t *weeks;
    struct employees_s *next;
} Employees;

typedef struct weeks_s {
    int week;
    int workingDays;
    int *hours;
    int totalwork;
    struct weeks_s *next;
} weeks_t;

Employees *node1() {
    Employees *eptr = malloc(sizeof(Employees));

    if (eptr == NULL) {
        fprintf(stderr, "Memory Allocation Error");
        exit(EXIT_FAILURE);
    }

    return eptr;
}

weeks_t *node2() {
    weeks_t *eptr = malloc(sizeof(weeks_t));

    if (eptr == NULL) {
        fprintf(stderr, "Memory Allocation Error");
        exit(EXIT_FAILURE);
    }

    return eptr;
}

void tot(Employees *head) {
    int total = 0; //all hours total for all weeks

    Employees *p = head;
    while (p != NULL) {
        weeks_t *d = p->weeks;
        while (d != NULL) {
            total += d->totalwork;
            d = d->next;
        }
        p->total = total;
        p = p->next;
        total = 0;
    }
}

void swapData(Employees *a, Employees *b) {
    char lastname[50], name[50], id[50];
    strcpy(lastname, a->lastname);
    strcpy(name, a->name);
    strcpy(id, a->id);

    strcpy(a->lastname, b->lastname);
    strcpy(a->name, b->name);
    strcpy(a->id, b->id);

    int tmpWeeks = a->workingWeeks;
    int tmpTotal = a->total;
    weeks_t *tmpPtr = a->weeks;

    a->workingWeeks = b->workingWeeks;
    a->total = b->total;
    a->weeks = b->weeks;

    strcpy(b->lastname, lastname);
    strcpy(b->name, name);
    strcpy(b->id, id);
    b->workingWeeks = tmpWeeks;
    b->total = tmpTotal;
    b->weeks = tmpPtr;
}

void sortEmployees(Employees *head) {
    if (!head) return;

    bool swapped;
    Employees *p;

    do {
        swapped = false;
        p = head;

        while (p->next != NULL) {
            if (p->total < p->next->total) { // sort descending
                swapData(p, p->next);
                swapped = true;
            }
            p = p->next;
        }
    } while (swapped);
}

void traverseEmployees(Employees *head) {
    Employees *p = head;

    while (p != NULL) {
        printf("Employee: %s %s %s | Weeks: %d | Total: %d\n",
               p->lastname, p->name, p->id,
               p->workingWeeks, p->total);

        weeks_t *w = p->weeks;
        while (w != NULL) {
            printf("   Week %d | Days: %d | TotalWork: %d\n",
                   w->week, w->workingDays, w->totalwork);

            printf("      Hours: ");
            for (int i = 0; i < w->workingDays; i++)
                printf("%d ", w->hours[i]);
            printf("\n");

            w = w->next;
        }

        p = p->next;
    }
}

int main(int argc, char *argv[]) {
    Employees *head = NULL;
    weeks_t *head2 = NULL;

    char lastname[50], name[50], id[50];
    int weeks;


    if (argc < 3) {
        fprintf(stderr, "Wrong arguments! | program_name file1 file2");
        exit(EXIT_FAILURE);
    }

    FILE * fptr = fopen(argv[1], "r");
    FILE * fptr2 = fopen(argv[2], "w");

    if (fptr == NULL || fptr2 == NULL) {
        fprintf(stderr, "Error while opening files!");
        exit(EXIT_FAILURE);
    }

    char line[256];

    int *indexes = malloc(sizeof(int) * 10);
    if (indexes == NULL) exit(-1);

    bool on_person = false;


    while (fgets(line, 256, fptr)) {

        if (sscanf(line, "%s %s %[^0-9] %d", lastname, name, id, &weeks) == 4) {
            Employees *node = node1();
            strcpy(node->lastname, lastname);
            strcpy(node->name, name);
            strcpy(node->id, id);
            node->workingWeeks = weeks;
            node->weeks = NULL;
            node->next = head;

            head = node;

            on_person = true;

        } else {
            int week, days, hour; //day as working hours in that particular day
            char *ptr = line;


            sscanf(ptr, "%d %d", &week, &days);
            while (*ptr && *ptr != ' ') ptr++;
            while (*ptr == ' ') ptr++;
            while (*ptr && *ptr != ' ') ptr++;
            while (*ptr == ' ') ptr++;

            weeks_t *nodex = node2();
            nodex->week = week;
            nodex->workingDays = days;
            nodex->totalwork = 0;


            int count = 0;
            int total = 0;

            nodex->hours = (int *) malloc(sizeof(int) * days);
            if (nodex->hours == NULL) exit(-1);

            while (sscanf(ptr, "%d", &hour) == 1) {
                nodex->hours[count] = hour;
                total += hour;
                count++;
                while (*ptr && *ptr != ' ') ptr++;
                while (*ptr == ' ') ptr++;

            }
            nodex->totalwork += total;
            nodex->next = head->weeks;
            head->weeks = nodex;

        }
    }

    fclose(fptr);

    tot(head);
    sortEmployees(head);
    traverseEmployees(head);

    return 0;
}

