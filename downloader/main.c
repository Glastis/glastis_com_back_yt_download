/*
** Created by Glastis on 30/07/18.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

static void             print_help()
{
    printf("%s\n", USAGE);
}

static void             init_opt(t_opt *opt)
{
    opt->id = NULL;
    opt->list_filepath = NULL;
    opt->progress_filepath = NULL;
    opt->download = 0;
    opt->convert = 0;
}

static void             get_opt(t_opt *opt, char **av)
{
    int                 i;

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
        else if (!opt->id)
        {
            opt->id = av[i];
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

int                     main(int ac, char **av)
{
    t_opt               opt;

    get_opt(&opt, av);
    return (0);
}