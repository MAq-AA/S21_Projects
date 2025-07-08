#include "s21_string.h"

#define DIGIT_IN_ARGS -1

#define DEFOULT_TYPE 0
#define SHORT_TYPE 1
#define LONG_TYPE 2
#define LONG_D_TYPE 3

struct scanf_spec {
  char type;
  int width;
  int len_of_type;
  bool dont_scanf;
  bool smth_read;
  bool wght_in_spec;
};

void skip_space(const char* buffer, int* b_i);
int check_system(const char* buffer, int* b_i);
bool check_for_nil(const char* buffer, int* b_i);
bool get_spec_type(char c, struct scanf_spec* Spec);
int get_digit_from_str(const char* format, int* f_i);
bool get_len_of_type(char c, struct scanf_spec* Spec);
unsigned long get_current_max(struct scanf_spec* Spec);
float chose_INF_or_NAN(const char* buffer, int* b_i, bool has_sign);
bool step_dot(const char* buffer, int* b_i, struct scanf_spec* Spec);
long double chenge_by_e(const char* buffer, int* b_i, long double fn);
bool check_sign(const char* buffer, int* b_i, struct scanf_spec* Spec);
void check_for_dont_scanf(const char* format, int f_i, int* s_c);
void skip_float(const char* buffer, int* b_i, struct scanf_spec* Spec);
void get_str(const char* buffer, int* b_i, char*, struct scanf_spec* Spec);
bool check_for_nan_or_inf(const char* buffer, int* b_i,
                          struct scanf_spec* Spec);
void put_number_of_char_scanf(int b_i, struct scanf_spec Spec, va_list args);
unsigned long route_by_system(const char* buffer, int* b_i,
                              struct scanf_spec* Spec);
bool parse_scanf_specificator(const char* format, int* f_i,
                              struct scanf_spec* Spec);
long double get_float_from_buffer(const char* buffer, int* b_i,
                                  struct scanf_spec* Spec);
long double get_fraction_from_buffer(const char* buffer, int* b_i,
                                     struct scanf_spec* Spec);
bool get_intenger_number(const char* buffer, int* b_i, struct scanf_spec* Spec,
                         va_list args);
bool put_scanf_spec(const char* buffer, const char* format, int* b_i, int* f_i,
                    va_list args);
unsigned long read_intenger(const char* buffer, int* b_i, bool* has_sign,
                            struct scanf_spec* Spec);
bool scanf_route_by_specificator(const char* buffer, int* b_i,
                                 struct scanf_spec* Spec, va_list args);
void get_char(const char* buffer, int* b_i, struct scanf_spec* Spec,
              va_list args);
unsigned long get_decimal_from_buffer(const char* buffer, int* b_i,
                                      struct scanf_spec* Spec);
unsigned long get_oct_from_buffer(const char* buffer, int* b_i,
                                  struct scanf_spec* Spec);
unsigned long get_hex_from_buffer(const char* buffer, int* b_i,
                                  struct scanf_spec* Spec);
void get_float_or_mantissa(const char* buffer, int* b_i,
                           struct scanf_spec* Spec, va_list args);

int s21_sscanf(const char* buffer, const char* format, ...) {
  int format_index = 0;
  int buffer_index = 0;
  char c = format[format_index];
  va_list args;
  va_start(args, format);
  int success_spec_counter = 0;
  if (buffer && s21_strlen(buffer) != 0) {
    while (c != '\0') {
      if (c == '%') {
        if (put_scanf_spec(buffer, format, &buffer_index, &format_index,
                           args)) {
          check_for_dont_scanf(format, format_index, &success_spec_counter);
        } else {
          break;
        }
      } else if (c == ' ') {
        skip_space(buffer, &buffer_index);
      } else if (buffer[buffer_index++] != c) {
        break;
      }
      c = format[++format_index];
    }
  } else {
    success_spec_counter = -1;
  }
  va_end(args);

  return success_spec_counter;
}

void check_for_dont_scanf(const char* format, int f_i, int* s_c) {
  if (format[f_i] != '%') {
    bool res = false;
    while (format[f_i] != '%' && !res) {
      if (format[f_i--] == '*') res = true;
    }
    if (!res) {
      (*s_c)++;
    }
  }
}

void skip_space(const char* buffer, int* b_i) {
  while (buffer[*b_i] == ' ' || buffer[*b_i] == '\t' || buffer[*b_i] == '\n')
    (*b_i)++;
}

