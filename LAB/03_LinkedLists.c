#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define mx 20

typedef struct products_s {
    char name[20*1];
    int price;
    struct products_s *next;
} products;

typedef struct producers_s {
    char name[20+1];
    char id[6+1];
    products *product;
    struct producers_s *next;
} producers;

products *node1() {
    products *eptr = malloc(sizeof(products));
    if (eptr == NULL) {
        fprintf(stderr, "Memory Allocation Error");
        exit(-1);
    }

    return eptr;
}

producers *node2() {
    producers *eptr = malloc(sizeof(producers));
    if (eptr == NULL) {
        fprintf(stderr, "Memory Allocation Error");
        exit(-1);
    }

    return eptr;
}

producers *createProducer(producers *head, char *name, char *id) {
    producers *node = node2();
    strcpy(node->name, name);
    strcpy(node->id, id);
    node->product = NULL;
    node->next = head;
    head = node;

    return head;
}

products *createProduct(products *head, char *name, int price) {
    products *node = node1();
    strcpy(node->name, name);
    node->price = price;
    node->next = head;

    head = node;

    return head;
}

void addProducttoProducer(producers *head, char *id, char *name, int price) {
    producers *p = head;
    while (p != NULL) {
        if (strcmp(p->id, id) == 0) {
            p->product = createProduct(p->product, name, price);
            return;
        }
        p = p->next;
    }
}

void printAll(producers *head) {
    producers *p = head;
    while (p) {
        fprintf(stdout, "%s (%s):\n", p->name, p->id);
        products *pr = p->product;
        while (pr) {
            fprintf(stdout, "     %s -> %d\n", pr->name, pr->price);
            pr = pr->next;
        }
        p = p->next;
    }
}

int main(int argc, char *argv[]) {
    producers *head1 = NULL;
    char word1[mx], word2[mx];
    int price;

    if (argc < 3) {
        fprintf(stderr, "Wrong arguments! | program_name file1 file2");
        exit(-1);
    }

    FILE * fptr = fopen(argv[1], "r");
    FILE * fptr2 = fopen(argv[2], "r");

    if (fptr == NULL || fptr2 == NULL) {
        fprintf(stderr, "File error!");
        exit(-1);
    }

    while (fscanf(fptr, "%s %s", word1, word2) == 2) {
        head1 = createProducer(head1, word1, word2);
    }
    fclose(fptr);

    while (fscanf(fptr2, "%s %s %d", word1, word2, &price) == 3) {
        addProducttoProducer(head1, word1, word2, price);
    }
    fclose(fptr2);

    printAll(head1);

    return 0;
}
