#include <pcre.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATCHES_SIZE 32
#define ARR_DEFAULT_SIZE 10
#define LINE_MATCH_WITH_INVERT 0
#define RED "\x1B[01;31m"
#define WHITE "\x1b[0m"
#define GREEN "\x1b[32m"
#define BLUE "\x1b[36m"
#define PURPLE "\x1b[35m"

struct args {
  bool i;
  bool v;
  bool c;
  bool l;
  bool n;
  bool h;
  bool s;
  bool o;
  bool next_arg_is_regexp;
  bool file_with_regexp_in_argv;
};

struct regexp {
  void** regexps;
  int size_of_regexps_arr;
  int regexp_counter;
  pcre* current_regexp;
  int number_of_current_regexp;
  char* current_line;
  void** matches;
  int size_of_matches;
  int matches_counter;
  int line_with_match_counter;
  char last_char;
};

struct file {
  int all_lines_counter;
  void** files;
  int size_of_files_arr;
  int file_counter;
  FILE* current_file;
  int number_of_current_file;
  unsigned long long int number_of_line_in_current_file;
};

bool try_to_open_all_files(struct args*, struct file*);
bool bre_to_pcre(char*, struct regexp*);
bool put_match_index(struct regexp*, int, int);
int compare_subarrays(const void*, const void*);
void print_line_with_red(struct args*, struct regexp*, struct file*);
bool prepare_struct(struct args*, struct regexp*, struct file*, int, char*[]);
int find_hit_with_one_regexp(struct regexp*, struct args*);
int find_hits_in_line(struct regexp*, struct args*);
int find_and_print_match_in_file(struct args*, struct regexp*, struct file*);
void print_prefix(struct args*, struct file*);
void* my_dup(void*, size_t);
size_t my_getline(char**, size_t*, FILE*);
bool parse_args(int, char*[], struct args*, struct regexp*, struct file*);
bool parse_flags(char*, struct args*);
bool read_regexp_from_file(char*, struct regexp*);
bool compile_all_regexps(void***, int, bool);
bool get_all_regexp(FILE*, struct regexp*);
bool put_elem_in_arr(void***, int*, int*, void*, size_t);
bool try_and_open_file(char*, FILE**, bool);
void clear_memory(struct regexp*, struct file*);
void main_function(struct args*, struct regexp*, struct file*);

int main(int argc, char* argv[]) {
  struct args Args;
  struct regexp Regs;
  struct file File;
  bool all_is_success;

  if (argc >= 2) {
    all_is_success = prepare_struct(&Args, &Regs, &File, argc, argv);

    if (all_is_success) {
      main_function(&Args, &Regs, &File);
    }

    clear_memory(&Regs, &File);
  } else {
    printf("Использование: s21_grep ПАРАМЕТР… ШАБЛОНЫ ФАЙЛ…\n");
  }

  return 0;
}

bool prepare_struct(struct args* Args, struct regexp* Regs, struct file* File,
                    int argc, char* argv[]) {
  bool all_is_success;

  *Args = (struct args){.i = false,
                        .v = false,
                        .c = false,
                        .l = false,
                        .n = false,
                        .h = false,
                        .s = false,
                        .o = false,
                        .next_arg_is_regexp = true,
                        .file_with_regexp_in_argv = false};

  *Regs = (struct regexp){
      .regexps = malloc(sizeof(void*) * ARR_DEFAULT_SIZE),
      .size_of_regexps_arr = ARR_DEFAULT_SIZE,
      .regexp_counter = 0,
      .line_with_match_counter = 0,
      .number_of_current_regexp = 0,
      .matches = calloc(ARR_DEFAULT_SIZE, sizeof(void*) * ARR_DEFAULT_SIZE),
      .size_of_matches = 10ULL,
      .matches_counter = 0ULL,
      .last_char = '\n'};

  *File = (struct file){.all_lines_counter = 0,
                        .files = malloc(sizeof(void*) * ARR_DEFAULT_SIZE),
                        .size_of_files_arr = ARR_DEFAULT_SIZE,
                        .file_counter = 0,
                        .current_file = NULL,
                        .number_of_current_file = 0,
                        .number_of_line_in_current_file = 0ULL};

  all_is_success = parse_args(argc, argv, Args, Regs, File);

  if (all_is_success) {
    all_is_success =
        compile_all_regexps(&(Regs->regexps), Regs->regexp_counter, Args->i);
    if (all_is_success) {
      all_is_success = try_to_open_all_files(Args, File);
    }
  }

  if (Args->o && Args->v) all_is_success = false;

  return all_is_success;
}

