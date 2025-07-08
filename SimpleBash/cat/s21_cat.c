#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_OF_LINE 1024

struct arguments {
  int count;
  char* path;
  bool v;  // Отоброжение непечатных символов
  bool e;  // '\n' => '$'
  bool n;  // Нумерация строк
  bool b;  // Нумерация непустых строк
  bool t;  // '\t' => '^I'
  bool s;  // Сокращение нескольких пустых строк
};

struct file {
  FILE* file;
  char* line;
  unsigned long len_of_line;
  unsigned long long number_of_lines;
  bool last_line_is_empty;
};

bool try_and_prepair_struct(struct arguments*, struct file*, char*[], int);
void parse_args(char*[], struct arguments*);
void parse_flags(char*, struct arguments*);
bool try_and_open_file(struct arguments, struct file*);
bool try_and_make_memoryspace_for_line(struct file*);
void route_with_flags(struct file*, struct arguments);
void using_flag_s(struct file*);
void get_number_to_line(struct file*, struct arguments);
char* insert_into_string(char*, char, int);
void change_nonprinting_symbols(struct file*, struct arguments);
void clear_memory(struct file);
bool line_is_empty(char*);
bool try_and_resize_line(struct file*);
int count_digits_logarithmic(unsigned long long);
bool try_and_realloc_lines(struct file*, char**);

int main(int argc, char* argv[]) {
  struct arguments Args;
  struct file File;

  if (argc >= 2) {
    bool preparing_is_sucsess =
        try_and_prepair_struct(&Args, &File, argv, argc);

    if (preparing_is_sucsess) {
      route_with_flags(&File, Args);
      clear_memory(File);
    }
  }

  return 0;
}

bool try_and_prepair_struct(struct arguments* Args, struct file* File,
                            char* argv[], int argc) {
  bool all_is_sucsess = true;
  memset(Args, 0, sizeof(struct arguments));
  memset(File, 0, sizeof(struct arguments));
  Args->count = argc;

  parse_args(argv, Args);

  File->len_of_line = 1024;
  File->number_of_lines = 1ULL;
  File->last_line_is_empty = false;
  all_is_sucsess = try_and_open_file(*Args, File);
  all_is_sucsess = all_is_sucsess && try_and_make_memoryspace_for_line(File);

  return all_is_sucsess;
}

void parse_args(char* args[], struct arguments* Args) {
  if (Args->count == 2) {
    Args->path = args[1];
  } else {
    parse_flags(args[1], Args);
    Args->path = args[2];
  }
}

void parse_flags(char* flags, struct arguments* Args) {
  if (flags[1] == '-') {
    if (strcmp(flags, "--number-nonblank") == 0) {
      Args->b = true;
    } else if (strcmp(flags, "--number") == 0) {
      Args->n = true;
    } else if (strcmp(flags, "--squeeze-blank") == 0) {
      Args->s = true;
    } else {
      printf("Такого флага не существует\n");
    }
  } else {
    for (int i = 0; i < (int)strlen(flags) - 1; i++) {
      switch (flags[i + 1]) {
        case 'v':
          Args->v = true;
          break;
        case 'n':
          Args->n = true;
          break;
        case 'b':
          Args->b = true;
          break;
        case 't':
          Args->t = true;
          Args->v = true;
          break;
        case 'e':
          Args->e = true;
          Args->v = true;
          break;
        case 's':
          Args->s = true;
          break;
        case 'T':
          Args->t = true;
          break;
        case 'E':
          Args->e = true;
          break;
        default:
          printf("Такого флага не существует\n");
          break;
      }
    }
  }
}

bool try_and_open_file(struct arguments Args, struct file* File) {
  bool res = true;
  File->file = fopen(Args.path, "r");

  if (File->file == NULL) {
    printf("s21_cat: %s: Не удалось прочитать файл\n", Args.path);
    res = false;
  }

  return res;
}

