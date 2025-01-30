#include <lib/memops.h>
void memset(void *ptr, int value, int size)
{
    char *cptr = (char *)ptr;
    for (int i = 0; i < size; ++i)
    {
        cptr[i] = value;
    }
}

void memcpy(char *dest, char *src, int size)
{
    for (int i = 0; i < size; ++i)
    {
        dest[i] = src[i];
    }
}

int memcmp(void *s1, void *s2, int n)
{
    unsigned char *p1 = (unsigned char *)s1;
    unsigned char *p2 = (unsigned char *)s2;

    for (int i = 0; i < n; i++)
    {
        if (p1[i] != p2[i])
        
        {
            return p1[i] - p2[i];
        }
    }

    return 0;
}

char *strchr(char *s, int c)
{
    while (*s != '\0')
    {
        if (*s == (char)c)
        {
            return (char *)s;
        }
        s++;
    }
    if (c == '\0')
    {
        return (char *)s;
    }
    return 0;
}