bool try_to_open_all_files(struct args* Args, struct file* File) {
  FILE* tmp_file;
  bool all_is_success = false;

  for (int i = 0; i < File->file_counter; i++) {
    all_is_success = try_and_open_file(File->files[i], &tmp_file, !Args->s);
    if (all_is_success) {
      fclose(tmp_file);
    } else {
      break;
    }
  }

  if (File->file_counter == 0) {
    fprintf(stderr, "Нет файла для чтения, stdin не обрабатывается\n");
  }

  return all_is_success;
}

bool parse_args(int argc, char* argv[], struct args* Args, struct regexp* Regs,
                struct file* File) {
  bool all_is_success;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      all_is_success = parse_flags(argv[i], Args);
    } else if (Args->file_with_regexp_in_argv) {
      all_is_success = read_regexp_from_file(argv[i], Regs);
      Args->file_with_regexp_in_argv = false;
    } else if (Args->next_arg_is_regexp) {
      all_is_success = bre_to_pcre(argv[i], Regs);
      Args->next_arg_is_regexp = false;
    } else {
      all_is_success = put_elem_in_arr(&(File->files), &File->file_counter,
                                       &File->size_of_files_arr, argv[i],
                                       strlen(argv[i]) + 1);
    }
    if (!all_is_success) {
      break;
    }
  }

  return all_is_success;
}

bool compile_all_regexps(void*** arr, int count_of_regexps, bool flag_i) {
  bool all_is_success = true;
  const char* error_message;
  int error_number;

  for (int i = 0; i < count_of_regexps; i++) {
    char* pattern = (*arr)[i];
    (*arr)[i] =
        pcre_compile((*arr)[i], flag_i, &error_message, &error_number, NULL);
    free(pattern);
    if ((*arr)[i] == NULL) {
      fprintf(stderr, "Не удалось скомпилировать регулярное выражение\n");
      break;
    }
  }

  return all_is_success;
}

bool parse_flags(char* argv, struct args* Args) {
  bool all_is_success = true;

  for (int i = 1; i <= (int)strlen(argv) - 1; i++) {
    switch (argv[i]) {
      case 'e':
        Args->next_arg_is_regexp = true;
        i = (int)strlen(argv);
        break;
      case 'i':
        Args->i = true;
        break;
      case 'v':
        Args->v = true;
        break;
      case 'c':
        Args->c = true;
        break;
      case 'l':
        Args->l = true;
        break;
      case 'n':
        Args->n = true;
        break;
      case 'h':
        Args->h = true;
        break;
      case 's':
        Args->s = true;
        break;
      case 'f':
        Args->file_with_regexp_in_argv = true;
        Args->next_arg_is_regexp = false;
        i = (int)strlen(argv);
        break;
      case 'o':
        Args->o = true;
        break;
      default:
        fprintf(stderr, "s21_grep: '-%c' - нет такого флага\n", argv[i]);
        all_is_success = false;
        break;
    }
  }

  return all_is_success;
}

bool read_regexp_from_file(char* file_name, struct regexp* Regs) {
  FILE* file_with_regx = NULL;
  bool all_is_success;

  all_is_success = try_and_open_file(file_name, &file_with_regx, true);
  if (all_is_success) {
    all_is_success = get_all_regexp(file_with_regx, Regs);
    fclose(file_with_regx);
  }

  return all_is_success;
}

