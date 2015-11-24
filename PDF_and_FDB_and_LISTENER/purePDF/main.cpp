#include <iostream>
#include "listener.h"
#include "filedatabase.h"

using namespace std;
bool exists(const string& filename)
{
    struct stat statbuffer;
    return( stat(filename.c_str(), &statbuffer) == 0);
}

int main(string email, string csvfile) {
//Check wether file exists
    if(exists(csvfile) == true)
    {
        if(csvfile.find(".csv") != string::npos)
        {
            //We let the CSVReader process the file, pass it to PDFCreator and make a PDF out of it. 
	    //PDFCreator will call SendDirToPhp which will mail the file!
	    string path = "/var/www/laravel/storage/uploads/" + csvfile;
            csvreader(path, email);
        }
        else
        {
            //Not a valid file.
        }
    }
    return 0;
}

