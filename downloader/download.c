/*
** Created by Glastis on 18/08/18.
*/

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

static t_workinfo           *init_workinfo(t_process *process, t_opt *opt)
{
    t_workinfo              *workinfo;
    t_worker                *worker;
    unsigned int            i;
    unsigned int            total_threads;

    total_threads = opt->thread_amount_download + opt->thread_amount_convert;
    i = 0;
    workinfo = safe_malloc(total_threads, sizeof(t_workinfo));
    while (i < total_threads)
    {
        worker = safe_malloc(1, sizeof(t_worker));
        worker->process = process;
        worker->vid_id = NULL;
        worker->job = (i < opt->thread_amount_download) ? DOWNLOADER : CONVERTER;
        worker->job_process = (i < opt->thread_amount_download) ? &download_job : &convert_job;
        workinfo[i].worker = worker;
        workinfo[i].opt = opt;
        ++i;
    }
    return workinfo;
}

static char                 *get_unprocessed_video(t_worker *worker)
{
    int                     i;

    i = 0;
    pthread_mutex_lock(&mutlist->process_mutex);
    while (i < worker->process->video_amount)
    {
        if ((worker->job == DOWNLOADER && !worker->process->video[i]->downloaded) || (!worker->process->video[i]->converted))
        {
            pthread_mutex_unlock(&mutlist->process_mutex);
            return (worker->process->video[i]->id);
        }
        ++i;
    }
    pthread_mutex_unlock(&mutlist->process_mutex);
    return (NULL);
}

void                        download_job(t_workinfo *workinfo)
{

}

void                        convert_job(t_workinfo *workinfo)
{

}

static void                 *search_job(void *workinfo_arg)
{
    t_workinfo              *workinfo;

    workinfo = (t_workinfo *) workinfo_arg;
    while ((workinfo->worker->vid_id = get_unprocessed_video(workinfo->worker)))
    {
        workinfo->worker->job_process(workinfo);
    }
    pthread_exit(NULL);
}

void                        download_videos(t_process *process, t_opt *opt)
{
    t_workinfo              *workinfo;
    unsigned int            i;

    i = 0;
    init_mutlist();
    workinfo = init_workinfo(process, opt);
    while (i < opt->thread_amount_download)
    {
        pthread_create(&workinfo[i].worker->id, NULL, &search_job, &workinfo[i]);
        ++i;
    }
    while (i < process->video_amount)
    {
        pthread_join(workinfo[i].worker->id, NULL);
        ++i;
    }
}