bool put_scanf_spec(const char* buffer, const char* format, int* b_i, int* f_i,
                    va_list args) {
  struct scanf_spec Spec;
  s21_memset(&Spec, 0, sizeof(struct scanf_spec));
  bool res = true;

  if (format[++(*f_i)] != '%') {
    if (parse_scanf_specificator(format, f_i, &Spec)) {
      if (!scanf_route_by_specificator(buffer, b_i, &Spec, args)) {
        res = false;
      }
    } else {
      res = false;
    }
  } else if (buffer[(*b_i)++] != format[*f_i]) {
    res = false;
  }

  return res;
}

bool parse_scanf_specificator(const char* format, int* f_i,
                              struct scanf_spec* Spec) {
  bool next_is_precision = false;
  char cur_symb = format[(*f_i)];
  bool all_success = true;

  while (true) {
    if (((cur_symb > '0' || next_is_precision) && cur_symb <= '9')) {
      Spec->width = get_digit_from_str(format, f_i);
      Spec->wght_in_spec = true;
    } else if (cur_symb == '*') {
      Spec->dont_scanf = true;
    } else {
      if (!get_spec_type(cur_symb, Spec)) {
        if (!get_len_of_type(cur_symb, Spec)) {
          all_success = false;
          break;
        }
      } else {
        break;
      }
    }
    cur_symb = format[++(*f_i)];
  }

  return Spec->type && all_success;
}

bool get_spec_type(char c, struct scanf_spec* Spec) {
  bool res = true;
  switch (c) {
    case 'c':
      Spec->type = c;
      break;
    case 'd':
      Spec->type = c;
      break;
    case 'i':
      Spec->type = c;
      break;
    case 'e':
      Spec->type = c;
      break;
    case 'E':
      Spec->type = c;
      break;
    case 'f':
      Spec->type = c;
      break;
    case 'g':
      Spec->type = c;
      break;
    case 'G':
      Spec->type = c;
      break;
    case 'o':
      Spec->type = c;
      break;
    case 's':
      Spec->type = c;
      break;
    case 'u':
      Spec->type = c;
      break;
    case 'x':
      Spec->type = c;
      break;
    case 'X':
      Spec->type = c;
      break;
    case 'p':
      Spec->type = c;
      break;
    case 'n':
      Spec->type = c;
      break;
    default:
      res = false;
  }
  return res;
}

bool get_len_of_type(char c, struct scanf_spec* Spec) {
  bool res = true;
  switch (c) {
    case 'h':
      res = Spec->len_of_type ? false : true;
      Spec->len_of_type = SHORT_TYPE;
      break;
    case 'l':
      res = Spec->len_of_type ? false : true;
      Spec->len_of_type = LONG_TYPE;
      break;
    case 'L':
      res = Spec->len_of_type ? false : true;
      Spec->len_of_type = LONG_D_TYPE;
      break;
    default:
      res = false;
  }
  return res;
}

bool scanf_route_by_specificator(const char* buffer, int* b_i,
                                 struct scanf_spec* Spec, va_list args) {
  if (Spec->type == 'c' || Spec->type == 's') {
    get_char(buffer, b_i, Spec, args);
  } else if (Spec->type == 'g' || Spec->type == 'G' || Spec->type == 'E' ||
             Spec->type == 'e' || Spec->type == 'f') {
    skip_space(buffer, b_i);
    if (!Spec->dont_scanf) {
      get_float_or_mantissa(buffer, b_i, Spec, args);
    } else {
      skip_float(buffer, b_i, Spec);
    }
  } else if (Spec->type == 'n') {
    put_number_of_char_scanf(*b_i, *Spec, args);
  } else {
    skip_space(buffer, b_i);
    get_intenger_number(buffer, b_i, Spec, args);
  }

  return Spec->smth_read;
}

void get_char(const char* buffer, int* b_i, struct scanf_spec* Spec,
              va_list args) {
  if (!Spec->dont_scanf) {
    char* str = va_arg(args, char*);
    if (Spec->type == 'c') {
      *str = buffer[(*b_i)++];
      Spec->smth_read = true;
    } else if (Spec->type == 's') {
      skip_space(buffer, b_i);
      get_str(buffer, b_i, str, Spec);
    }
  } else {
    if (Spec->type == 'c') {
      (*b_i)++;
      Spec->smth_read = true;
    } else if (Spec->type == 's') {
      skip_space(buffer, b_i);
      while (buffer[*b_i] != '\n' && buffer[*b_i] != ' ' &&
             buffer[*b_i] != '\t' && buffer[*b_i] != '\0') {
        Spec->smth_read = true;
        (*b_i)++;
      }
    }
  }
}