bool get_all_regexp(FILE* file, struct regexp* Regs) {
  bool all_is_success = true;
  char* line = NULL;
  size_t l = 0;

  while (my_getline(&line, &l, file) != (size_t)-1) {
    if (line[strlen(line) - 1] == '\n') {
      line[strlen(line) - 1] = '\0';
    }
    if (strlen(line) >= 2 && line[strlen(line) - 1] == '\\' &&
        line[strlen(line) - 2] != '\\') {
      all_is_success = false;
      fprintf(stderr,
              "s21_grep: Обратная косая черта в конце регулрного выражения\n");
      break;
    } else {
      all_is_success = bre_to_pcre(line, Regs);
    }
  }

  if (Regs->regexp_counter == 0) {
    all_is_success = false;
  }

  free(line);

  return all_is_success;
}

void main_function(struct args* Args, struct regexp* Regs, struct file* File) {
  bool all_is_success = true;
  int res;

  for (int i = 0; i < File->file_counter; i++) {
    File->number_of_current_file = i;
    all_is_success =
        try_and_open_file(File->files[i], &(File->current_file), !Args->s);
    if (all_is_success) {
      res = find_and_print_match_in_file(Args, Regs, File);
      fclose(File->current_file);
      File->number_of_line_in_current_file = 0ULL;
    }
    if (!all_is_success || res < -1) {
      break;
    }
    if (Args->l && res != PCRE_ERROR_NOMATCH) {
      if (Args->v) {
        printf(PURPLE "%s\n" WHITE, (char*)File->files[i]);
      } else {
        printf(PURPLE "%s\n" WHITE, (char*)File->files[i]);
      }
    }
  }

  if (all_is_success && Args->c && !Args->l) {
    printf("%d\n", Regs->line_with_match_counter);
  }
}

int find_and_print_match_in_file(struct args* Args, struct regexp* Regs,
                                 struct file* File) {
  int res;
  size_t l = 0;

  while (my_getline(&(Regs->current_line), &l, File->current_file) !=
         (size_t)-1) {
    File->all_lines_counter++;
    File->number_of_line_in_current_file++;
    res = find_hits_in_line(Regs, Args);
    if (res != PCRE_ERROR_NOMATCH && (Args->l || Args->c)) {
      if (Args->c && !Args->l) {
        continue;
      } else if (Args->l) {
        break;
      }
    }
    if (res != PCRE_ERROR_NOMATCH && Args->v && !Args->l && !Args->c) {
      print_prefix(Args, File);
      printf("%s", Regs->current_line);
      Regs->last_char = strlen(Regs->current_line);
    } else if (!(Args->l || Args->c || Args->v)) {
      print_line_with_red(Args, Regs, File);
    }
  }
  if (Regs->last_char != '\n' && !(Args->o || Args->l || Args->c)) {
    printf("\n");
  }
  File->number_of_line_in_current_file = 0;

  return res;
}

void print_line_with_red(struct args* Args, struct regexp* Regs,
                         struct file* File) {
  char* line = Regs->current_line;
  int lenght = strlen(Regs->current_line) - 1;
  int offset = 0;
  int start;
  int end;
  if (Regs->matches[0] != NULL) {
    print_prefix(Args, File);
    qsort(Regs->matches, Regs->matches_counter, sizeof(Regs->matches[0]),
          compare_subarrays);
    for (int i = 0; i < Regs->matches_counter; i++) {
      start = ((int*)(Regs->matches[i]))[0];
      end = ((int*)(Regs->matches[i]))[1];
      if (offset > start) {
        free(Regs->matches[i]);
        Regs->matches[i] = NULL;
        continue;
      }
      if (!Args->o) {
        Regs->last_char = line[lenght];
        printf("%.*s" RED "%.*s" WHITE, start - offset, &line[offset],
               end - start, &line[start]);
        offset = end;
      } else {
        if (i != 0) {
          print_prefix(Args, File);
        }
        printf(RED "%.*s\n" WHITE, end - start, &line[start]);
      }
      free(Regs->matches[i]);
      Regs->matches[i] = NULL;
    }
    if (!Args->o) {
      printf("%s", &line[offset]);
    }
  }

  Regs->matches_counter = 0;
}

