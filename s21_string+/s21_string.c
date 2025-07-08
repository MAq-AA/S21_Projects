#include "s21_string.h"

#include <string.h>
#ifdef __linux__
const char *err_list[] = {"Success",
                          "Operation not permitted",
                          "No such file or directory",
                          "No such process",
                          "Interrupted system call",
                          "Input/output error",
                          "No such device or address",
                          "Argument list too long",
                          "Exec format error",
                          "Bad file descriptor",
                          "No child processes",
                          "Resource temporarily unavailable",
                          "Cannot allocate memory",
                          "Permission denied",
                          "Bad address",
                          "Block device required",
                          "Device or resource busy",
                          "File exists",
                          "Invalid cross-device link",
                          "No such device",
                          "Not a directory",
                          "Is a directory",
                          "Invalid argument",
                          "Too many open files in system",
                          "Too many open files",
                          "Inappropriate ioctl for device",
                          "Text file busy",
                          "File too large",
                          "No space left on device",
                          "Illegal seek",
                          "Read-only file system",
                          "Too many links",
                          "Broken pipe",
                          "Numerical argument out of domain",
                          "Numerical result out of range",
                          "Resource deadlock avoided",
                          "File name too long",
                          "No locks available",
                          "Function not implemented",
                          "Directory not empty",
                          "Too many levels of symbolic links",
                          "Unknown error 41",
                          "No message of desired type",
                          "Identifier removed",
                          "Channel number out of range",
                          "Level 2 not synchronized",
                          "Level 3 halted",
                          "Level 3 reset",
                          "Link number out of range",
                          "Protocol driver not attached",
                          "No CSI structure available",
                          "Level 2 halted",
                          "Invalid exchange",
                          "Invalid request descriptor",
                          "Exchange full",
                          "No anode",
                          "Invalid request code",
                          "Invalid slot",
                          "Unknown error 58",
                          "Bad font file format",
                          "Device not a stream",
                          "No data available",
                          "Timer expired",
                          "Out of streams resources",
                          "Machine is not on the network",
                          "Package not installed",
                          "Object is remote",
                          "Link has been severed",
                          "Advertise error",
                          "Srmount error",
                          "Communication error on send",
                          "Protocol error",
                          "Multihop attempted",
                          "RFS specific error",
                          "Bad message",
                          "Value too large for defined data type",
                          "Name not unique on network",
                          "File descriptor in bad state",
                          "Remote address changed",
                          "Can not access a needed shared library",
                          "Accessing a corrupted shared library",
                          ".lib section in a.out corrupted",
                          "Attempting to link in too many shared libraries",
                          "Cannot exec a shared library directly",
                          "Invalid or incomplete multibyte or wide character",
                          "Interrupted system call should be restarted",
                          "Streams pipe error",
                          "Too many users",
                          "Socket operation on non-socket",
                          "Destination address required",
                          "Message too long",
                          "Protocol wrong type for socket",
                          "Protocol not available",
                          "Protocol not supported",
                          "Socket type not supported",
                          "Operation not supported",
                          "Protocol family not supported",
                          "Address family not supported by protocol",
                          "Address already in use",
                          "Cannot assign requested address",
                          "Network is down",
                          "Network is unreachable",
                          "Network dropped connection on reset",
                          "Software caused connection abort",
                          "Connection reset by peer",
                          "No buffer space available",
                          "Transport endpoint is already connected",
                          "Transport endpoint is not connected",
                          "Cannot send after transport endpoint shutdown",
                          "Too many references: cannot splice",
                          "Connection timed out",
                          "Connection refused",
                          "Host is down",
                          "No route to host",
                          "Operation already in progress",
                          "Operation now in progress",
                          "Stale file handle",
                          "Structure needs cleaning",
                          "Not a XENIX named type file",
                          "No XENIX semaphores available",
                          "Is a named type file",
                          "Remote I/O error",
                          "Disk quota exceeded",
                          "No medium found",
                          "Wrong medium type",
                          "Operation canceled",
                          "Required key not available",
                          "Key has expired",
                          "Key has been revoked",
                          "Key was rejected by service",
                          "Owner died",
                          "State not recoverable",
                          "Operation not possible due to RF-kill",
                          "Memory page has hardware error"};
