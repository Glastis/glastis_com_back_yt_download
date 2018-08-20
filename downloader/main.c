/*
** Created by Glastis on 30/07/18.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "header/accepted_formats.h"
#include "header/main.h"
#include "header/get_list_info.h"
#include "header/utilities.h"
#include "header/download.h"
#include "header/trace.h"

#ifndef TRACE_DEBUG
void                        debug_init()
{

}
#endif

static void                 init_opt(t_opt *opt)
{
    opt->list_filepath = NULL;
    opt->progress_filepath = NULL;
    opt->output_format = NULL;
    opt->output_format_type = DEFAULT;
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
        if (!strcmp(OPT_COMPLETION_FORMAT, av[i]) || !strcmp(OPT_COMPLETION_FORMAT_SHOT, av[i]))
        {
            if (!av[i + 1])
            {
                fprintf(stderr, "%s", av[i]);
                error(ERROR_ARGUMENT_VALUE);
            }
            ++i;
            opt->output_format = av[i];
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

static enum e_format        check_opt_format(char *format)
{
    unsigned int            i;

    i = 0;
    while (ACCEPTED_FORMATS_AUDIO[i] || ACCEPTED_FORMATS_VIDEO[i])
    {
        if (ACCEPTED_FORMATS_AUDIO[i] && !strcmp(ACCEPTED_FORMATS_AUDIO[i], format))
        {
            return (AUDIO);
        }
        else if (ACCEPTED_FORMATS_VIDEO[i] && !strcmp(ACCEPTED_FORMATS_VIDEO[i], format))
        {
            return (VIDEO);
        }
        ++i;
    }
    fprintf(stderr, "%s: ", format);
    error(ERROR_ARGUMENT_BAD_FORMAT);
    return (DEFAULT);
}

static void                 check_opt(t_opt *opt)
{
    if (opt->thread_amount_download < THREAD_MIN_DOWNLOAD || opt->thread_amount_convert < THREAD_MIN_CONVERT)
    {
        error(ERROR_BAD_TREAD_AMOUNT);
    }
    if (opt->output_format)
    {
        opt->output_format_type = check_opt_format(opt->output_format);
    }
}

int                         main(int ac, char **av)
{
    t_opt                   opt;
    t_process               process;

    UNUSED(ac);
    debug_init();
    get_opt(&opt, av);
    check_opt(&opt);
    get_process(&opt, &process);
    download_videos(&process, &opt);
    return (0);
}