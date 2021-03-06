
//
// Created by ceesjan on 28-10-2015.
//

#ifndef Listener
#define Listener

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include "dbpusher/dbpusher.h"
#include <locale>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

using namespace std;

string strToLower(string str)
{
    locale loc;
    for (string::size_type i=0; i<str.length(); ++i)
        tolower(str[i],loc);
    return str;
}


int listener(string path) {

    int length, i = 0;
    int fd;
    int wd;
    char buffer[BUF_LEN];

    fd = inotify_init();

    if (fd < 0)
    {
        perror("inotify_init");
    }

    wd = inotify_add_watch(fd, path.c_str(),  IN_CLOSE_WRITE | IN_MOVE);
    length = read(fd, buffer, BUF_LEN);

    if (length < 0)
    {
        perror("read");
    }

    while (i < length)
    {
        struct inotify_event *event = (struct inotify_event *) &buffer[i];

        if (event->len)
        {

            
            if (event->mask & IN_MOVE)
            {
                if (event->mask & IN_ISDIR)
                {
                    printf("The directory %s was moved.\n", event->name);
                }
                else
                {
                    printf("The file %s was moved.\n", event->name);

                    if (strstr(event->name, ".csv") != NULL)
                    {
                        thread t1(push_list_to_database, path + event->name);
                        t1.detach();
                    }
                    else
                    {
                        cout << "non valid csv file!" << endl;
                    }
                }
            }

            else if (event->mask & IN_CLOSE_WRITE)
            {
                if (event->mask & IN_ISDIR)
                {
                    printf("The directory %s is done modifying.\n", event->name);
                }
                else
                {
                    printf("The file %s is done modifying.\n", event->name);

                    if (strstr(event->name, ".csv") != NULL)
                    {
                        thread t1(push_list_to_database, path + event->name);
                        t1.detach();
                    }
                    else
                    {
                        cout << "non valid csv file!" << endl;
                    }
                }

            }

        }
        i += EVENT_SIZE + event->len;
    }

    (void) inotify_rm_watch(fd, wd);
    (void) close(fd);

    listener(path);
}

#endif


