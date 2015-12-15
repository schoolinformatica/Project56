#ifndef dbpusher
#define dbpusher

#include "../pqcon/pgsqlcon.h"
#include "../helperfunc/helperfunc.h"
#include <algorithm>
#include <string.h>
#include <thread>

using namespace std;

string createQuery(string pathToFile, string table) {
    return "COPY " + table + " FROM \'" + pathToFile + "\' DELIMITER ';' CSV HEADER";
}

string extractCsvFileName(string fullPathToCsvFile) {
    //Find last backslash in string, return everything after that
    size_t found = fullPathToCsvFile.find_last_of("/\\");
    return fullPathToCsvFile.substr(found + 1);
}

void push_list_to_database(string pathToFile) {
    Pgsqlcon p;

    string csvName = extractCsvFileName(pathToFile);

    //TODO: Make sure DB matches CSV Files as far as tables and their columsn are concerned
    if (csvName.compare("") != 0) {
        //0 == strings are equal
        if (csvName.compare("positions.csv") == 0) {
            p.exec_none_transaction(createQuery(pathToFile, "positions"));
        }
        else if (csvName.compare("connections.csv") == 0) {
            p.exec_none_transaction(createQuery(pathToFile, "connections"));
        }
        else if (csvName.compare("monitoring.csv") == 0) {
            p.exec_none_transaction(createQuery(pathToFile, "monitoring"));
        }
        else if (csvName.compare("events.csv") == 0) {
            p.exec_none_transaction(createQuery(pathToFile, "events"));
        }
    }
    else {
        cout << "CSV file not recognized as CityGis CSV file." << endl;
    }
}


#endif
