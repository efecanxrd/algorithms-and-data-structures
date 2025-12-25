#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct driver_s {
    int driverNumber;
    char driverName[21];
    char teamName[21];
    int laps;
    int *lapTime;
    int totalTime;
    struct driver_s *next;
} Driver;

Driver *createNode() {
    Driver *eptr = malloc(sizeof(Driver));
    if (eptr == NULL) {
        fprintf(stderr, "Memory Allocation Error");
        exit(EXIT_FAILURE);
    }

    return eptr;
}

void sortDrivers(Driver **head) {
    if (*head == NULL) return;

    int swapped;
    Driver *p;
    Driver *last = NULL;

    do {
        swapped = 0;
        p = *head;

        while (p->next != last) {
            if (p->totalTime > p->next->totalTime) {

                // swap DATA, not nodes
                int tmpNum = p->driverNumber;
                p->driverNumber = p->next->driverNumber;
                p->next->driverNumber = tmpNum;

                char tmpName[21];
                strcpy(tmpName, p->driverName);
                strcpy(p->driverName, p->next->driverName);
                strcpy(p->next->driverName, tmpName);

                char tmpTeam[21];
                strcpy(tmpTeam, p->teamName);
                strcpy(p->teamName, p->next->teamName);
                strcpy(p->next->teamName, tmpTeam);

                int tmpLaps = p->laps;
                p->laps = p->next->laps;
                p->next->laps = tmpLaps;

                int *tmpLapArr = p->lapTime;
                p->lapTime = p->next->lapTime;
                p->next->lapTime = tmpLapArr;

                int tmpTotal = p->totalTime;
                p->totalTime = p->next->totalTime;
                p->next->totalTime = tmpTotal;

                swapped = 1;
            }
            p = p->next;
        }
        last = p;
    } while (swapped);
}

int main(int argc, char *argv[]) {
    Driver *head = NULL;

    char line[21], name[21], team[21];
    int driverNumber, lapTime;
    int lapsCount = atoi(argv[1]);

    if (argc < 3) {
        fprintf(stderr, "Wrong arguments");
        exit(EXIT_FAILURE);
    }

    FILE * fptr = fopen(argv[2], "r");
    if (fptr == NULL) {
        fprintf(stderr, "File error!");
        exit(EXIT_FAILURE);
    }

    while (fscanf(fptr, "%s", line) == 1) {
        FILE *fptr2 = fopen(line, "r");

        if (fptr2 == NULL) {
            fprintf(stderr, "Error while opening %s", line);
            exit(EXIT_FAILURE);
        }

        int laps = 0; //for arr

        while (fscanf(fptr2, "%d %s %s %d", &driverNumber, name, team, &lapTime) == 4) {
            Driver *c = head;
            int found = 0;

            //fprintf(stdout, "%d %s %s %d", driverNumber, name, team, lapTime);

            while (c != NULL) {
                if (strcmp(c->driverName, name) == 0) {
                    found = 1;
                    c->lapTime[c->laps] = lapTime;
                    c->laps++;
                    break;
                }
                c = c->next;
            }

            if (found == 0) {
                Driver *node = createNode();
                node->driverNumber = driverNumber;
                strcpy(node->driverName, name);
                strcpy(node->teamName, team);
                node->laps = 0; //initialization
                node->lapTime = calloc(lapsCount, sizeof(int));
                node->lapTime[node->laps] = lapTime;
                node->laps++;
                node->totalTime = 0;
                node->next = head;
                head = node;
            }
        }

        fclose(fptr2);

    }

    Driver *p = head;

    Driver *fastest;
    int lap = 99999;

    while (p != NULL) {
        //fprintf(stdout, "%d %s %s %d\n", p->driverNumber, p->driverName, p->teamName, p->laps);
        for (int i=0; i < p->laps; i++) {
            //fprintf(stdout, "%d ", p->lapTime[i]);
            p->totalTime += p->lapTime[i];
            if (p->lapTime[i] <= lap) {
                lap = p->lapTime[i];
                fastest = p;
            }
        }
        p = p->next;
    }

    fprintf(stdout, "Fastest Lap: %s, %s, %d seconds, Lap: %d\n", fastest->driverName, fastest->teamName, lap, fastest->laps);

    sortDrivers(&head);

    fprintf(stdout, "\n\nDriver ranking\n");
    Driver *c = head;

    for (int j=1; j<=3; j++) {
        fprintf(stdout, "%d %s, %s, %d seconds\n", j, c->driverName, c->teamName, c->totalTime);
        for (int i=0; i < c->laps; i++) {
        }
        c = c->next;
    }


    fclose(fptr);

    return 0;
}
