/*
** Created by Glastis on 18/08/18.
*/

#ifndef DOWNLOADER_DOWNLOAD_H
#define DOWNLOADER_DOWNLOAD_H

#include <pthread.h>
#include "process.h"
#include "main.h"

#define THREAD_CONVERTER_WAIT_DELAY                 500u /* Miliseconds to wait available videos to convert. */
#define THREAD_CONVERTER_MAX_RETRY                  300

enum                        e_role
{
    DOWNLOADER,
    CONVERTER
};

struct                      s_workinfo
{
    t_opt                   *opt;
    struct s_worker         *worker;
};

struct                      s_worker
{
    pthread_t               id;
    enum e_role             job;
    void                    (*job_process)(struct s_workinfo *);
    t_video                 *video;
    t_process               *process;
};

struct                      s_mutlist
{
    pthread_mutex_t         process_mutex;
    pthread_mutex_t         opt_mutex;
    pthread_mutex_t         output_file_mutex;
};

typedef struct s_worker     t_worker;
typedef struct s_workinfo   t_workinfo;
typedef struct s_mutlist    t_mutlist;

void                        download_videos(t_process *process, t_opt *opt);
void                        download_job(struct s_workinfo *workinfo);
void                        convert_job(struct s_workinfo *workinfo);

#endif /* !DOWNLOADER_DOWNLOAD_H */
