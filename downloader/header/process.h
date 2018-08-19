/*
** Created by Glastis on 30/07/18.
*/

#ifndef DOWNLOADER_PROCESS_H
#define DOWNLOADER_PROCESS_H

struct                      s_opt
{
    char                    *list_filepath;
    char                    *progress_filepath;
    char                    *output_format;
    unsigned int            thread_amount_download;
    unsigned int            thread_amount_convert;
};

struct                      s_video
{
    char                    *id;
    char                    *title;
    int                     downloaded;
    int                     download_ended;
    int                     converted;
};

struct                      s_process
{
    struct s_video          **video;
    unsigned int            video_amount;
};

typedef struct s_video      t_video;
typedef struct s_process    t_process;
typedef struct s_opt        t_opt;

#endif /* !DOWNLOADER_PROCESS_H */
