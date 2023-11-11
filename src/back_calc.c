#include "./back.h"

void s_push(struct sta **top, int data1, char data2) {
  struct sta *tmp;
  tmp = malloc(sizeof(struct sta));
  tmp->prior = data1;
  tmp->symb = data2;
  if ((*top) == NULL) {
    tmp->link = NULL;
    *top = tmp;
  } else {
    tmp->link = *top;
    *top = tmp;
  }
}

char s_pop(struct sta **top) {
  struct sta *out = NULL;
  out = *top;
  *top = out->link;
  char oper = out->symb;
  free(out);
  return oper;
}

void s_delite(struct sta **top) {
  struct sta *out = *top;
  *top = out->link;
  free(out);
}

void c_push(struct cell **top, double data) {
  struct cell *tmp;
  tmp = malloc(sizeof(struct cell));
  tmp->number = data;
  if ((*top) == NULL) {
    tmp->link = NULL;
    *top = tmp;
  } else {
    tmp->link = *top;
    *top = tmp;
  }
}

double c_pop(struct cell **top) {
  struct cell *out = NULL;
  out = *top;
  *top = out->link;
  double oper = out->number;
  free(out);
  return oper;
}

void c_delite(struct cell **top) {
  struct cell *out = *top;
  *top = out->link;
  free(out);
}

int get_priority(const list obj[], char token) {
  for (int i = 0; i < 17; i++) {
    if (obj[i].symb == token) {
      return obj[i].prior;
    }
  }
  return 0;
}

char find_short(char *full_name) {
  char short_name = 0;
  if (strcmp(full_name, "cos") == 0) {
    short_name = 'c';
  }
  if (strcmp(full_name, "sin") == 0) {
    short_name = 's';
  }
  if (strcmp(full_name, "tan") == 0) {
    short_name = 't';
  }
  if (strcmp(full_name, "acos") == 0) {
    short_name = 'a';
  }
  if (strcmp(full_name, "asin") == 0) {
    short_name = 'i';
  }
  if (strcmp(full_name, "atan") == 0) {
    short_name = 'n';
  }
  if (strcmp(full_name, "sqrt") == 0) {
    short_name = 'q';
  }
  if (strcmp(full_name, "ln") == 0) {
    short_name = 'l';
  }
  if (strcmp(full_name, "log") == 0) {
    short_name = 'o';
  }
  return short_name;
}

int string_format(char *input_string, double x_num) {
  char buffer[255] = {0};
  for (size_t i = 0, j = 0; i < strlen(input_string); i++) {
    if (input_string[i] == 'c' || input_string[i] == 's' ||
        input_string[i] == 't' || input_string[i] == 'a' ||
        input_string[i] == 'l') {
      char long_name[5] = {0};
      int z = 0;
      while (input_string[i] != '(') {
        long_name[z++] = input_string[i];
        i++;
      }
      i--;
      buffer[j++] = find_short(long_name);
      continue;
    }
    if (input_string[i] == 'm') {
      buffer[j++] = '%';
      i += 2;
      continue;
    }
    if (input_string[i] == '-' &&
        (input_string[i + 1] > 47 && input_string[i + 1] < 58)) {
      buffer[j++] = '~';
      continue;
    }
    if (input_string[i] == 'x') {
      char src[20] = {0};
      sprintf(src, "%lf", x_num);
      if (src[0] == '-') {
        src[0] = '~';
      }
      strcat(buffer, src);
      j = (int)strlen(buffer);
      continue;
    }
    buffer[j++] = input_string[i];
  }
  for (size_t i = 0; i < 255; i++) {
    input_string[i] = '\0';
  }
  for (size_t i = 0; i < strlen(buffer); i++) {
    input_string[i] = buffer[i];
  }
  return SUCCESS;
}

