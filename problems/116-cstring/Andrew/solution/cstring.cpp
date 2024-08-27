#include "cstring"

size_t Strlen(const char* str) {
  auto str_end = str;
  while(*str_end != 0) { ++str_end; }
  return str_end - str;
}

int Strcmp(const char* first, const char* second) {
  int value = 0;
  for (size_t iter = 0;; ++iter) {
    value = first[iter] - second[iter];
    if (value != 0 || first[iter] == 0 || second[iter] == 0) {
      return value;
    }
  }
  return 0;
}

int Strncmp(const char* first, const char* second, size_t count) {
  int value = 0;
  for (size_t iter = 0; iter < count; ++iter) {  //^
    value = first[iter] - second[iter];
    if (value != 0 || first[iter] == 0 || second[iter] == 0) {
      return value;
    }
  }
  return 0;
}

char* Strcpy(char* dest, const char* src) {
  for (size_t iter = 0 ;; ++iter) {
    dest[iter] = src[iter];
    if (src[iter] == 0) {
      return dest;
    }
  }
  return dest;
}

char* Strncpy(char* dest, const char* src, size_t count) {
  size_t iter = 0;
  for (; iter < count && src[iter] != 0; ++iter) {
    dest[iter] = src[iter];
  }
  for (; iter < count; ++iter) {
    dest[iter] = 0;
  }
  return dest;
}

char* Strcat(char* dest, const char* src) {  // !
  size_t len = Strlen(dest);
  for (size_t iter = 0 ;; ++iter) {
    dest[len+iter] = src[iter];
    if (src[iter] == 0) {
      return dest;
    }
  }
  return dest;
}

char* Strncat(char* dest, const char* src, size_t count) {
  size_t len = Strlen(dest);
  for (size_t iter = 0 ;; ++iter) {
    dest[len + iter] = src[iter];
    if (src[iter] == 0) {
      return dest;
    }
    if (iter == count) {
      dest[len + iter] = 0;
      return dest;
    }
  }
  return dest;
}

const char* Strchr(const char* str, char symbol) {
  for (auto iter = str;; ++iter) {
    if (*iter == symbol) {
      return iter;
    }
    if (*iter == 0) {
      return nullptr;
    }
  }
  return nullptr;
}

const char* Strrchr(const char* str, char symbol) {
  const char* answer = nullptr;
  for (auto iter = str;; ++iter) {
    if (*iter == symbol) {
      answer = iter;
    }
    if (*iter == 0) {
      return answer;
    }
  }
  return nullptr;
}

size_t Strspn(const char* dest, const char* src) {
  for (size_t iter = 0;; ++iter) {
    if (dest[iter] == 0 || !Strchr(src, dest[iter])) {
      return iter;
    }
  }
}

size_t Strcspn(const char* dest, const char* src) {
  for (size_t iter = 0;; ++iter) {
    if (dest[iter] == 0 || Strchr(src, dest[iter])) {
      return iter;
    }
  }
}

const char* Strpbrk(const char* dest, const char* breakset) {
  for (const char* iter = dest; *iter != 0; ++iter) {
    if (Strchr(breakset, *iter)) {
      return iter;
    }
  }
  return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
  size_t pattern_length = Strlen(pattern);
  if (pattern_length == 0) {
    return str;
  }
  auto substr = Strchr(str, pattern[0]);
  while (substr) {
    if (Strncmp(substr, pattern, pattern_length) == 0) {
      return substr;
    }
    substr = Strchr(substr + 1, pattern[0]);
  }
  return nullptr;
}