#elif defined(__APPLE__)
const char *err_list[] = {"Undefined error: 0",
                          "Operation not permitted",
                          "No such file or directory",
                          "No such process",
                          "Interrupted system call",
                          "Input/output error",
                          "Device not configured",
                          "Argument list too long",
                          "Exec format error",
                          "Bad file descriptor",
                          "No child processes",
                          "Resource deadlock avoided",
                          "Cannot allocate memory",
                          "Permission denied",
                          "Bad address",
                          "Block device required",
                          "Resource busy",
                          "File exists",
                          "Cross-device link",
                          "Operation not supported by device",
                          "Not a directory",
                          "Is a directory",
                          "Invalid argument",
                          "Too many open files in system",
                          "Too many open files",
                          "Inappropriate ioctl for device",
                          "Text file busy",
                          "File too large",
                          "No space left on device",
                          "Illegal seek",
                          "Read-only file system",
                          "Too many links",
                          "Broken pipe",
                          "Numerical argument out of domain",
                          "Result too large",
                          "Resource temporarily unavailable",
                          "Operation now in progress",
                          "Operation already in progress",
                          "Socket operation on non-socket",
                          "Destination address required",
                          "Message too long",
                          "Protocol wrong type for socket",
                          "Protocol not available",
                          "Protocol not supported",
                          "Socket type not supported",
                          "Operation not supported",
                          "Protocol family not supported",
                          "Address family not supported by protocol family",
                          "Address already in use",
                          "Can't assign requested address",
                          "Network is down",
                          "Network is unreachable",
                          "Network dropped connection on reset",
                          "Software caused connection abort",
                          "Connection reset by peer",
                          "No buffer space available",
                          "Socket is already connected",
                          "Socket is not connected",
                          "Can't send after socket shutdown",
                          "Too many references: can't splice",
                          "Operation timed out",
                          "Connection refused",
                          "Too many levels of symbolic links",
                          "File name too long",
                          "Host is down",
                          "No route to host",
                          "Directory not empty",
                          "Too many processes",
                          "Too many users",
                          "Disc quota exceeded",
                          "Stale NFS file handle",
                          "Too many levels of remote in path",
                          "RPC struct is bad",
                          "RPC version wrong",
                          "RPC prog. not avail",
                          "Program version wrong",
                          "Bad procedure for program",
                          "No locks available",
                          "Function not implemented",
                          "Inappropriate file type or format",
                          "Authentication error",
                          "Need authenticator",
                          "Device power is off",
                          "Device error",
                          "Value too large to be stored in data type",
                          "Bad executable (or shared library)",
                          "Bad CPU type in executable",
                          "Shared library version mismatch",
                          "Malformed Mach-o file",
                          "Operation canceled",
                          "Identifier removed",
                          "No message of desired type",
                          "Illegal byte sequence",
                          "Attribute not found",
                          "Bad message",
                          "EMULTIHOP (Reserved)",
                          "No message available on STREAM",
                          "ENOLINK (Reserved)",
                          "No STREAM resources",
                          "Not a STREAM",
                          "Protocol error",
                          "STREAM ioctl timeout",
                          "Operation not supported on socket",
                          "Policy not found",
                          "State not recoverable",
                          "Previous owner died",
                          "Interface output queue is full",
                          "Capabilities insufficient"};
#endif

void *s21_memchr(const void *str, int c, s21_size_t n) {
  char *p = (char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    if (*p == c) {
      break;
    }
    p++;
  }
  return p;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  char *p1 = (char *)str1;
  char *p2 = (char *)str2;
  int result = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (*p1 < *p2) {
      result = -1;
      break;
    }
    if (*p1 > *p2) {
      result = 1;
      break;
    }
    p1++;
    p2++;
  }
  return result;
}

