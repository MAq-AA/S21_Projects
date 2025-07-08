#include "s21_string.h"

#define NODIGIT -1
#define MAX_integer_LENGHT 21

#define DONT_SHOW 0
#define ONLY_MINUS 1
#define MINUS_AND_SPACE 2
#define MINUS_AND_PLUS 3

#define DEFOULT_TYPE 0
#define SHORT_TYPE 1
#define LONG_TYPE 2
#define LONG_D_TYPE 3

#define ONCE_FREC_LEN 18

struct specificator {
  char type;
  bool left_aligement;
  bool show_zeros_or_system;
  bool add_zeros;
  int width;
  int how_to_show_sign;
  int precision;
  int len_of_type;
  bool wchar_is_using;
  bool precision_in_spec;
  int mantis;
};

int get_mantis(long double* d);
int s21_wctomb(char* s, s21_wchar_t wc);
bool spec_type(char, struct specificator*);
int get_digit(const char* format, int* f_i);
bool parse_flags(char, struct specificator*);
void prepare_Spec(struct specificator* Spec);
void put_res(char* buffer, int* b_i, char* res);
void delete_useless_zeros(char* buffer, int* b_i, struct specificator* Spec);
void put_system(char* buffer, int* b_i, char type);
void shift_buffer(char* buffer, int* b_i, int shift, int width);
void put_space(char* buffer, int*, int wight, bool add_zeros);
bool put_specificator(char*, const char*, int*, int*, va_list);
void parse_digit(const char*, int*, bool, struct specificator*);
bool parse_specificator(const char*, int*, struct specificator*);
void get_wight_and_precision(struct specificator* Spec, va_list args);
void route_by_specificator(char*, int*, struct specificator*, va_list);
void put_number_of_char(int b_i, struct specificator Spec, va_list args);
void delete_useless_char(char* buffer, int* b_i, struct specificator* Spec);
void longDoubleToStr(char* buffer, int* b_i, long double num, int precision);
unsigned long convert_integer_to_int(long double* fractional_part,
                                     int precision);
void chose_e_or_f(char* buffer, int* b_i, struct specificator* Spec,
                  va_list args);
unsigned long convert_fraction_to_int(long double* fractional_part,
                                      int* precision);
void put_super_long_integer_to_buffer(char* buffer, int* b_i,
                                      long double int_part);
bool check_for_inf_nan(char* buffer, int* b_i, long double d,
                       struct specificator* Spec);
void put_string_in_buffer(char* buffer, int* b_i, struct specificator* Spec,
                          va_list args);
void put_double_in_buffer(char* buffer, int* b_i, struct specificator* Spec,
                          va_list args);
void parse_double_and_put(char* buffer, int* b_i, long double d,
                          struct specificator* Spec);
void put_mantis_in_buffer(char* buffer, int* b_i, long double d,
                          struct specificator* Spec);
void put_intenger_in_buffer(char* buffer, int* b_i, struct specificator* Spec,
                            va_list args);
int put_wchar(char* buffer, int* b_i, char* mbchar, wchar_t wstr,
              struct specificator* Spec);
void put_with_wight_and_system(char* buffer, int*, char* res, int width,
                               struct specificator Spec);
void put_integer_in_substr(char substr[], int* pos, unsigned long digit,
                           struct specificator Spec);
void intenger_to_string_and_put(char* buffer, int* b_i, unsigned long integer,
                                struct specificator Spec, bool is_signed);

int s21_sprintf(char* buffer, const char* format, ...) {
  int format_index = 0;
  int buffer_index = 0;
  char c = format[format_index];
  va_list args;
  va_start(args, format);
  bool wchar_is_using;

  while (c != '\0') {
    if (c == '%') {
      wchar_is_using =
          put_specificator(buffer, format, &buffer_index, &format_index, args);
    } else {
      buffer[buffer_index++] = c;
    }
    c = format[++format_index];
  }

  buffer[buffer_index] = '\0';
  va_end(args);

  return wchar_is_using ? -1 : (int)s21_strlen(buffer);
}