void get_str(const char* buffer, int* b_i, char* str, struct scanf_spec* Spec) {
  int bytes_read = 0;
  char ch;

  for (;;) {
    if (Spec->width > bytes_read && !Spec->width) break;
    ch = buffer[(*b_i)++];
    if (ch == '\0' || ch == '\n' || ch == '\t' || ch == ' ') break;
    str[bytes_read++] = ch;
    Spec->smth_read = true;
  }

  str[bytes_read] = '\0';
}

bool get_intenger_number(const char* buffer, int* b_i, struct scanf_spec* Spec,
                         va_list args) {
  bool has_sign = false;
  unsigned long tmp_d;
  tmp_d = read_intenger(buffer, b_i, &has_sign, Spec);
  if (Spec->type == 'u' || Spec->type == 'o' || Spec->type == 'x' ||
      Spec->type == 'X') {
    if (Spec->len_of_type == SHORT_TYPE) {
      if (!Spec->dont_scanf && Spec->smth_read) {
        short unsigned* dn = va_arg(args, short unsigned*);
        *dn = has_sign ? tmp_d * -1 : tmp_d;
      }
    } else if (Spec->len_of_type == LONG_TYPE) {
      if (!Spec->dont_scanf && Spec->smth_read) {
        long unsigned* dn = va_arg(args, long unsigned*);
        *dn = has_sign ? tmp_d * -1 : tmp_d;
      }
    } else if (Spec->len_of_type == DEFOULT_TYPE) {
      if (!Spec->dont_scanf && Spec->smth_read) {
        unsigned* dn = va_arg(args, unsigned*);
        *dn = has_sign ? tmp_d * -1 : tmp_d;
      }
    }
  } else if (Spec->type == 'd' || Spec->type == 'i') {
    if (Spec->len_of_type == SHORT_TYPE) {
      if (!Spec->dont_scanf && Spec->smth_read) {
        short* dn = va_arg(args, short*);
        *dn = has_sign ? tmp_d * -1 : tmp_d;
      }
    } else if (Spec->len_of_type == LONG_TYPE) {
      if (!Spec->dont_scanf && Spec->smth_read) {
        long* dn = va_arg(args, long*);
        *dn = has_sign ? tmp_d * -1 : tmp_d;
      }
    } else if (Spec->len_of_type == DEFOULT_TYPE) {
      if (!Spec->dont_scanf && Spec->smth_read) {
        int* dn = va_arg(args, int*);
        *dn = has_sign ? tmp_d * -1 : tmp_d;
      }
    }
  } else if (Spec->type == 'p') {
    void** pnt = va_arg(args, void**);
    if (!check_for_nil(buffer, b_i)) {
      *pnt = (void*)tmp_d;
    } else {
      Spec->smth_read = true;
      *pnt = S21_NULL;
    }
    tmp_d++;
  }
  return Spec->smth_read;
}

bool check_for_nil(const char* buffer, int* b_i) {
  char* nil = "(nil)";
  bool res = true;
  for (int i = 0; i < 5; i++) {
    if (nil[i] != buffer[*b_i + i]) {
      res = false;
    }
  }
  return res;
}

unsigned long read_intenger(const char* buffer, int* b_i, bool* has_sign,
                            struct scanf_spec* Spec) {
  *has_sign = check_sign(buffer, b_i, Spec);
  unsigned long res = 0;
  if (Spec->type == 'u' || Spec->type == 'd') {
    res = get_decimal_from_buffer(buffer, b_i, Spec);
  } else {
    res = route_by_system(buffer, b_i, Spec);
  }

  return res;
}

unsigned long route_by_system(const char* buffer, int* b_i,
                              struct scanf_spec* Spec) {
  unsigned long res = 0;
  int system = check_system(buffer, b_i);
  if ((Spec->type == 'i' && system == 16) || Spec->type == 'x' ||
      Spec->type == 'X' || Spec->type == 'p') {
    if (system == 16) Spec->width += -2;
    res = get_hex_from_buffer(buffer, b_i, Spec);
  } else if ((Spec->type == 'i' && system == 8) || Spec->type == 'o') {
    if (system == 8) Spec->width += -1;
    res = get_oct_from_buffer(buffer, b_i, Spec);
  } else {
    res = get_decimal_from_buffer(buffer, b_i, Spec);
  }
  return res;
}

