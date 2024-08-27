#pragma once

#include <cstdint>
#include <cinttypes>

#include <iostream>

uint64_t Strlen(const char*);

int Strcmp(const char*, const char*);

int Strncmp(const char*, const char*, uint64_t);

char* Strcpy(char*, const char*);

char* Strncpy(char*, const char*, uint64_t);

char* Strcat(char* dest, const char* src);

char* Strncat(char* dest, const char* src, uint64_t count);

const char* Strchr(const char* str, char symbol);

const char* Strrchr(const char* str, char symbol);

uint64_t Strspn(const char* dest, const char* src);

uint64_t Strcspn(const char* dest, const char* src);

const char* Strpbrk(const char* dest, const char* breakset);

const char* Strstr(const char* str, const char* pattern);