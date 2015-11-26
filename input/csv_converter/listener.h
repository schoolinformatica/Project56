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
#include <thread>
#include "csvreader.h"
#include "filedatabase/filedatabase.h"


#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

using namespace std;

string get_file_name(string file) {
    stringstream ss(file);
    string column;
    while(getline(ss, column, '.')) {
        return column;
    }
}

int listener(string path) {
    int length, i = 0;
    int fd;
    int wd;
    char buffer[BUF_LEN];

    fd = inotify_init();

    if (fd < 0) {
        perror("inotify_init");
    }

    wd = inotify_add_watch(fd, path.c_str(), IN_CLOSE_WRITE | IN_MOVED_TO);
    length = read(fd, buffer, BUF_LEN);

    if (length < 0) {
        perror("read");
    }

    while (i < length) {
        struct inotify_event *event = (struct inotify_event *) &buffer[i];
        if (event->len) {
            if (event->mask & IN_MOVED_TO) {
                if (event->mask & IN_ISDIR) {

                }
                else {

                    if (strstr(event->name, ".csv") != NULL) {
                        thread t1(csvreader, path + event->name, get_file_name(event->name));
                        t1.detach();
                    }
                    else {
                        cout << "non valid csv file!" << endl;
                    }
                }
            }
            else if (event->mask & IN_CLOSE_WRITE) {
                if (event->mask & IN_ISDIR) {

                }
                else {

                    if (strstr(event->name, ".csv") != NULL) {
                          thread t1(csvreader, path + event->name, get_file_name(event->name));
                          t1.detach();
                    }
                    else {
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
