#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAIL 1

struct sta {
  int prior;
  char symb;
  struct sta *link;
};

struct cell {
  double number;
  struct cell *link;
};

typedef struct {
  int prior;
  char symb;
} list;

void s_push(struct sta **top, int data1, char data2);
char s_pop(struct sta **top);
void s_delite(struct sta **top);
void c_push(struct cell **top, double data);
double c_pop(struct cell **top);
void c_delite(struct cell **top);
int get_priority(const list obj[], char token);
char find_short(char *full_name);
int string_format(char *input_string, double x_num);
void to_polish(const char *input_string, char *polish_stirng);
double get_double(char *polish_string, size_t *i);
void addition(struct cell **src, double f_oper, double s_oper);
void subtraction(struct cell **src, double f_oper, double s_oper);
void multiply(struct cell **src, double f_oper, double s_oper);
int division(struct cell **src, double f_oper, double s_oper);
void modulus(struct cell **src, double f_oper, double s_oper);
void power(struct cell **src, double f_oper, double s_oper);
int calc_comp(char *polish_string, double *result);

/* Short named func:
cos - c;
sin - s;
tan - t;
acos - a;
asin - i;
atan - n;
sqrt - q;
ln - l;
log - o;
*/