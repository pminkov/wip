#ifndef __STRING_UTIL_H
#define __STRING_UTIL_H

int starts_with(char *s, const char *with) {
  return strncmp(s, with, strlen(with)) == 0;
}

char* substr(const char* input, int offset, int len, char* dest) {
  int input_len = strlen (input);

  if (offset + len > input_len) {
    return NULL;
  }

  strncpy(dest, input + offset, len);
  return dest;
}

#endif
