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

#define USAGE                                       "./dowloader id list_file progress_file[--convert,-c] [--download,-d]"

#define ERROR_ARGUMENT_IGNORED                      "Argument ignored. See --help or -h to get usage."

#define UNUSED(X)                                   ((void)(X))

struct                  s_opt
{
    char                *list_filepath;
    char                *progress_filepath;
    char                *id;
    int                 download;
    int                 convert;
};

struct                  s_video
{
    char                *id;
    int                 downloaded;
    int                 converted;
};

struct                  s_process
{
    struct s_video      *video;
};

typedef struct s_opt    t_opt;

int                     main(int ac, char **av);

#endif /* !DOWNLOADER_MAIN_H */
