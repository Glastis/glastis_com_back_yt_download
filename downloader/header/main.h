/*
** Created by Glastis on 30/07/18.
*/

#ifndef DOWNLOADER_MAIN_H
#define DOWNLOADER_MAIN_H

#define OPT_COMPLETION_FORMAT                       "--format"
#define OPT_COMPLETION_FORMAT_SHOT                  "-f"
#define OPT_HELP                                    "--help"
#define OPT_HELP_SHOT                               "-h"

#define ERROR_ARGUMENT_IGNORED                      "Argument ignored. See --help or -h to get usage."
#define ERROR_ARGUMENT_VALUE                        "Argument must be followed by value. See --help or -h to get usage."
#define ERROR_BAD_TREAD_AMOUNT                      "Thread number must be more than 0"
#define ERROR_ARGUMENT_BAD_FORMAT                   "Unknown or invalid format."


#define THREAD_DEFAULT_DOWNLOAD                     4u
#define THREAD_DEFAULT_CONVERT                      4u
#define THREAD_MIN_DOWNLOAD                         1u
#define THREAD_MIN_CONVERT                          1u

int                         main(int ac, char **av);

#endif /* !DOWNLOADER_MAIN_H */