void *s21_memcpy(void *restrict dest, const void *restrict src, s21_size_t n) {
  char *p1 = dest;
  char *p2 = (char *)src;
  for (s21_size_t i = 0; i < n; i++) {
    *p1 = *p2;
    p1++;
    p2++;
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  char *p = str;
  for (s21_size_t i = 0; i < n; i++) {
    *p = c;
    p++;
  }
  return str;
}

char *s21_strncat(char *restrict dest, const char *restrict src, s21_size_t n) {
  char *p1 = dest;
  char *p2 = (char *)src;
  while (*p1 != '\0') {
    p1++;
  }
  for (s21_size_t i = 0; i < n; i++) {
    *p1 = *p2;
    p1++;
    p2++;
    if (*p2 == '\0') {
      break;
    }
  }
  return dest;
}

char *s21_strchr(const char *str, int c) {
  char *p = (char *)str;
  int len = 0;
  while (*p != '\0') {
    len++;
    p++;
  }
  p = (char *)str;
  for (int i = 0; i < len; i++) {
    if (*p == c) {
      break;
    }
    p++;
  }
  return p;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  char *p1 = (char *)str1;
  char *p2 = (char *)str2;
  int result = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (*p1 < *p2 || (*p1 == '\0' && *p2 != '\0')) {
      result = -1;
      break;
    }
    if (*p1 > *p2 || (*p1 != '\0' && *p2 == '\0')) {
      result = 1;
      break;
    }
    p1++;
    p2++;
  }
  return result;
}

char *s21_strncpy(char *restrict dest, const char *restrict src, s21_size_t n) {
  char *p1 = dest;
  char *p2 = (char *)src;
  for (s21_size_t i = 0; i < n; i++) {
    if (*p2 == '\0') {
      *p1 = '\0';
      p1++;
    } else {
      *p1 = *p2;
      p1++;
      p2++;
    }
  }
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  char *p1 = (char *)str1;
  char *p2 = (char *)str2;
  s21_size_t index = 0;
  int matched = 0;
  while (*p1 != '\0' && matched == 0) {
    while (*p2 != '\0') {
      if (*p1 == *p2) {
        matched = 1;
        break;
      }
      p2++;
    }
    if (matched == 0) {
      index++;
      p1++;
      p2 = (char *)str2;
    }
  }
  return index;
}

char *s21_strerror(int errnum) {
  char *err_str = "Unknown error";
  s21_size_t err_list_size = sizeof(err_list) / sizeof(err_list[0]);
  if (errnum >= 0 && (s21_size_t)errnum < err_list_size) {
    err_str = (char *)err_list[errnum];
  }
  return err_str;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  while (*str != '\0') {
    len++;
    str++;
  }
  return len;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *p1 = (char *)str1;
  char *p2 = (char *)str2;
  int matched = 0;
  while (*p1 != '\0' && matched == 0) {
    while (*p2 != '\0') {
      if (*p1 == *p2) {
        matched = 1;
        break;
      }
      p2++;
    }
    if (matched == 0) {
      p1++;
      p2 = (char *)str2;
    }
  }
  if (matched == 0) {
    p1 = S21_NULL;
  }
  return p1;
}

char *s21_strrchr(const char *str, int c) {
  char *p = (char *)str;
  int len = 0;
  int matched = 0;
  while (*p != '\0') {
    len += 1;
    p++;
  }
  for (int i = len - 1; i >= 0; i--) {
    if (*p == c) {
      matched = 1;
      break;
    }
    p -= sizeof(char);
  }
  if (matched == 0) {
    p = S21_NULL;
  }
  return p;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *p1 = (char *)haystack;
  char *p2 = (char *)needle;
  int len2 = 0;
  int matched = 0;
  int count = 0;
  while (*p2 != '\0') {
    len2++;
    p2++;
  }
  while (*p1 != '\0') {
    p2 = (char *)needle;
    for (int i = 0; i < len2; i++) {
      if (*p1 != *p2) {
        break;
      }
      p1++;
      p2++;
      count++;
    }
    if (count == len2) {
      matched = 1;
      p1 -= len2 * sizeof(char);
      break;
    }
    p1++;
  }
  if (!matched) {
    p1 = S21_NULL;
  }
  return p1;
}