int find_hits_in_line(struct regexp* Regs, struct args* Args) {
  int res;

  for (int i = 0; i < Regs->regexp_counter; i++) {
    Regs->current_regexp = Regs->regexps[i];
    res = find_hit_with_one_regexp(Regs, Args);
    if (res < -1) {
      break;
    }
  }

  return res;
}

int find_hit_with_one_regexp(struct regexp* Regs, struct args* Args) {
  int capture_count, result;
  pcre_fullinfo(Regs->current_regexp, NULL, PCRE_INFO_CAPTURECOUNT,
                &capture_count);
  int ovec_size = (capture_count + 1) * 2;
  int* ovector = calloc(ovec_size, sizeof(int));
  int offset = 0;
  char* line = Regs->current_line;
  int lenght = strlen(line);
  if (!ovector) {
    fprintf(stderr, "Ошибка выделения памяти\n");
    result = -2;
  } else {
    do {
      result = pcre_exec(Regs->current_regexp, NULL, line, lenght, offset, 0,
                         ovector, ovec_size);
      if (result < -1) {
        fprintf(stderr, "Ошибка выполнения pcre_exec: %d\n", result);
      } else if (result != PCRE_ERROR_NOMATCH) {
        if (!Args->v && (Args->l || Args->c)) {
          Regs->line_with_match_counter++;
          break;
        } else if (Args->v) {
          result = -1;
          break;
        }
        if (!put_match_index(Regs, ovector[0], ovector[1])) {
          result = -2;
        }
        offset = offset == ovector[1] ? offset + 1 : ovector[1];
      } else if (result == PCRE_ERROR_NOMATCH) {
        if (Args->v) {
          if (Args->c || Args->l) {
            result = 1;
            Regs->line_with_match_counter++;
            break;
          } else if (offset == 0) {
            result = 1;
            Regs->matches_counter = 0;
            break;
          }
        }
      }
    } while ((offset < lenght) && (result >= 0));
  }

  free(ovector);

  return result;
}

bool put_match_index(struct regexp* Regs, int start, int end) {
  bool all_is_success = true;

  int match[2] = {start, end};

  if (!put_elem_in_arr(&(Regs->matches), &Regs->matches_counter,
                       &Regs->size_of_regexps_arr, match, sizeof(int) * 2)) {
    all_is_success = false;
  }

  return all_is_success;
}

void print_prefix(struct args* Args, struct file* File) {
  if (File->file_counter > 1 && !Args->h) {
    printf(PURPLE "%s" BLUE ":" WHITE,
           (char*)File->files[File->number_of_current_file]);
  }
  if (Args->n) {
    printf(GREEN "%llu" BLUE ":" WHITE, File->number_of_line_in_current_file);
  }
}

bool put_elem_in_arr(void*** arr, int* count_of_elem, int* size_of_arr,
                     void* elem, size_t size) {
  bool all_is_success = true;
  bool arr_full = *count_of_elem == *size_of_arr;
  char* new_arr = NULL;

  if (arr_full) {
    *size_of_arr *= 2;
    new_arr = realloc(*arr, ((*size_of_arr) * sizeof(char*)));
    if (new_arr == NULL) {
      free(*arr);
      all_is_success = false;
      *size_of_arr /= 2;
    } else {
      *arr = (void**)new_arr;
    }
  }

  if (all_is_success) {
    (*arr)[*count_of_elem] = my_dup(elem, size);
    if ((*arr)[*count_of_elem] == NULL) {
      printf("Ошибка выделения памяти!");
      all_is_success = false;
    } else {
      (*count_of_elem)++;
    }
  }

  return all_is_success;
}

void* my_dup(void* elem, size_t size) {
  void* dst = NULL;

  if (!(!elem || size == 0)) {
    dst = malloc(size);
    if (dst != NULL) {
      memcpy(dst, elem, size);
    }
  }

  return dst;
}

