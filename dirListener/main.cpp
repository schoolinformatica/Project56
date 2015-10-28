#include <iostream>
#include <thread>
#include <dirent.h>
#include <vector>
#include <unistd.h>
#include "csvreader.h"

using namespace std;

//this method returns a vector containing all the files in the given directory.
vector<const char *> getDirFileList(const char *directory) {
    DIR *dir;
    vector<const char *> FileList;
    struct dirent *ent;

    if ((dir = opendir(directory)) != NULL) {
        //we loop through the given directory and add all the files we find to our FileList
        while ((ent = readdir(dir)) != NULL) {
            FileList.push_back(ent->d_name);

        }
        //When we scanned all the files, we close the directory and return the list
        closedir(dir);
        return FileList;
    }
    else {
        //We were not able to find the directory and return an error
        perror("");
        return FileList;
    }
}

int main() {
    vector<const char *> oldFileList;
    vector<const char *> newFileList;
    newFileList = getDirFileList("/home/cooperatio");

    while (true)
    {
        //We create a vector that holds the list of files and dirs BEFORE the 2 second loop
        oldFileList = newFileList;
        sleep(1);
        //We redo this procedure AFTER the 2 seconds have passed
        newFileList = getDirFileList("/home/cooperatio/");
        sleep(1);
        cout << "----------------------------------------" << endl;

        //Then, we check wether the newList is larger than the old one. If so, new files have been added!
        if (newFileList.size() > oldFileList.size()) {
            for (int i = 0 ; i < newFileList.size(); i ++){
               cout << newFileList.at(i) <<endl;

            }

            cout << "now the old is coming"  << endl;

            for (int i = 0 ; i <  oldFileList.size() ; i ++){
                cout << oldFileList.at(i) <<  endl;
            }
            //We create a const char that contains the last element in the newFileList(the file that has been added, and convert it to a string.
            //Note: We do not take any measures to ensure that only .csv files will be handled, since the web interface will provide this constraint.
            const char *FileChar = newFileList.back();
            string FileString(FileChar);
            //Finally, we add our servers' home directory (where we will be storing our .csv files) to the FileString so we have a complete path.
            string FinalFileString = "/home/cooperatio/" + FileString;
            //And then we call ouCSV-parsing method from our header file
            cout << "----------------test----------------" << endl;
            csvreader(FinalFileString);
        }
        break;
    }
    for (int i = 0 ; i < newFileList.size(); i ++){
        cout << newFileList.at(i) <<endl;

    }

    cout << "now the old is coming"  << endl;

    for (int i = 0 ; i <  oldFileList.size() ; i ++){
        cout << oldFileList.at(i) <<  endl;
    }

    return 0;
}