unsigned long get_decimal_from_buffer(const char* buffer, int* b_i,
                                      struct scanf_spec* Spec) {
  unsigned long digit = 0;
  unsigned long cur_max = get_current_max(Spec);
  unsigned long up_step =
      (Spec->type == 'd' || Spec->type == 'i') ? __INT64_MAX__ : __UINT64_MAX__;
  int up_step_div = up_step % 10;

  int start_b_i = 0;
  int max_len_of_digit = (Spec->type == 'd' || Spec->type == 'i') ? 19 : 20;
  bool digit_is_overflow = false;

  while (buffer[*b_i] >= '0' && buffer[*b_i] <= '9') {
    Spec->smth_read = true;
    if (!start_b_i && buffer[*b_i] != '0') start_b_i = *b_i;
    if (Spec->width == 0 && Spec->wght_in_spec) break;
    Spec->width--;
    digit_is_overflow =
        (digit > up_step / 10) ||
        (digit == up_step / 10 && buffer[*b_i] - '0' > up_step_div);
    digit = digit * 10 + (buffer[*b_i] - '0');
    if ((start_b_i && *b_i - start_b_i >= max_len_of_digit) ||
        digit_is_overflow) {
      digit = max_len_of_digit == 19 && Spec->len_of_type != LONG_TYPE
                  ? -1UL
                  : cur_max;
      while (buffer[*b_i] >= '0' && buffer[*b_i] <= '9') (*b_i)++;
      break;
    }
    (*b_i)++;
  }

  return digit;
}

long double get_float_from_buffer(const char* buffer, int* b_i,
                                  struct scanf_spec* Spec) {
  long double digit = 0;

  while (buffer[*b_i] >= '0' && buffer[*b_i] <= '9') {
    Spec->smth_read = true;
    if (Spec->width == 0 && Spec->wght_in_spec) break;
    Spec->width--;
    digit = digit * 10 + (buffer[*b_i] - '0');
    (*b_i)++;
  }

  return digit;
}

unsigned long get_oct_from_buffer(const char* buffer, int* b_i,
                                  struct scanf_spec* Spec) {
  unsigned long digit = 0;
  unsigned long cur_max = get_current_max(Spec);
  unsigned long up_step =
      (Spec->type == 'd' || Spec->type == 'i') ? __INT64_MAX__ : __UINT64_MAX__;
  int up_step_div = up_step % 8;
  int start_b_i = 0;
  int max_len_of_digit = (Spec->type == 'd' || Spec->type == 'i') ? 21 : 22;
  bool digit_is_overflow = false;

  while (buffer[*b_i] >= '0' && buffer[*b_i] <= '7') {
    Spec->smth_read = true;
    if (!start_b_i && buffer[*b_i] != '0') start_b_i = *b_i;
    if (Spec->width == 0 && Spec->wght_in_spec) break;
    Spec->width--;
    digit_is_overflow =
        (digit > up_step / 8) ||
        (digit == up_step / 8 && buffer[*b_i] - '0' > up_step_div);
    digit = digit * 8 + (buffer[*b_i] - '0');
    if ((start_b_i && *b_i - start_b_i >= max_len_of_digit) ||
        digit_is_overflow) {
      digit = max_len_of_digit == 21 && Spec->len_of_type != LONG_TYPE
                  ? -1UL
                  : cur_max;
      while (buffer[*b_i] >= '0' && buffer[*b_i] <= '9') (*b_i)++;
      break;
    }
    (*b_i)++;
  }

  return digit;
}

