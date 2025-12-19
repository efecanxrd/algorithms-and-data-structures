#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mult(int x, int y) {
    if (y==0) return 0;
    if (y==1) return x;
    return x + mult(x, y-1);
}

void d2b(int d, int *b, int *n) {
    if (d == 0) {
        *n = 0;
        return;
    }

    int index = 0;
    while (d > 0) {
        b[index++] = d % 2;
        d /= 2;
    }
    *n = index;
}

int catalan(int n) {
    if (n == 0) return 1;

    int result = 0;
    for (int i = 0; i < n; i++) {
        result += catalan (i) * catalan(n - 1 - i);
    }
    return result;

}

int countSpaces(char *s) {
    if (*s=='\0') {return 0;}

    return (isspace((unsigned char)*s) ? 1 : 0 + countSpaces(s + 1));
}

int main() {



    return 0;
}

