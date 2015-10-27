#include <iostream>
#include <thread>
#include <dirent.h>
#include <vector>
#include <stdio.h>
#include <w32api/synchapi.h>

using namespace std;

vector<string> getDirFileList(const char* directory)
{
    DIR *dir;
    vector<string> FileList;
    struct dirent *ent;

    if ((dir = opendir (directory)) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL)
        {
            printf ("%s\n", ent->d_name);
            FileList.push_back(ent->d_name);
        }
        closedir (dir);
        return FileList;
    }
    else
    {
        /* could not open directory */
        perror ("");
        return FileList;
    }
}



int main() {

    vector<string> oldFiles = getDirFileList("home/robert/");
    while(true)
    {
        // Constructs the new thread and runs it. Does not block execution.
        thread t1(getDirFileList, "home/robert/");
        Sleep(2000);
    }
    // Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
    return 0;
}