#include "../include/string.h"

void strcpy(char *dst, const char *src)
{
    while((*src) != '\0')
    {
        *(dst ++) = *(src ++);
    }
    *dst = '\0';
}