/*
** Created by Glastis on 19/08/18.
*/


#include "header/trace.h"

#ifdef TRACE_DEBUG
#include <stdio.h>
#include <time.h>


static FILE                             *fp_trace;

void __attribute__ ((constructor))      trace_begin()
{
    fp_trace = fopen("trace.out", "w");
}

void __attribute__ ((destructor))       trace_end ()
{
    if (fp_trace)
    {
        fclose(fp_trace);
    }
}

void                                    __cyg_profile_func_enter (void *func,  void *caller)
{
    if (fp_trace)
    {
        fprintf(fp_trace, "e %p %p %lu\n", func, caller, time(NULL) );
    }
}

void                                    __cyg_profile_func_exit (void *func, void *caller)
{
    if (fp_trace)
    {
        fprintf(fp_trace, "x %p %p %lu\n", func, caller, time(NULL));
    }
}

#endif /* !TRACE_DEBUG */