size_t my_getline(char** lineptr, size_t* n, FILE* stream) {
  size_t bytes_read = 0;
  char ch;

  if (*lineptr == NULL || *n <= 0) {
    *n = 128;
    *lineptr = realloc(*lineptr, *n);
  }

  if (*lineptr != NULL) {
    for (;;) {
      ch = fgetc(stream);
      if (ch == EOF) break;
      if ((size_t)(bytes_read + 1) >= *n) {
        *n *= 2;
        *lineptr = realloc(*lineptr, *n);
        if (*lineptr == NULL) {
          bytes_read = -1;
          break;
        }
      }
      (*lineptr)[bytes_read++] = ch;
      if (ch == '\n') break;
    }
  } else {
    bytes_read = -1;
  }

  (*lineptr)[bytes_read] = '\0';
  return bytes_read > 0 ? bytes_read : (size_t)-1;
}

bool try_and_open_file(char* file_name, FILE** file, bool output_error) {
  bool all_is_success = true;
  *file = fopen(file_name, "r");
  if (*file != NULL) {
    size_t lenght = 4;
    char* header = calloc(lenght, sizeof(char*));
    if (header == NULL) {
      fprintf(stderr, "s21_regexp: Не удалось выделить память\n");
      all_is_success = false;
    } else {
      int read = my_getline(&header, &lenght, *file);
      rewind(*file);
      if (read >= 4 && strncmp(header, "\177ELF", 4) == 0) {
        if (output_error) {
          fprintf(stderr, "s21_regexp: %s - исполняющий файл\n", file_name);
        }
        fclose(*file);
        all_is_success = false;
      }
    }
    free(header);
  } else {
    if (output_error) {
      fprintf(stderr, "s21_regexp: Не удалось открыть файл %s\n", file_name);
    }
    all_is_success = false;
  }

  return all_is_success;
}

int compare_subarrays(const void* a, const void* b) {
  int first_element_a = **(int**)a;
  int first_element_b = **(int**)b;

  return (first_element_a > first_element_b) -
         (first_element_a < first_element_b);
}

bool bre_to_pcre(char* bre_pattern, struct regexp* Regs) {
  bool all_is_success = true;
  char pcre_pattern[2 * strlen(bre_pattern) + 1];
  bool next_is_special = false;
  int j = 0;
  for (int i = 0; bre_pattern[i] != '\0'; i++) {
    switch (bre_pattern[i]) {
      case '+':
      case '?':
      case '|':
      case '(':
      case ')':
      case '{':
      case '}':
        if (!next_is_special) {
          pcre_pattern[j++] = '\\';
        } else {
          next_is_special = false;
        }
        pcre_pattern[j++] = bre_pattern[i];
        break;
      case '\\':
        next_is_special = true;
        break;
      case '.':
      case '*':
      case '^':
      case '$':
      case '[':
      case ']':
        if (next_is_special) {
          pcre_pattern[j++] = '\\';
          next_is_special = false;
        }
        pcre_pattern[j++] = bre_pattern[i];
        break;
      default:
        pcre_pattern[j++] = bre_pattern[i];
        break;
    }
  }
  pcre_pattern[j] = '\0';

  all_is_success = put_elem_in_arr(&(Regs->regexps), &Regs->regexp_counter,
                                   &Regs->size_of_regexps_arr, pcre_pattern,
                                   strlen(pcre_pattern) + 1);

  return all_is_success;
}

void clear_memory(struct regexp* Regs, struct file* File) {
  if (File->files != NULL) {
    for (int i = 0; i < File->file_counter; i++) {
      free(File->files[i]);
    }
    free(File->files);
  }
  if (Regs->regexps != NULL) {
    for (int i = 0; i < Regs->regexp_counter; i++) {
      pcre_free(Regs->regexps[i]);
    }
    free(Regs->regexps);
  }
  if (Regs->matches != NULL) {
    for (int i = 0; i < Regs->matches_counter; i++) {
      free(Regs->matches[i]);
    }
    free(Regs->matches);
  }
  if (Regs->current_line != NULL) {
    free(Regs->current_line);
  }
}