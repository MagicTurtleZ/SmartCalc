#include "back.h"

void printStr(char *s) {
    for (int i = 0; i < strlen(s); i++) {
        printf("%c", s[i]);
    }
    printf("\n");
    // memset(s,0,sizeof(s));
    // for (int i = 0; i < 255; i++) {
    //     s[i] = '\0';
    // }
}

void clearStr(char *s) {
    for (int i = 0; i < 255; i++) {
        s[i] = '\0';
    }
}

int main() {
    char a[256] = "x ^ 2 + 1";
    char b[256] = {0};
    char c[256] = {0};
    double res = 0;
    for (double i = -3; i <= 3.2; i += 0.2) {
        strcpy(b, a);
        string_format(b, i);
        to_polish(b, c);
        printStr(c);
        calc_comp(c, &res);
        printf("%lf\n", res);
    //     // res = 0;
    //     //clearStr(b);
        clearStr(c);
    }
}