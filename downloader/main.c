/*
** Created by Glastis on 30/07/18.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "header/main.h"
#include "header/get_list_info.h"
#include "header/utilities.h"
#include "header/download.h"

static void                 init_opt(t_opt *opt)
{
    opt->list_filepath = NULL;
    opt->progress_filepath = NULL;
    opt->download = 0;
    opt->convert = 0;
    opt->thread_amount_download = THREAD_DEFAULT_DOWNLOAD;
    opt->thread_amount_convert = THREAD_DEFAULT_CONVERT;
}

static void                 get_opt(t_opt *opt, char **av)
{
    int                     i;

    i = 1;
    init_opt(opt);
    while (av[i])
    {
        if (!strcmp(OPT_COMPLETION_DOWNLOAD, av[i]) || !strcmp(OPT_COMPLETION_DOWNLOAD_SHOT, av[i]))
        {
            opt->download = 1;
        }
        else if (!strcmp(OPT_COMPLETION_CONVERT, av[i]) || !strcmp(OPT_COMPLETION_CONVERT_SHOT, av[i]))
        {
            opt->convert = 1;
        }
        else if (!strcmp(OPT_HELP, av[i]) || !strcmp(OPT_HELP_SHOT, av[i]))
        {
            print_help();
            exit(0);
        }
        else if (!opt->list_filepath)
        {
            opt->list_filepath = av[i];
        }
        else if (!opt->progress_filepath)
        {
            opt->progress_filepath = av[i];
        }
        else
        {
            fprintf(stderr, "%s: %s\n", av[i], ERROR_ARGUMENT_IGNORED);
        }
        ++i;
    }
}

static void                 check_opt(t_opt *opt)
{
    if (opt->thread_amount_download < THREAD_MIN_DOWNLOAD || opt->thread_amount_convert < THREAD_MIN_CONVERT)
    {
        error(ERROR_BAD_TREAD_AMOUNT);
    }
}

int                         main(int ac, char **av)
{
    t_opt                   opt;
    t_process               process;

    get_opt(&opt, av);
    check_opt(&opt);
    get_process(&opt, &process);
//    puts_all_vid_info(&process);
    download_videos(&process, &opt);
    return (0);
}