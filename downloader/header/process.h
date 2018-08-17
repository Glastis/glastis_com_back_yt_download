/*
** Created by Glastis on 30/07/18.
*/

#ifndef DOWNLOADER_PROCESS_H
#define DOWNLOADER_PROCESS_H

struct                      s_video
{
    char                    *id;
    char                    *title;
    int                     downloaded;
    int                     converted;
};

struct                      s_process
{
    struct s_video          **video;
    int                     video_amount;
};

typedef struct s_video      t_video;
typedef struct s_process    t_process;

#endif /* !DOWNLOADER_PROCESS_H */