unsigned long get_hex_from_buffer(const char* buffer, int* b_i,
                                  struct scanf_spec* Spec) {
  unsigned long digit = 0;
  unsigned long cur_max = get_current_max(Spec);
  unsigned long up_step =
      (Spec->type == 'd' || Spec->type == 'i') ? __INT64_MAX__ : __UINT64_MAX__;
  int up_step_div = up_step % 16;
  int start_b_i = 0;
  int max_len_of_digit = (Spec->type == 'd' || Spec->type == 'i') ? 15 : 16;
  bool digit_is_overflow = false;
  int last_dgt = 0;

  while (true) {
    Spec->smth_read = true;
    if (!start_b_i && buffer[*b_i] != '0') start_b_i = *b_i;
    if (Spec->width == 0 && Spec->wght_in_spec) break;
    Spec->width--;
    if (buffer[*b_i] >= '0' && buffer[*b_i] <= '9') {
      last_dgt = (buffer[*b_i] - '0');
    } else if (buffer[*b_i] >= 'a' && buffer[*b_i] <= 'f') {
      last_dgt = (buffer[*b_i] - 'a' + 10);
    } else if (buffer[*b_i] >= 'A' && buffer[*b_i] <= 'F') {
      last_dgt = (buffer[*b_i] - 'A' + 10);
    } else {
      break;
    }
    digit_is_overflow = (digit > up_step / 16) ||
                        (digit == up_step / 16 && (last_dgt > up_step_div));
    if ((start_b_i && *b_i - start_b_i >= max_len_of_digit) ||
        digit_is_overflow) {
      digit = max_len_of_digit == 15 && Spec->len_of_type != LONG_TYPE
                  ? -1UL
                  : cur_max;
      break;
    }
    digit = digit * 16 + last_dgt;
    (*b_i)++;
  }

  return digit;
}

unsigned long get_current_max(struct scanf_spec* Spec) {
  unsigned long res;
  if (Spec->type == 'u' || Spec->type == 'o' || Spec->type == 'x' ||
      Spec->type == 'X') {
    switch (Spec->len_of_type) {
      case LONG_TYPE:
        res = __UINT64_MAX__;
        break;
      case SHORT_TYPE:
        res = __UINT16_MAX__;
        break;
      case DEFOULT_TYPE:
        res = __UINT32_MAX__;
        break;
    }
  } else {
    switch (Spec->len_of_type) {
      case LONG_TYPE:
        res = __INT64_MAX__;
        break;
      case SHORT_TYPE:
        res = __INT16_MAX__;
        break;
      case DEFOULT_TYPE:
        res = __INT32_MAX__;
        break;
    }
  }
  return res;
}

int check_system(const char* buffer, int* b_i) {
  int res = 10;
  if (buffer[*b_i] == '0') {
    if (buffer[*b_i + 1] == 'x' || buffer[*b_i + 1] == 'X') {
      res = 16;
      (*b_i)++;
    } else {
      res = 8;
    }
    (*b_i)++;
  }
  return res;
}

bool check_sign(const char* buffer, int* b_i, struct scanf_spec* Spec) {
  bool res = false;
  if (buffer[*b_i] == '-') {
    (*b_i)++;
    res = true;
    Spec->width--;
  } else if (buffer[*b_i] == '+') {
    (*b_i)++;
    Spec->width--;
  }
  return res;
}

void get_float_or_mantissa(const char* buffer, int* b_i,
                           struct scanf_spec* Spec, va_list args) {
  bool has_sign = check_sign(buffer, b_i, Spec);
  if (Spec->len_of_type == DEFOULT_TYPE) {
    float* fn = va_arg(args, float*);
    if (!check_for_nan_or_inf(buffer, b_i, Spec)) {
      *fn = get_float_from_buffer(buffer, b_i, Spec);
      if (step_dot(buffer, b_i, Spec)) {
        *fn += get_fraction_from_buffer(buffer, b_i, Spec);
      }
      *fn = chenge_by_e(buffer, b_i, *fn);
      *fn = has_sign ? *fn * -1 : *fn;
    } else {
      *fn = chose_INF_or_NAN(buffer, b_i, has_sign);
    }
  } else if (Spec->len_of_type == LONG_TYPE) {
    double* fn = va_arg(args, double*);
    if (!check_for_nan_or_inf(buffer, b_i, Spec)) {
      *fn = get_float_from_buffer(buffer, b_i, Spec);
      if (step_dot(buffer, b_i, Spec)) {
        *fn += get_fraction_from_buffer(buffer, b_i, Spec);
      }
      *fn = chenge_by_e(buffer, b_i, *fn);
      *fn = has_sign ? *fn * -1 : *fn;
    } else {
      *fn = chose_INF_or_NAN(buffer, b_i, has_sign);
    }
  } else if (Spec->len_of_type == LONG_D_TYPE) {
    long double* fn = va_arg(args, long double*);
    if (!check_for_nan_or_inf(buffer, b_i, Spec)) {
      *fn = get_float_from_buffer(buffer, b_i, Spec);
      if (step_dot(buffer, b_i, Spec)) {
        *fn += get_fraction_from_buffer(buffer, b_i, Spec);
      }
      *fn = chenge_by_e(buffer, b_i, *fn);
      *fn = has_sign ? *fn * -1 : *fn;
    } else {
      *fn = chose_INF_or_NAN(buffer, b_i, has_sign);
    }
  }
}