bool put_specificator(char* buffer, const char* format, int* b_i, int* f_i,
                      va_list args) {
  struct specificator Spec;
  s21_memset(&Spec, 0, sizeof(struct specificator));

  if (format[++(*f_i)] != '%') {
    if (parse_specificator(format, f_i, &Spec)) {
      if (Spec.width == -1 || Spec.precision == -1) {
        get_wight_and_precision(&Spec, args);
      }
      prepare_Spec(&Spec);
      route_by_specificator(buffer, b_i, &Spec, args);
    } else {
      while (format[*f_i] != '%') {
        (*f_i)--;
      }
      (*f_i)++;
      buffer[(*b_i)++] = '%';
    }
  } else {
    buffer[(*b_i)++] = format[*f_i];
  }

  return Spec.wchar_is_using;
}

bool parse_specificator(const char* format, int* f_i,
                        struct specificator* Spec) {
  bool next_is_precision = false;
  char cur_symb = format[(*f_i)];
  bool all_success = true;

  while (true) {
    if (cur_symb != '.') {
      if (((cur_symb > '0' || next_is_precision) && cur_symb <= '9') ||
          cur_symb == '*') {
        parse_digit(format, f_i, next_is_precision, Spec);
      } else {
        if (!spec_type(cur_symb, Spec)) {
          if (!parse_flags(cur_symb, Spec)) {
            all_success = false;
            break;
          }
        } else {
          break;
        }
      }
    } else {
      next_is_precision = true;
    }
    cur_symb = format[++(*f_i)];
  }

  return Spec->type && all_success;
}

