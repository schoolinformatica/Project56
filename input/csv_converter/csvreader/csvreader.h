#ifndef CSVReader
#define CSVReader

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "dbpusher.h"
#include <map>



using namespace std;


/*
 * @path -> full path to the csv file
 * @table -> table which the file is associated with
 *
 * This method reads the csv file and calls the insert()
 * method to convert all the data to our own file
 * format.
 *
 * This method returns 1 upon a successfull read, 0 upon any kind of failure
 */


int csvreader(string path, string table)
{
    cout << "CSV reader started!" << endl;
    if(!CheckIfFileExists(path.c_str()) || table.empty() == true)
    {
        cout << "Error: file not found or table not recognized" << endl;
        return 0;
    }
    else 
    {
        vector<string> row;
        stringstream ss;
        ifstream in;

        in.open(path);
        char delimiter = ';';
        bool inquotes = false;

        while (in.good()) {
            char c = in.get();
            if (!inquotes && c == '"') //beginquotechar
            {
                inquotes = true;
            }
            else if (inquotes && c == '"') //quotechar
            {
                if (in.peek() == '"')//2 consecutive quotes resolve to 1
                {
                    ss << (char) in.get();
                }
                else //endquotechar
                {
                    inquotes = false;
                }
            }
            else if (!inquotes && c == delimiter) //end of field
            {
                row.push_back(ss.str());
                ss.str("");
            }
            else if (!inquotes && (c == '\r' || c == '\n')) 
            {
                if (in.peek() == '\n') 
                { 
                    in.get(); 
                }
                row.push_back(ss.str());
                ss.str(string());
            }
            else
	    {
                ss << c;
            }
        }

        in.close();

        //Call the insert method
        push_list_to_database(row, table);

        //deleting the csv file
        cout << "deleting file" << endl;
        //remove(path.c_str());
	cout << "All done. CSV file removed and put into database" << endl;
        return 1;
    }
}


#endif