void skip_float(const char* buffer, int* b_i, struct scanf_spec* Spec) {
  bool has_sign = check_sign(buffer, b_i, Spec);
  long double fn = 0;
  if (!check_for_nan_or_inf(buffer, b_i, Spec)) {
    fn = get_float_from_buffer(buffer, b_i, Spec);
    if (step_dot(buffer, b_i, Spec)) {
      fn += get_fraction_from_buffer(buffer, b_i, Spec);
    }
    fn = chenge_by_e(buffer, b_i, fn);
    fn = has_sign ? fn * -1 : fn;
  } else {
    fn = chose_INF_or_NAN(buffer, b_i, has_sign);
  }
}

long double chenge_by_e(const char* buffer, int* b_i, long double fn) {
  if (buffer[*b_i] == 'e' || buffer[*b_i] == 'E') {
    (*b_i)++;
    bool has_minus = buffer[(*b_i)++] == '-';
    int exp = get_digit_from_str(buffer, b_i);
    if (has_minus) {
      while (exp != 0) {
        fn /= 10;
        exp--;
      }
    } else {
      while (exp != 0) {
        fn *= 10;
        exp--;
      }
    }
  }
  return fn;
}

float chose_INF_or_NAN(const char* buffer, int* b_i, bool has_sign) {
  float res;
  if (buffer[*b_i - 1] == 'n' || buffer[*b_i - 1] == 'N') {
    res = has_sign ? -NAN : NAN;
  } else {
    res = has_sign ? -INFINITY : INFINITY;
  }
  return res;
}

bool check_for_nan_or_inf(const char* buffer, int* b_i,
                          struct scanf_spec* Spec) {
  bool res = false;
  if (buffer[*b_i] == 'i' || buffer[*b_i] == 'I') {
    (*b_i)++;
    if (buffer[*b_i] == 'n' || buffer[*b_i] == 'N') {
      (*b_i)++;
      if (buffer[*b_i] == 'f' || buffer[*b_i] == 'F') {
        (*b_i)++;
        Spec->smth_read = true;
      }
    }
    res = true;
  } else if (buffer[*b_i] == 'n' || buffer[*b_i] == 'N') {
    (*b_i)++;
    if (buffer[*b_i] == 'a' || buffer[*b_i] == 'A') {
      (*b_i)++;
      if (buffer[*b_i] == 'n' || buffer[*b_i] == 'N') {
        (*b_i)++;
        Spec->smth_read = true;
      }
    }
    res = true;
  }
  return res;
}

long double get_fraction_from_buffer(const char* buffer, int* b_i,
                                     struct scanf_spec* Spec) {
  int tmp_b_i;
  long double fractional_part = 0;
  while (buffer[*b_i] >= '0' && buffer[*b_i] <= '9') {
    if (Spec->width - 1 == 0) break;
    Spec->width--;
    (*b_i)++;
  }
  Spec->width--;
  tmp_b_i = (*b_i) - 1;
  while (buffer[tmp_b_i] >= '0' && buffer[tmp_b_i] <= '9') {
    if (Spec->width - 1 == 0) break;
    Spec->width--;
    fractional_part = (fractional_part + (buffer[tmp_b_i] - '0')) / 10;
    tmp_b_i--;
  }
  return fractional_part;
}

bool step_dot(const char* buffer, int* b_i, struct scanf_spec* Spec) {
  bool has_fraction = false;

  if (buffer[*b_i] == '.') {
    Spec->width--;
    (*b_i)++;
    has_fraction = true;
  }

  return has_fraction;
}

int get_digit_from_str(const char* str, int* str_i) {
  int digit = 0;

  while (str[*str_i] >= '0' && str[*str_i] <= '9') {
    digit = digit * 10 + (str[*str_i] - '0');
    (*str_i)++;
  }

  (*str_i)--;
  return digit;
}

void put_number_of_char_scanf(int b_i, struct scanf_spec Spec, va_list args) {
  if (Spec.len_of_type == LONG_TYPE) {
    long int* d = va_arg(args, long int*);
    *d = b_i;
  } else if (Spec.len_of_type == SHORT_TYPE) {
    short int* d = va_arg(args, short int*);
    *d = b_i;
  } else {
    int* d = va_arg(args, int*);
    *d = b_i;
  }
}