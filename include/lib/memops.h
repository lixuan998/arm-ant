#pragma once

#include <common/stdint.h>
#include <common/stddef.h>

void memset(void *ptr, int value, int size);

void memcpy(char *dest, char *src, int size);

int memcmp(void *s1, void *s2, int n);

char *strchr(char *s, int c);