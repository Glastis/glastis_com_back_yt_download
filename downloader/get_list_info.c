/*
** Created by Glastis on 30/07/18.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "header/get_list_info.h"
#include "header/utilities.h"

static void                 init_process(t_process *process)
{
    process->video = NULL;
    process->video_amount = 0;
}

static t_video              *init_video()
{
    t_video                 *video;

    video = safe_malloc(1, sizeof(t_video));
    video->id = NULL;
    video->converted = FALSE;
    video->downloaded = FALSE;
    video->download_ended = FALSE;
    return (video);
}

int                         is_existing_video(t_process *process, char *id)
{
    unsigned int            i;

    i = 0;
    while (i < process->video_amount)
    {
        if (!strcmp(process->video[i]->id, id))
        {
            return (TRUE);
        }
        ++i;
    }
    return (FALSE);
}

static size_t               curl_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t                  new_size;
    t_str                   *str;

    str = (t_str *)userp;
    new_size = size * nmemb;
    str->data = safe_realloc(str->data, str->len + new_size + 1, sizeof(char));
    memcpy(&(str->data[str->len]), contents, new_size);
    str->len += new_size;
    str->data[str->len] = '\0';
    return new_size;
}

static char                 *get_video_title_from_request(char *json)
{
    unsigned int            i;
    unsigned int            saved;
    char                    tmp;
    char                    *title;

    i = 0;
    title = NULL;
    while (json[i] && !comp_str(&json[i], YOUTUBE_JSON_TITLE_BEG))
    {
        ++i;
    }
    if (str_greater_than(&json[i], sizeof(YOUTUBE_JSON_TITLE_BEG)))
    {
        i += sizeof(YOUTUBE_JSON_TITLE_BEG) - 1;
        saved = i;
        while (json[i] && !comp_str(&json[i], YOUTUBE_JSON_TITLE_END))
        {
            ++i;
        }
        tmp = json[i];
        json[i] = '\0';
        title = safe_malloc(i - saved + 1, sizeof(char));
        memcpy(title, &json[saved], i - saved);
        title[i - saved] = '\0';
        json[i] = tmp;
    }
    free(json);
    return (title);
}

char                        *get_video_title(char *id)
{
    char                    *url;
    CURL                    *curl_handle;
    CURLcode                res;
    t_str                   str;

    str_init(&str);
    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();
    if (curl_handle)
    {
        str.data = safe_malloc(1, sizeof(char));
        url = str_coupler(YOUTUBE_FETCH_INFO_URL, id);
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, curl_callback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&str);
        curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, CURL_USER_AGENT);
        res = curl_easy_perform(curl_handle);
        free(url);
        if (res == CURLE_OK)
        {
            curl_easy_cleanup(curl_handle);
            curl_global_cleanup();
            return (get_video_title_from_request(str.data));
        }
    }
    return (NULL);
}

void                        puts_vid_info(t_video *vid)
{
    printf("vid id: %s\n", vid->id);
    printf("vid title: %s\n", vid->title);
}

void                        puts_all_vid_info(t_process *process)
{
    unsigned int            i;

    i = 0;
    if (!process || !process->video)
    {
        return;
    }
    while (i < process->video_amount)
    {
        puts_vid_info(process->video[i]);
        ++i;
    }
}

int                         add_video(t_process *process, char *id)
{
    char                    *title;
    t_video                 *vid;

    title = get_video_title(id);
    if (title)
    {
        process->video = safe_realloc(process->video, (size_t) (process->video_amount + 1), sizeof(t_video *));
        vid = init_video();
        vid->id = id;
        vid->title = title;
        process->video[process->video_amount] = vid;
        ++process->video_amount;
        return (TRUE);
    }
    free(id);
    return (FALSE);
}

static char                 *extract_id_check_retval(char *str, unsigned int i)
{
    if (i < ID_ARGUMENT_LEN_MIN || i > ID_ARGUMENT_LEN_MAX)
    {
        return (NULL);
    }
    return (str_coupler(str, NULL));
}

static char                 *extract_id(char *url)
{
    unsigned int            i;

    i = 0;
    while (url[i])
    {
        if (comp_str(&url[i], ID_ARGUMENT_URL_BEG) && url[i + 1] && url[i + 2])
        {
            url = &url[i + safe_strlen(ID_ARGUMENT_URL_BEG)];
            i = 0;
            while (url[i] && !comp_str(&url[i], ID_ARGUMENT_URL_END))
            {
                ++i;
            }
            return (extract_id_check_retval(url, i));
        }
        ++i;
    }
    return (extract_id_check_retval(url, i));
}

static void                 parse_video_list(t_process *process, char *raw)
{
    unsigned int            i;
    unsigned int            last;
    char                    *id;

    i = 0;
    last = 0;
    while (raw[i])
    {
        if (raw[i] == SEPARATOR)
        {
            raw[i] = '\0';
            id = extract_id(&raw[last]);
            if (id && !is_existing_video(process, id))
            {
                add_video(process, id);
            }
            else if (id)
            {
                free(id);
            }
            raw[i] = '\n';
            last = i + 1;
        }
        ++i;
    }
}

static void                 get_video_from_file(char *filename, t_process *process)
{
    int                     fd;
    char                    *buff;
    unsigned int            readed;
    int                     buff_size;

    buff_size = 0;
    if (!(fd = open(filename, O_RDONLY)))
    {
        buff = str_coupler(filename, ": ");
        buff = str_coupler(buff, strerror(errno));
        error(buff);
    }
    buff = safe_malloc(READ_SIZE + 1, sizeof(char));
    while ((readed = (unsigned int)read(fd, &buff[buff_size], READ_SIZE)) >= READ_SIZE)
    {
        buff_size += READ_SIZE;
        buff = safe_realloc(buff, (size_t) (buff_size + 1), sizeof(char));
    }
    close(fd);
    buff[buff_size + readed]  = '\0';
    parse_video_list(process, buff);
    free(buff);
}

void                        get_process(t_opt *opt, t_process *process)
{
    init_process(process);
    get_video_from_file(opt->list_filepath, process);
}