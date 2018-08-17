/*
** Created by Glastis on 30/07/18.
*/

#ifndef DOWNLOADER_UTILITIES_H
#define DOWNLOADER_UTILITIES_H

#define USAGE                                       "./dowloader id list_file progress_file"
#define TRUE                                        1
#define FALSE                                       0
#define UNUSED(X)                                   ((void)(X))

#define ERROR_MALLOC_FAILED                         "Failed to allocate memory"

struct                      s_str
{
    size_t                  len;
    char                    *data;
};

typedef struct s_str        t_str;

void                        print_help();
void                        error(const char *error);
unsigned int                safe_strlen(const char *str);
void                        *safe_malloc(size_t len, size_t type);
void                        *safe_realloc(void *ptr, size_t len, size_t type);
char                        *str_coupler(const char *str1, const char *str2);
unsigned int                comp_str(const char *str1, const char *str2);
unsigned int                str_greater_than(const char *str, unsigned int max);
void                        str_init(t_str *str);

#endif /* !DOWNLOADER_UTILITIES_H */