bool try_and_make_memoryspace_for_line(struct file* File) {
  File->len_of_line = LEN_OF_LINE;
  bool res = true;

  File->line = calloc(File->len_of_line, sizeof(char));

  if (File->line == NULL) {
    printf("Не удалось выделить память для строки\n");
    res = false;
  }

  return res;
}

void route_with_flags(struct file* File, struct arguments Args) {
  while (fgets(File->line, File->len_of_line, File->file)) {
    if (strlen(File->line) == File->len_of_line - 1) {
      if (!try_and_resize_line(File)) {
        break;
      }
    }
    if (Args.s) {
      using_flag_s(File);
    }
    if (Args.b || Args.n) {
      get_number_to_line(File, Args);
    }
    if (Args.e || Args.t || Args.v) {
      change_nonprinting_symbols(File, Args);
    }
    printf("%s", File->line);
    memset(File->line, 0, File->len_of_line);
  }
}

bool try_and_resize_line(struct file* File) {
  char* tmp_line = calloc(File->len_of_line, sizeof(char));
  bool res = true;

  do {
    if (!try_and_realloc_lines(File, &tmp_line)) {
      res = false;
      break;
    }
    fgets(tmp_line, File->len_of_line, File->file);
    strcat(File->line, tmp_line);
    File->len_of_line *= 2;
  } while (strlen(tmp_line) == File->len_of_line / 2 - 1);
  free(tmp_line);

  return res;
}

bool try_and_realloc_lines(struct file* File, char** tmp_line) {
  bool res = true;
  char* new_tmp_line = realloc(*tmp_line, sizeof(char) * File->len_of_line);
  char* new_line = realloc(File->line, sizeof(char) * File->len_of_line * 2);

  if (new_tmp_line == NULL || new_line == NULL) {
    printf("Не удалось увеличить память для строки\n");
    res = false;
  } else {
    *tmp_line = new_tmp_line;
    File->line = new_line;
  }

  return res;
}

void get_number_to_line(struct file* File, struct arguments Args) {
  if (File->line[0] != '\0') {
    if (!Args.b || !line_is_empty(File->line)) {
      int i = 6 - count_digits_logarithmic(File->number_of_lines);
      while (i > 0) {
        printf(" ");
        i--;
      }
      printf("%llu\t", File->number_of_lines);
      File->number_of_lines += 1;
    }
  }
}

int count_digits_logarithmic(unsigned long long num) {
  return floor(log10(num)) + 1;
}

void using_flag_s(struct file* File) {
  if (line_is_empty(File->line)) {
    if (File->last_line_is_empty) {
      File->line[0] = '\0';
    } else {
      File->last_line_is_empty = true;
    }
  } else {
    File->last_line_is_empty = false;
  }
}

bool line_is_empty(char* line) {
  bool res = false;

  if (line[0] == '\n') {
    res = true;
  }

  return res;
}

void change_nonprinting_symbols(struct file* File, struct arguments Args) {
  char* line = File->line;

  for (int i = 0; line[i] != '\0'; i++) {
    if (((line[i] >= 0 && line[i] <= 8) || (line[i] >= 11 && line[i] <= 31) ||
         line[i] == 127) &&
        Args.v) {
      insert_into_string(line, (char)((line[i] + 64) % 128), i);
    } else if (Args.e && line[i] == 10) {
      line[i] = '$';
      line[i + 1] = '\n';
      line[i + 2] = '\0';
      break;
    } else if (Args.t && line[i] == 9) {
      insert_into_string(line, (char)(line[i] + 64), i);
    }
  }
}

char* insert_into_string(char* line, char code, int pos) {
  int l = (int)strlen(line) + 1;

  for (; l != pos; l--) {
    line[l] = line[l - 1];
  }
  line[pos] = '^';
  line[pos + 1] = (char)code;

  return line;
}

void clear_memory(struct file File) {
  free(File.line);
  fclose(File.file);
}