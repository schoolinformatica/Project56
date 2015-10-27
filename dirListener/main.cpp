#include <iostream>
#include <thread>
#include <dirent.h>
#include <vector>
#include <stdio.h>
#include <unistd.h>

using namespace std;


string checkForNewFiles(vector<string> oldList);

string checkForNewFiles(vector<string> oldList, vector<string> newList)
{

}

//null als standaardparam zodat de param optioneel is
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
            FileList.push_back(ent->d_name);
            printf(ent->d_name);
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

int main()
{
    while(true)
    {
        vector<string> oldFileList = getDirFileList("/home/robert/");
        thread t1(getDirFileList, "/home/robert/");
        t1.join();
        sleep(2);
        vector<string> newFileList = getDirFileList("/home/robert/");
        if(oldFileList.size() < newFileList.size());
        {
            printf("NEW FILE ADDED");
            //newFileList[newFileList.size() - 1] doorpipen
        }
    }
    return 0;
}