/*
** Created by Glastis on 30/07/18.
*/

#ifndef DOWNLOADER_GET_LIST_INFO_H
#define DOWNLOADER_GET_LIST_INFO_H

#define READ_SIZE                                   1024
#define SEPARATOR                                   '\n'
#define ID_ARGUMENT_URL_BEG                         "v="
#define ID_ARGUMENT_URL_END                         "&"
#define ID_ARGUMENT_LEN_MIN                         5u
#define ID_ARGUMENT_LEN_MAX                         14u
#define YOUTUBE_FETCH_INFO_URL                      "https://www.googleapis.com/youtube/v3/videos?part=snippet&key=AIzaSyCC54endL40nIdYj5V-3sEsBNRSNfoHjWk&id="
#define CURL_USER_AGENT                             "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/67.0.3396.87 Safari/537.36 OPR/54.0.2952.64"
#define YOUTUBE_JSON_TITLE_BEG                      "\"title\": \""
#define YOUTUBE_JSON_TITLE_END                      "\","
#define ERROR_FILE_OPENING                          "Failed to open file"

#include "process.h"

void                        get_process(t_opt *opt, t_process *process);
int                         add_video(t_process *process, char *id);
void                        puts_all_vid_info(t_process *process);
void                        puts_vid_info(t_video *vid);

#endif /* !DOWNLOADER_GET_LIST_INFO_H */
