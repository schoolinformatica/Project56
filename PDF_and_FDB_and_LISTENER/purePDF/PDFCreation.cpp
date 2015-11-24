#include <iostream>
#include <sys/stat.h>
#include "filedatabase/fdbread.h"
#include "filedatabase/filedatabase.h"
#include "csvreader.h"

using namespace std;

//Method to check wether a given file exists.
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
            //We are dealing with an FDB file.
            //We call the CSVReader which converts the file to FDB.
            //And at the same time we create a PDF from the return value of CSVReader. Neat, eh?
            //TODO: MAKE SURE THIS PATH IS RIGHT FOR THE SERVER
	    string path = "/var/www/laravel/storage/uploads/" + csvfile;
            pdfcreator(csvreader(path));
        }
        else
        {
            //Not a valid file.
        }
    }
    return 0;

}

