/*
** Created by Glastis on 30/07/18.
*/

#ifndef DOWNLOADER_MAIN_H
#define DOWNLOADER_MAIN_H

#define OPT_COMPLETION_DOWNLOAD                     "--download"
#define OPT_COMPLETION_DOWNLOAD_SHOT                "-d"
#define OPT_COMPLETION_CONVERT                      "--convert"
#define OPT_COMPLETION_CONVERT_SHOT                 "-c"
#define OPT_HELP                                    "--help"
#define OPT_HELP_SHOT                               "-h"

#define ERROR_ARGUMENT_IGNORED                      "Argument ignored. See --help or -h to get usage."
#define ERROR_BAD_TREAD_AMOUNT                      "Thread number must be more than 0"

#define THREAD_DEFAULT_DOWNLOAD                     4u
#define THREAD_DEFAULT_CONVERT                      4u
#define THREAD_MIN_DOWNLOAD                         1u
#define THREAD_MIN_CONVERT                          1u

struct                      s_opt
{
    char                    *list_filepath;
    char                    *progress_filepath;
    int                     download;
    int                     convert;
    unsigned int            thread_amount_download;
    unsigned int            thread_amount_convert;
};

typedef struct s_opt        t_opt;

int                         main(int ac, char **av);

#endif /* !DOWNLOADER_MAIN_H */
