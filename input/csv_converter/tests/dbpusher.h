#ifndef dbpusher
#define dbpusher

#include "mock_pgsqlcon.h"
#include "../helperfunc/helperfunc.h"
#include <algorithm>
#include <string.h>
#include <thread>

using namespace std;

string createQuery(string pathToFile, string table)
{
    string tablename = table.substr(0, table.length() - 4);
    //substringing to get rid of '.csv'
    return "DELETE FROM " + tablename + ";" "" + " COPY " + tablename + " FROM \'" + pathToFile + "\' DELIMITER ';' CSV HEADER";
}

string extractCsvFileName(string fullPathToCsvFile)
{
    //Find last backslash in string, return everything after that
    size_t found = fullPathToCsvFile.find_last_of("/\\");
    return fullPathToCsvFile.substr(found + 1);
}

int push_list_to_database(string pathToFile)
{
    mock_pgsqlcon p;

    string csvName = extractCsvFileName(pathToFile);

    if (csvName.compare("") != 0)
    {
        //0 == strings are equal
        if(csvName.compare("positions.csv") == 0)
        {
            p.mock_exec_none_transaction(createQuery(pathToFile, csvName));

            cout << "CSV file entered." << endl;
        }
        else if(csvName.compare("connections.csv") == 0)
        {
            p.mock_exec_none_transaction(createQuery(pathToFile, csvName));
            cout << "CSV file entered." << endl;
        }
        else if(csvName.compare("monitoring.csv") == 0)
        {
            p.mock_exec_none_transaction(createQuery(pathToFile, csvName));
            cout << "CSV file entered." << endl;
        }
        else if(csvName.compare("events.csv") == 0)
        {
            p.mock_exec_none_transaction(createQuery(pathToFile, csvName));
            cout << "CSV file entered." << endl;
        }
        return 1;
    }
    else
    {
        cout << "CSV file not recognized as CityGis CSV file." << endl;
        return 0;
    }
}


#endif
