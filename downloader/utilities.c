/*
** Created by Glastis on 30/07/18.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header/utilities.h"

void                        print_help()
{
    printf("%s\n", USAGE);
}

void                        str_init(t_str *str)
{
    str->data = NULL;
    str->len = 0;
}

inline __attribute__((always_inline)) void                  error(const char *error)
{
    fprintf(stderr, "Error: %s\n", error);
    exit(-1);
}

inline __attribute__((always_inline)) unsigned int          str_greater_than(const char *str, unsigned int max)
{
    unsigned int                                            i;

    i = 0;
    if (!str)
    {
        return (0);
    }
    while (str[i] && i <= max)
    {
        ++i;
    }
    return (unsigned int) (str[i] != '\0');
}

inline __attribute__((always_inline)) unsigned int          safe_strlen(const char *str)
{
    if (!str)
    {
        return (0);
    }
    return (unsigned int) (strlen(str));
}

inline __attribute__((always_inline)) void                  *safe_malloc(size_t len, size_t type)
{
    void                                                    *ret;

    if (type > 0)
    {
        len *= type;
    }
    if (!(ret = malloc(len)))
    {
        error(ERROR_MALLOC_FAILED);
    }
    return (ret);
}

inline __attribute__((always_inline)) void                  *safe_realloc(void *ptr, size_t len, size_t type)
{
    void                                                    *ret;

    if (type > 0)
    {
        len *= type;
    }
    if (!(ret = realloc(ptr, len)))
    {
        error(ERROR_MALLOC_FAILED);
    }
    return ret;

}

inline __attribute__((always_inline)) unsigned int          comp_str(const char *str1, const char *str2)
{
    unsigned int                                            i;

    i = 0;
    if (!str1 || !str2)
    {
        return (0);
    }
    while (str1[i] && str2[i] && str1[i] == str2[i])
    {
        ++i;
    }
    return (unsigned int) ((!str1[i]) || (!str2[i]));
}

char                        *str_coupler(const char *str1, const char *str2)
{
    char                    *new;
    unsigned int            len1;
    unsigned int            len2;

    len1 = safe_strlen(str1);
    len2 = safe_strlen(str2);
    if (len1 + len2 == 0)
    {
        return (NULL);
    }
    new = safe_malloc(len1 + len2, sizeof(char));
    if (str1)
    {
        memcpy(new, str1, len1);
    }
    if (str2)
    {
        memcpy(&new[len1], str2, len2);
    }
    new[len1 + len2] = '\0';
    return (new);
}