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


#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

using namespace std;

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

    wd = inotify_add_watch(fd, path.c_str(), IN_MODIFY | IN_CREATE | IN_DELETE | IN_CLOSE_WRITE | IN_MOVE);
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
            if (event->mask & IN_CREATE)
            {
                if (event->mask & IN_ISDIR)
                {
                    printf("The directory %s was create.\n", event->name);
                }
                else
                {
                    printf("The file %s was created.\n", event->name);

                    if (strstr(event->name, ".csv") != NULL)
                    {
                        push_list_to_database(path + event->name);
                    }
                    else
                    {
                        cout << "non valid csv file!" << endl;
                    }
                }
            }

            else if (event->mask & IN_MODIFY)
            {
                if (event->mask & IN_ISDIR)
                {
                    printf("The directory %s was modified.\n", event->name);
                }
                else
                {
                    printf("The file %s was modified.\n", event->name);

                    if (strstr(event->name, ".csv") != NULL)
                    {
                        push_list_to_database(path + event->name);
                    }
                    else
                    {
                        cout << "non valid csv file!" << endl;
                    }
                }
            }

            else if (event->mask & IN_MOVE)
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
                        push_list_to_database(path + event->name);
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

                        push_list_to_database(path + event->name);
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
