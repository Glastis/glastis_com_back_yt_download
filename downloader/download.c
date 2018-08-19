/*
** Created by Glastis on 18/08/18.
*/

#define _BSD_SOURCE

#include <unistd.h>
#include <stdio.h>
#include "header/download.h"
#include "header/utilities.h"

t_mutlist                   *mutlist;

static void                 init_mutlist()
{
    mutlist = safe_malloc(1, sizeof(t_mutlist));
    pthread_mutex_init(&mutlist->process_mutex, NULL);
    pthread_mutex_init(&mutlist->opt_mutex, NULL);
    pthread_mutex_init(&mutlist->output_file_mutex, NULL);
}

static t_workinfo           **init_workinfo(t_process *process, t_opt *opt)
{
    t_workinfo              **workinfo;
    t_workinfo              *workinfo_tmp;
    t_worker                *worker;
    unsigned int            i;
    unsigned int            total_threads;

    total_threads = opt->thread_amount_download + opt->thread_amount_convert;
    i = 0;
    workinfo = safe_malloc(total_threads, sizeof(t_workinfo *));
    while (i < total_threads)
    {
        workinfo_tmp = safe_malloc(1, sizeof(t_workinfo));
        worker = safe_malloc(1, sizeof(t_worker));
        worker->process = process;
        worker->video = NULL;
        worker->job = (i < opt->thread_amount_download) ? DOWNLOADER : CONVERTER;
        worker->job_process = (i < opt->thread_amount_download) ? &download_job : &convert_job;
        workinfo_tmp->worker = worker;
        workinfo_tmp->opt = opt;
        workinfo[i] = workinfo_tmp;
        ++i;
    }
    return (workinfo);
}

static t_video              *get_unprocessed_video(t_worker *worker, int wait)
{
    unsigned int            i;
    int                     ended;

    ended = TRUE;
    i = 0;
    if (wait)
    {
        usleep(THREAD_CONVERTER_WAIT_DELAY);
    }
    pthread_mutex_lock(&mutlist->process_mutex);
    while (i < worker->process->video_amount)
    {
        printf("%s\n", (worker->job == DOWNLOADER)  ? "DOWN" : "conv");
        if ((worker->job == DOWNLOADER && !worker->process->video[i]->downloaded) || (!worker->process->video[i]->converted))
        {
            if (worker->job == CONVERTER && !worker->process->video[i]->download_ended)
            {
                ended = FALSE;
            }
            else
            {
                if (worker->job == DOWNLOADER)
                {
                    worker->process->video[i]->downloaded = TRUE;
                }
                else
                {
                    worker->process->video[i]->converted = TRUE;
                }
                pthread_mutex_unlock(&mutlist->process_mutex);
                return (worker->process->video[i]);
            }
        }
        ++i;
    }
    pthread_mutex_unlock(&mutlist->process_mutex);
    return ((ended) ? NULL : get_unprocessed_video(worker, TRUE));
}

void                        download_job(t_workinfo *workinfo)
{
    printf("Downloading %s\n", workinfo->worker->video->id);
    pthread_mutex_lock(&mutlist->process_mutex);
}

void                        convert_job(t_workinfo *workinfo)
{
    printf("Converting %s\n", workinfo->worker->video->id);
}

static void                 *search_job(void *workinfo_arg)
{
    t_workinfo              *workinfo;

    workinfo = (t_workinfo *) workinfo_arg;
    while ((workinfo->worker->video = get_unprocessed_video(workinfo->worker, FALSE)))
    {
        workinfo->worker->job_process(workinfo);
    }
    pthread_exit(NULL);
}

void                        download_videos(t_process *process, t_opt *opt)
{
    t_workinfo              **workinfo;
    unsigned int            i;

    i = 0;
    init_mutlist();
    workinfo = init_workinfo(process, opt);
    while (i < (opt->thread_amount_download + opt->thread_amount_convert))
    {
        pthread_create(&workinfo[i]->worker->id, NULL, &search_job, workinfo[i]);
        ++i;
    }
    while (i < process->video_amount)
    {
        pthread_join(workinfo[i]->worker->id, NULL);
        ++i;
    }
}