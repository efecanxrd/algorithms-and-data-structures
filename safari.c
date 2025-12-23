#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//A safari reservation system. Areas have limited space for cars
//If there are more cars reserved than limit in particular timeline, we warn.

typedef struct area_s {
    char areaName[26];
    int *present;
    int max;
    struct requests_s *request;
    struct area_s *next;
} area;

typedef struct requests_s {
    char vehicleName[26];
    char areaName[26]; //We don't need this but can be used for diff implementations
    char arrivalTime[6];
    char departureTime[6];
    struct requests_s *next;
} requests;

area *node1() {
    area *eptr = malloc(sizeof(area));
    if (eptr == NULL) {
        fprintf(stderr, "Memory Allocation Error!");
        exit(EXIT_FAILURE);
    }
    return eptr;
}

requests *node2() {
    requests *eptr = malloc(sizeof(requests));
    if (eptr == NULL) {
        fprintf(stderr, "Memory Allocation Error!");
        exit(EXIT_FAILURE);
    }
    return eptr;
}


int main(int argc, char *argv[]) {
    area *head = NULL;

    char areaName[26], arrival[6], departure [6];
    int max;

    if (argc < 3) {
        fprintf(stderr, "Wrong arguments!");
        exit(EXIT_FAILURE);
    }

    FILE * fptr = fopen(argv[1], "r");
    FILE * fptr2 = fopen(argv[2], "r");

    if (fptr == NULL || fptr2 == NULL) {
        fprintf(stderr, "Error while opening the files");
        exit(-1);
    }

    while (fscanf(fptr, "%s %d", areaName, &max) == 2) {
        area *node = node1();
        strcpy(node->areaName, areaName);
        node->present = calloc(24 * 4, sizeof(int));
        if (node->present == NULL) exit(-1);
        node->max = max;
        node->request = NULL;
        node->next = head;
        head = node;
    }

    fclose(fptr);

    char line[256];
    char vehicleName[26];

    while (fgets(line, 256, fptr2)) {
        if (line[0] == '#') {
            sscanf(line, "#%s", vehicleName);
            continue;
        }
        sscanf(line,  "%s %s %s", areaName, arrival, departure);
        requests *node = node2();
        strcpy(node->vehicleName, vehicleName);
        strcpy(node->areaName, areaName);
        strcpy(node->arrivalTime, arrival);
        strcpy(node->departureTime, departure);
        node->next = NULL;

        area *curr = head;
        while (curr != NULL) {
            if (strcmp(areaName, curr->areaName) == 0) {
                node->next = curr->request;
                curr->request = node;
                break;
            }
            curr = curr->next;
        }

    }


    fclose(fptr2);

    int Ahour, Amin, Dhour, Dmin;
    area *p = head;
    while (p != NULL) {
        fprintf(stdout, "%s %d\n", p->areaName, p->max);
        requests *d = p->request;
        while (d != NULL) {
            fprintf(stdout, "%s %s %s %s\n", d->vehicleName, d->areaName, d->arrivalTime, d->departureTime);
            sscanf(d->arrivalTime, "%d:%d", &Ahour, &Amin);
            sscanf(d->departureTime, "%d:%d", &Dhour, &Dmin);

            int index = Ahour * 4 + Amin / 15;
            int index2 = Dhour * 4 + Dmin / 15;

            for (int i=index; i<=index2; i++) {
                p->present[i]++;
            }

            for (int i=0; i<96; i++) {
                if (p->present[i] > p->max) {
                    fprintf(stdout, "Found an inconsistency.\n%s, at %s has been present between %d:%d - %d-%d, overruling the maximum of %d\n", d->vehicleName, p->areaName, Ahour, Amin, Dhour, Dmin, p->max);
                }
            }


            d = d->next;
        }
        p = p->next;
        fprintf(stdout, "\n \n");
    }

    return 0;
}