bool spec_type(char c, struct specificator* Spec) {
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

bool parse_flags(char c, struct specificator* Spec) {
  bool res = true;
  switch (c) {
    case '-':
      Spec->left_aligement = true;
      break;
    case '+':
      Spec->how_to_show_sign = MINUS_AND_PLUS;
      break;
    case ' ':
      Spec->how_to_show_sign = MINUS_AND_SPACE;
      break;
    case '#':
      Spec->show_zeros_or_system = true;
      break;
    case '0':
      Spec->add_zeros = true;
      break;
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

void parse_digit(const char* format, int* f_i, bool is_precision,
                 struct specificator* Spec) {
  if (!is_precision) {
    Spec->width = get_digit(format, f_i);
  } else {
    Spec->precision = get_digit(format, f_i);
    Spec->precision_in_spec = true;
  }
}

int get_digit(const char* format, int* f_i) {
  int digit = 0;
  while (format[*f_i] >= '0' && format[*f_i] <= '9') {
    digit = digit * 10 + (format[*f_i] - '0');
    (*f_i)++;
  }

  if (format[*f_i] == '*') {
    digit = NODIGIT;
  } else {
    (*f_i)--;
  }

  return digit;
}

void get_wight_and_precision(struct specificator* Spec, va_list args) {
  while (true) {
    if (Spec->width == -1) {
      Spec->width = va_arg(args, int);
    } else if (Spec->precision == -1) {
      Spec->precision = va_arg(args, int);
    } else {
      break;
    }
  }
}

void prepare_Spec(struct specificator* Spec) {
  if (Spec->type == 'u') {
    Spec->show_zeros_or_system = false;
    Spec->how_to_show_sign = DONT_SHOW;
  } else if (Spec->type == 'X' || Spec->type == 'x' || Spec->type == 'o') {
    Spec->how_to_show_sign = DONT_SHOW;
  } else if (Spec->type == 'p' || Spec->type == 's' || Spec->type == 'c') {
    Spec->how_to_show_sign = DONT_SHOW;
    Spec->show_zeros_or_system = true;
  } else if (Spec->type == 'g' || Spec->type == 'G' || Spec->type == 'E' ||
             Spec->type == 'e' || Spec->type == 'f') {
    Spec->precision = Spec->precision_in_spec ? Spec->precision : 6;
    if (Spec->type == 'g' || Spec->type == 'G') {
      Spec->precision = Spec->precision ? Spec->precision - 1 : 5;
    }
  }
  if (Spec->left_aligement) {
    Spec->add_zeros = false;
  }
}

void route_by_specificator(char* buffer, int* b_i, struct specificator* Spec,
                           va_list args) {
  if (Spec->type == 'f') {
    put_double_in_buffer(buffer, b_i, Spec, args);
  } else if (Spec->type == 'g' || Spec->type == 'G' || Spec->type == 'e' ||
             Spec->type == 'E') {
    chose_e_or_f(buffer, b_i, Spec, args);
  } else if (Spec->type == 's' || Spec->type == 'c') {
    put_string_in_buffer(buffer, b_i, Spec, args);
  } else if (Spec->type == 'n') {
    put_number_of_char(*b_i, *Spec, args);
  } else {
    put_intenger_in_buffer(buffer, b_i, Spec, args);
  }
}

void chose_e_or_f(char* buffer, int* b_i, struct specificator* Spec,
                  va_list args) {
  if (Spec->len_of_type == LONG_D_TYPE) {
    long double d = va_arg(args, long double);
    if (!check_for_inf_nan(buffer, b_i, d, Spec)) {
      put_mantis_in_buffer(buffer, b_i, d, Spec);
    }
  } else {
    double d = va_arg(args, double);
    if (!check_for_inf_nan(buffer, b_i, d, Spec)) {
      put_mantis_in_buffer(buffer, b_i, d, Spec);
    }
  }
}

bool check_for_inf_nan(char* buffer, int* b_i, long double d,
                       struct specificator* Spec) {
  bool res = false;
  if (isinf(d)) {
    Spec->width += Spec->how_to_show_sign != DONT_SHOW || signbit(d) ? -4 : -3;
    put_space(buffer, b_i, Spec->width, false);
    if (signbit(d)) {
      buffer[(*b_i)++] = '-';
      buffer[*b_i] = '\0';
      s21_strncat(buffer, "inf", 3);
      *b_i += 3;
    } else {
      if (Spec->how_to_show_sign == MINUS_AND_SPACE) {
        buffer[(*b_i)++] = ' ';
      } else if (Spec->how_to_show_sign == MINUS_AND_PLUS) {
        buffer[(*b_i)++] = '+';
      }
      buffer[*b_i] = '\0';
      s21_strncat(buffer, "inf", 3);
      *b_i += 3;
    }
    res = true;
  } else if (isnan(d)) {
    Spec->width += Spec->how_to_show_sign != DONT_SHOW || signbit(d) ? -4 : -3;
    put_space(buffer, b_i, Spec->width, false);
    if (signbit(d)) {
      buffer[(*b_i)++] = '-';
      buffer[*b_i] = '\0';
      s21_strncat(buffer, "nan", 3);
      *b_i += 3;
    } else {
      if (Spec->how_to_show_sign == MINUS_AND_SPACE) {
        buffer[(*b_i)++] = ' ';
      } else if (Spec->how_to_show_sign == MINUS_AND_PLUS) {
        buffer[(*b_i)++] = '+';
      }
      buffer[*b_i] = '\0';
      s21_strncat(buffer, "nan", 3);
      *b_i += 3;
    }
    res = true;
  }

  return res;
}

void put_mantis_in_buffer(char* buffer, int* b_i, long double d,
                          struct specificator* Spec) {
  long double tmp_d = d;
  int mantis = get_mantis(&d);
  Spec->mantis = mantis;
  if (signbit(tmp_d)) d *= -1;

  if (Spec->type == 'e' || Spec->type == 'E' ||
      (mantis < -4 || mantis > Spec->precision)) {
    parse_double_and_put(buffer, b_i, d, Spec);
  } else {
    Spec->precision =
        mantis > 0 ? Spec->precision - (mantis + 1) : Spec->precision - mantis;
    Spec->mantis = 0;
    parse_double_and_put(buffer, b_i, tmp_d, Spec);
  }
}

void put_mantis(char* buffer, int* b_i, struct specificator* Spec) {
  if (Spec->type == 'e' || Spec->type == 'E' ||
      (Spec->mantis < -4 || Spec->mantis > Spec->precision)) {
    buffer[(*b_i)++] = Spec->type == 'E' || Spec->type == 'G' ? 'E' : 'e';
    buffer[(*b_i)++] = Spec->mantis < 0 ? '-' : '+';
    Spec->mantis *= Spec->mantis < 0 ? -1 : 1;
    struct specificator tmp_spec = {0};
    tmp_spec.precision = 2;
    intenger_to_string_and_put(buffer, b_i, Spec->mantis, tmp_spec, false);
  }
}

int get_mantis(long double* d) {
  *d = *d < 0 ? -(*d) : *d;
  int mantis = 0;
  while (*d < 1 || *d >= 10) {
    if (*d < 1) {
      *d *= 10;
      mantis--;
    } else {
      *d /= 10;
      mantis++;
    }
  }
  return mantis;
}

void put_double_in_buffer(char* buffer, int* b_i, struct specificator* Spec,
                          va_list args) {
  if (Spec->len_of_type == LONG_D_TYPE) {
    long double d = va_arg(args, long double);
    if (!check_for_inf_nan(buffer, b_i, d, Spec)) {
      parse_double_and_put(buffer, b_i, d, Spec);
    }
  } else {
    double d = va_arg(args, double);
    if (!check_for_inf_nan(buffer, b_i, d, Spec)) {
      parse_double_and_put(buffer, b_i, d, Spec);
    }
  }
}

void parse_double_and_put(char* buffer, int* b_i, long double value,
                          struct specificator* Spec) {
  int tmp_b_i = *b_i;
  if (!signbit(value)) {
    buffer[(*b_i)++] = Spec->how_to_show_sign == MINUS_AND_PLUS    ? '+'
                       : Spec->how_to_show_sign == MINUS_AND_SPACE ? ' '
                                                                   : '\0';
    if (Spec->how_to_show_sign == DONT_SHOW) (*b_i)--;
  }
  longDoubleToStr(buffer, b_i, value, Spec->precision);
  delete_useless_char(buffer, b_i, Spec);
  put_mantis(buffer, b_i, Spec);
  Spec->width -= *b_i - tmp_b_i;
  if (Spec->left_aligement && Spec->width > 0) {
    put_space(buffer, b_i, Spec->width, false);
  } else if (!Spec->left_aligement && Spec->width > 0) {
    shift_buffer(buffer, b_i, Spec->width, *b_i - tmp_b_i);
  }
}

void longDoubleToStr(char* buffer, int* b_i, long double num, int precision) {
  bool is_negative = signbit(num);
  num = is_negative ? -num : num;

  if (precision == 0) {
    num = roundl(num);
  }

  long double int_part;
  long double frac_part = modfl(num, &int_part);

  if (is_negative) {
    buffer[(*b_i)++] = '-';
  }

  if (int_part < 1.0L) {
    buffer[(*b_i)++] = '0';
  } else {
    int n_digits = (int)floorl(log10l(int_part)) + 1;
    char int_buf[500];
    int int_len = 0;
    long double temp = int_part;

    for (int i = n_digits - 1; i >= 0; i--) {
      long double factor = powl(10.0L, i);
      int digit = (int)(temp / factor);
      temp -= digit * factor;
      int_buf[int_len++] = '0' + digit;
    }
    for (int i = 0; i < int_len; i++) {
      buffer[(*b_i)++] = int_buf[i];
    }
  }
  buffer[(*b_i)++] = '.';
  if (precision > 0) {
    int digit;
    for (int i = 0; i < precision; i++) {
      frac_part *= 10.0L;
      if (i == precision - 1) {
        digit = (int)rint(frac_part);
      } else {
        digit = (int)frac_part;
      }
      frac_part -= digit;
      buffer[(*b_i)++] = '0' + digit;
    }
  }
}

void delete_useless_char(char* buffer, int* b_i, struct specificator* Spec) {
  if (Spec->type != 'f' && Spec->type != 'e' && Spec->type != 'E') {
    delete_useless_zeros(buffer, b_i, Spec);
  }

  if (*b_i > 0 && buffer[*b_i - 1] == '.' && !Spec->show_zeros_or_system) {
    buffer[--(*b_i)] = '\0';
  }
}

void delete_useless_zeros(char* buffer, int* b_i, struct specificator* Spec) {
  while (*b_i > 0 && buffer[*b_i - 1] == '0' && !Spec->show_zeros_or_system) {
    buffer[--(*b_i)] = '\0';
  }
}

void put_number_of_char(int b_i, struct specificator Spec, va_list args) {
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

void put_string_in_buffer(char* buffer, int* b_i, struct specificator* Spec,
                          va_list args) {
  if (Spec->type == 'c') {
    if (Spec->len_of_type == LONG_TYPE) {
      s21_wchar_t wc = va_arg(args, s21_wchar_t);
      char mbchar[MB_CUR_MAX];
      if (Spec->left_aligement) {
        put_wchar(buffer, b_i, mbchar, wc, Spec);
        put_space(buffer, b_i, Spec->width - 1, false);
      } else {
        put_space(buffer, b_i, Spec->width - 1, false);
        put_wchar(buffer, b_i, mbchar, wc, Spec);
      }
    } else {
      char c = va_arg(args, int);
      if (Spec->left_aligement) {
        buffer[(*b_i)++] = c;
        put_space(buffer, b_i, Spec->width - 1, false);
      } else {
        put_space(buffer, b_i, Spec->width - 1, false);
        buffer[(*b_i)++] = c;
      }
    }
  } else if (Spec->type == 's') {
    int str_len = 0;
    int tmp_b_i = *b_i;
    if (Spec->len_of_type == LONG_TYPE) {
      s21_wchar_t* wstr = va_arg(args, s21_wchar_t*);
      wstr = !wstr && (Spec->precision > 5 || !Spec->precision_in_spec)
                 ? L"(null)"
             : !wstr ? L""
                     : wstr;
      char mbchar[MB_CUR_MAX];
      for (int i = 0; wstr[i] != L'\0' &&
                      (Spec->precision > 0 || !Spec->precision_in_spec);
           i++) {
        Spec->precision -= put_wchar(buffer, b_i, mbchar, wstr[i], Spec);
        str_len = *b_i - tmp_b_i;
      }
    } else {
      char* str = va_arg(args, char*);
      str = !str && (Spec->precision > 5 || !Spec->precision_in_spec) ? "(null)"
            : !str                                                    ? ""
                                                                      : str;
      for (int i = 0;
           str[i] != '\0' && (Spec->precision > 0 || !Spec->precision_in_spec);
           i++) {
        buffer[(*b_i)++] = str[i];
        str_len = i + 1;
        Spec->precision--;
      }
    }
    if (Spec->left_aligement && Spec->width - str_len > 0) {
      put_space(buffer, b_i, Spec->width - str_len, false);
    } else if (Spec->width - str_len > 0) {
      shift_buffer(buffer, b_i, Spec->width - str_len, str_len);
    }
  }
}

int put_wchar(char* buffer, int* b_i, char* mbchar, wchar_t wstr,
              struct specificator* Spec) {
  int len = s21_wctomb(mbchar, wstr);
  if (len < 0) Spec->wchar_is_using = true;
  if (len > 0) {
    for (int j = 0; j < len; j++) {
      buffer[(*b_i)++] = mbchar[j];
    }
  }
  return len == -1 ? Spec->precision : len;
}

void put_intenger_in_buffer(char* buffer, int* b_i, struct specificator* Spec,
                            va_list args) {
  bool has_sign = false;
  if (Spec->type == 'd' || Spec->type == 'i') {
    if (Spec->len_of_type == LONG_TYPE) {
      long int d = va_arg(args, long int);
      has_sign = d < 0;
      d = has_sign ? -1 * d : d;
      intenger_to_string_and_put(buffer, b_i, d, *Spec, has_sign);
    } else if (Spec->len_of_type == SHORT_TYPE) {
      short int d = va_arg(args, int);
      has_sign = d < 0;
      d = has_sign ? -1 * d : d;
      intenger_to_string_and_put(buffer, b_i, d, *Spec, has_sign);
    } else {
      int d = va_arg(args, int);
      has_sign = d < 0;
      d = has_sign ? -1 * d : d;
      intenger_to_string_and_put(buffer, b_i, d, *Spec, has_sign);
    }
  } else if (Spec->type == 'u' || Spec->type == 'o' || Spec->type == 'x' ||
             Spec->type == 'X') {
    if (Spec->len_of_type == LONG_TYPE) {
      unsigned long int d = va_arg(args, unsigned long int);
      intenger_to_string_and_put(buffer, b_i, d, *Spec, has_sign);
    } else if (Spec->len_of_type == SHORT_TYPE) {
      unsigned short int d = va_arg(args, unsigned int);
      intenger_to_string_and_put(buffer, b_i, d, *Spec, has_sign);
    } else {
      unsigned int d = va_arg(args, unsigned int);
      intenger_to_string_and_put(buffer, b_i, d, *Spec, has_sign);
    }
  } else if (Spec->type == 'p') {
    unsigned long int d = (unsigned long int)va_arg(args, void*);
    if ((void*)d == S21_NULL) {
      buffer[*b_i] = '\0';
      s21_strncat(buffer, "(nil)", 5);
      *b_i += 5;
    } else {
      intenger_to_string_and_put(buffer, b_i, d, *Spec, has_sign);
    }
  }
}

void intenger_to_string_and_put(char* buffer, int* b_i, unsigned long integer,
                                struct specificator Spec, bool is_signed) {
  int len =
      Spec.precision > MAX_integer_LENGHT ? Spec.precision : MAX_integer_LENGHT;
  char substr[len + 1];
  substr[len] = '\0';
  s21_memset(substr, '\0', len + 1);

  char* res = substr;
  int pos = len;

  put_integer_in_substr(substr, &pos, integer, Spec);

  while (pos > 0) {
    if (len - pos < Spec.precision) {
      substr[--pos] = '0';
    } else {
      break;
    }
  }

  if ((Spec.how_to_show_sign != DONT_SHOW || is_signed) &&
      (!Spec.add_zeros || Spec.width <= Spec.precision)) {
    substr[--pos] = is_signed                                 ? '-'
                    : Spec.how_to_show_sign == MINUS_AND_PLUS ? '+'
                                                              : ' ';
  }

  res += pos;

  int len_of_space = Spec.width - (len - pos);
  put_with_wight_and_system(buffer, b_i, res, len_of_space, Spec);

  if ((Spec.how_to_show_sign != DONT_SHOW || is_signed) &&
      (Spec.add_zeros && Spec.width > Spec.precision)) {
    buffer[*b_i - Spec.width] = is_signed                                 ? '-'
                                : Spec.how_to_show_sign == MINUS_AND_PLUS ? '+'
                                                                          : ' ';
  }
}

void put_integer_in_substr(char substr[], int* pos, unsigned long integer,
                           struct specificator Spec) {
  char* ox = "0123456789ABCDEF";
  char* oxs = "0123456789abcdef";
  do {
    if (Spec.type == 'X') {
      substr[--(*pos)] = ox[integer % 16];
      integer /= 16;
    } else if (Spec.type == 'x' || Spec.type == 'p') {
      substr[--(*pos)] = oxs[integer % 16];
      integer /= 16;
    } else if (Spec.type == 'o') {
      substr[--(*pos)] = ox[integer % 8];
      integer /= 8;
    } else {
      substr[--(*pos)] = (integer % 10) + '0';
      integer /= 10;
    }
  } while (integer > 0);
}

void put_with_wight_and_system(char* buffer, int* b_i, char* res, int wight,
                               struct specificator Spec) {
  bool left_aligement = Spec.left_aligement;
  char type = Spec.show_zeros_or_system ? Spec.type : '\0';
  char put_zeros = Spec.add_zeros && !Spec.precision_in_spec;
  wight -= type == 'o' ? 1 : type ? 2 : 0;
  if (wight > 0) {
    if (left_aligement) {
      put_system(buffer, b_i, type);
      put_res(buffer, b_i, res);
      put_space(buffer, b_i, wight, put_zeros);
    } else {
      put_space(buffer, b_i, wight, put_zeros);
      put_system(buffer, b_i, type);
      put_res(buffer, b_i, res);
    }
  } else {
    put_system(buffer, b_i, type);
    put_res(buffer, b_i, res);
  }
}

void put_system(char* buffer, int* b_i, char type) {
  if (type == 'o') {
    buffer[(*b_i)++] = '0';
  } else if (type == 'x' || type == 'p') {
    buffer[(*b_i)++] = '0';
    buffer[(*b_i)++] = 'x';
  } else if (type == 'X') {
    buffer[(*b_i)++] = '0';
    buffer[(*b_i)++] = 'X';
  }
  buffer[*b_i] = '\0';
}

void put_res(char* buffer, int* b_i, char* res) {
  s21_strncat(buffer, res, s21_strlen(res));
  *b_i += s21_strlen(res);
}

void put_space(char* buffer, int* b_i, int wight, bool put_zeros) {
  char space[wight + 1];
  space[wight] = '\0';
  for (int i = 0; i < wight; i++) {
    if (put_zeros) {
      space[i] = '0';
    } else {
      space[i] = ' ';
    }
  }
  buffer[*b_i] = '\0';
  s21_strncat(buffer, space, s21_strlen(space));
  *b_i += wight > 0 ? wight : 0;
}

void shift_buffer(char* buffer, int* b_i, int shift, int width) {
  for (int i = 0; i <= width; i++) {
    buffer[(*b_i) - i + shift] = buffer[(*b_i) - i];
  }
  *b_i += shift;
  while (shift) {
    buffer[(*b_i) - (width + shift)] = ' ';
    shift--;
  }
}

int s21_wctomb(char* s, s21_wchar_t wc) {
  int res = -1;

  if (wc <= 0x7F) {
    s[0] = (char)wc;
    res = 1;
  } else if (wc <= 0x7FF) {
    s[0] = (char)(0xC0 | ((wc >> 6) & 0x1F));
    s[1] = (char)(0x80 | (wc & 0x3F));
    res = 2;
  } else if (wc <= 0xFFFF) {
    s[0] = (char)(0xE0 | ((wc >> 12) & 0x0F));
    s[1] = (char)(0x80 | ((wc >> 6) & 0x3F));
    s[2] = (char)(0x80 | (wc & 0x3F));
    res = 3;
  } else if (wc <= 0x10FFFF) {
    s[0] = (char)(0xF0 | ((wc >> 18) & 0x07));
    s[1] = (char)(0x80 | ((wc >> 12) & 0x3F));
    s[2] = (char)(0x80 | ((wc >> 6) & 0x3F));
    s[3] = (char)(0x80 | (wc & 0x3F));
    res = 4;
  }

  return res;
}