char *s21_strtok(char *restrict str, const char *restrict delim) {
  static char *new_str = S21_NULL;
  if (str != S21_NULL) {
    new_str = str;
  }
  char *delimiter;
  char *token = S21_NULL;
  int found = 0;
  while (*new_str != '\0') {
    delimiter = (char *)delim;
    while (*delimiter != '\0') {
      if (*new_str == *delimiter) {
        break;
      }
      if (*new_str != *delimiter) {
        delimiter++;
      }
      if (!*delimiter) {
        found = 1;
      }
    }
    if (found) {
      break;
    }
    new_str++;
  }
  if (found) {
    token = new_str;
    char *token_end = token;
    found = 0;

    while (*token_end != '\0') {
      delimiter = (char *)delim;
      while (*delimiter != '\0') {
        if (*token_end == *delimiter) {
          found = 1;
          *token_end = '\0';
          break;
        }
        delimiter++;
      }
      if (found) {
        new_str = token_end + 1;
        break;
      }
      token_end++;
      new_str++;
    }
  }
  return token;
}

void *s21_to_upper(const char *str) {
  char *p = (char *)str;
  while (*p != '\0') {
    if (*p >= 97 && *p <= 122) {
      *p -= 32;
    }
    p++;
  }
  p = (char *)str;
  return p;
}

void *s21_to_lower(const char *str) {
  char *p = (char *)str;
  while (*p != '\0') {
    if (*p >= 65 && *p <= 90) {
      *p += 32;
    }
    p++;
  }
  p = (char *)str;
  return p;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t src_len = 0;
  s21_size_t str_len = 0;

  while (*src != '\0') {
    src_len++;
    src++;
  }
  while (*str != '\0') {
    str_len++;
    str++;
  }

  src -= src_len;
  str -= str_len;

  char *result = malloc(src_len + str_len + 1);
  for (s21_size_t i = 0; i < start_index; i++) {
    result[i] = *src;
    src++;
  }

  for (s21_size_t i = start_index; i < start_index + str_len; i++) {
    result[i] = *str;
    str++;
  }
  for (s21_size_t i = start_index + str_len; i < src_len + str_len; i++) {
    result[i] = *src;
    src++;
  }
  result[src_len + str_len] = '\0';
  return result;
}

void *s21_trim(const char *src, const char *trim_chars) {
  s21_size_t src_len = 0;
  s21_size_t trim_start = 0;
  s21_size_t trim_end = 0;
  s21_size_t trimmed_len = 0;
  char *p1 = (char *)src;
  while (*p1 != '\0') {
    src_len++;
    p1++;
  }
  p1 = (char *)src;
  while (*p1 != '\0') {
    int found = 0;
    char *p2 = (char *)trim_chars;
    while (*p2 != '\0') {
      if (*p1 == *p2) {
        trim_start++;
        break;
      }
      if (*p1 != *p2) {
        p2++;
      }
      if (!*p2) {
        found = 1;
      }
    }
    if (found) {
      break;
    }
    p1++;
  }
  p1 = (char *)src + src_len - 1;
  while (*p1 != '\0') {
    int found = 0;
    char *p2 = (char *)trim_chars;
    while (*p2 != '\0') {
      if (*p1 == *p2) {
        trim_end++;
        break;
      }
      if (*p1 != *p2) {
        p2++;
      }
      if (!*p2) {
        found = 1;
      }
    }
    if (found) {
      break;
    }
    p1--;
  }
  trimmed_len = src_len - trim_start - trim_end;
  p1 = (char *)src + trim_start;
  char *result = malloc(trimmed_len + 1);

  for (s21_size_t i = 0; i < trimmed_len; i++) {
    result[i] = *p1;
    p1++;
  }
  result[trimmed_len] = '\0';
  return result;
}