void to_polish(const char *input_string, char *polish_stirng) {
  struct sta *aboba = NULL;
  list operators[17] = {{1, 'c'}, {1, 's'}, {1, 't'}, {1, 'a'}, {1, 'i'},
                        {1, 'n'}, {1, 'q'}, {1, 'l'}, {1, 'o'}, {1, '('},
                        {2, '+'}, {2, '-'}, {3, '*'}, {3, '/'}, {3, '%'},
                        {5, '~'}, {4, '^'}};
  int j = 0;
  for (size_t i = 0; i < strlen(input_string); i++) {
    if ((input_string[i] > 47 && input_string[i] < 58) ||
        input_string[i] == '.') {
      polish_stirng[j++] = input_string[i];
      if (input_string[i + 1] <= 45 || input_string[i + 1] >= 58 ||
          input_string[i + 1] == 47) {
        polish_stirng[j++] = ' ';
      }
      continue;
    }
    if (input_string[i] == '+' || input_string[i] == '-' ||
        input_string[i] == '*' || input_string[i] == '/' ||
        input_string[i] == '%' || input_string[i] == '~' ||
        input_string[i] == '^') {
      if (aboba == NULL) {
        s_push(&aboba, get_priority(operators, input_string[i]),
               input_string[i]);
        continue;
      } else {
        int current_prior = get_priority(operators, input_string[i]);
        if (current_prior > aboba->prior) {
          s_push(&aboba, get_priority(operators, input_string[i]),
                 input_string[i]);
          continue;
        } else {
          while (aboba != NULL) {
            if (current_prior <= aboba->prior) {
              polish_stirng[j++] = s_pop(&aboba);
            } else
              break;
          }
          s_push(&aboba, get_priority(operators, input_string[i]),
                 input_string[i]);
          continue;
        }
      }
    }
    if (input_string[i] == 'c' || input_string[i] == 's' ||
        input_string[i] == 't' || input_string[i] == 'a' ||
        input_string[i] == 'i' || input_string[i] == 'n' ||
        input_string[i] == 'q' || input_string[i] == 'l' ||
        input_string[i] == 'o' || input_string[i] == '(') {
      s_push(&aboba, get_priority(operators, input_string[i]), input_string[i]);
      continue;
    }
    if (input_string[i] == ')') {
      while (aboba->symb != '(') {
        polish_stirng[j++] = s_pop(&aboba);
      }
      s_delite(&aboba);
      if (aboba != NULL) {
        if (aboba->symb > 96) {
          polish_stirng[j++] = s_pop(&aboba);
        }
      }
      continue;
    }
  }
  while (aboba != NULL) {
    polish_stirng[j++] = s_pop(&aboba);
  }
}

double get_double(char *polish_string, size_t *i) {
  double result = 0;
  char number[100] = {0};
  int j = 0;
  while ((polish_string[*i] > 47 && polish_string[*i] < 58) ||
         polish_string[*i] == 46) {
    number[j++] = polish_string[*i];
    *i += 1;
  }
  return result = atof(number);
}

void addition(struct cell **src, double s_oper, double f_oper) {
  c_push(src, (f_oper + s_oper));
}

void subtraction(struct cell **src, double s_oper, double f_oper) {
  c_push(src, (s_oper - f_oper));
}

void multiply(struct cell **src, double s_oper, double f_oper) {
  c_push(src, (f_oper * s_oper));
}

int division(struct cell **src, double s_oper, double f_oper) {
  if ((f_oper > -0.0000001 && f_oper < 0.0000001) ||
      (s_oper > -0.0000001 && s_oper < 0.0000001)) {
    c_push(src, f_oper);
    c_push(src, s_oper);
    return FAIL;
  } else
    c_push(src, (s_oper / f_oper));
  return SUCCESS;
}

void modulus(struct cell **src, double s_oper, double f_oper) {
  c_push(src, ((int)f_oper % (int)s_oper));
}

void power(struct cell **src, double s_oper, double f_oper) {
  c_push(src, pow(s_oper, f_oper));
}

int calc_comp(char *polish_string, double *result) {
  struct cell *amogus = NULL;
  int bool = 0;
  for (size_t i = 0; i < strlen(polish_string) && bool != 1; i++) {
    if (polish_string[i] > 47 && polish_string[i] < 58) {
      c_push(&amogus, get_double(polish_string, &i));
      continue;
    }
    switch (polish_string[i]) {
      case '~':
        amogus->number *= -1;
        break;
      case 'c':
        amogus->number = cos(amogus->number);
        break;
      case 's':
        amogus->number = sin(amogus->number);
        break;
      case 't':
        amogus->number = tan(amogus->number);
        break;
      case 'a':
        amogus->number = acos(amogus->number);
        break;
      case 'i':
        amogus->number = asin(amogus->number);
        break;
      case 'n':
        amogus->number = atan(amogus->number);
        break;
      case 'q':
        amogus->number = sqrt(amogus->number);
        break;
      case 'l':
        amogus->number = log(amogus->number);
        break;
      case 'o':
        amogus->number = log10(amogus->number);
        break;
      case '+':
        addition(&amogus, c_pop(&amogus), c_pop(&amogus));
        break;
      case '-':
        subtraction(&amogus, c_pop(&amogus), c_pop(&amogus));
        break;
      case '*':
        multiply(&amogus, c_pop(&amogus), c_pop(&amogus));
        break;
      case '/':
        bool = division(&amogus, c_pop(&amogus), c_pop(&amogus));
        break;
      case '%':
        modulus(&amogus, c_pop(&amogus), c_pop(&amogus));
        break;
      case '^':
        power(&amogus, c_pop(&amogus), c_pop(&amogus));
        break;
    }
  }
  *result = amogus->number;
  return bool == 0 ? SUCCESS : FAIL;
}
