#include <iostream>
#include <thread>
#include <dirent.h>
#include <vector>
#include <stdio.h>
#include <unistd.h>

using namespace std;

//this method returns a vector containg all the files in the given directory.
vector<const char*> getDirFileList(const char* directory)
{
    DIR *dir;
    vector<const char*> FileList;
    struct dirent *ent;

    if ((dir = opendir (directory)) != NULL)
    {
        //we loop through the given directory and add all the files we find to our FileList
        while ((ent = readdir (dir)) != NULL)
        {
            FileList.push_back(ent->d_name);
		cout << ent->d_name << endl;
//            printf(ent->d_name);
        }
        //When we scanned all the files, we close the directory and return the list
        closedir (dir);
        return FileList;
    }
    else
    {
        //We were not able to find the directory and return an error
        perror ("");
        return FileList;
    }
}

int main()
{
    while(true)
    {
        //We create a vector that holds the list of files and dirs BEFORE the 2 second loop
        vector<const char*> oldFileList = getDirFileList("/home/cooperatio/");
        thread t1(getDirFileList, "/home/cooperatio/");
        t1.join();
        sleep(2);
        //We redo this procedure AFTER the 2 seconds have passed
        vector<const char*> newFileList = getDirFileList("/home/cooperatio/");

        //Then, we check wether the newList is larger than the old one. If so, new files have been added!
        if(oldFileList.size() < newFileList.size());
        {
            //We create a const char that contains the last element in the newFileList(the file that has been added, and convert it to a string.
            //Note: We do not take any measures to ensure that only .csv files will be handled, since the web interface will provide this constraint.
            const char* FileChar = newFileList.back();
            string str(FileChar);
cout << FileChar << endl;
//            printf(FileChar);
        }
    }
    return 0;
}