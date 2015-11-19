#ifndef filedatabase
#define filedatabase

#define EOI "end of info" /* End of info section */
#define EOH "--------" /* End of header section */

#include "fdbhelperfunc.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include <thread>
#include <string.h>

using namespace std;


/*
 * @table -> table you want to update
 * @filenumber -> the last filenumber
 *
 * Method that updates the latest filenumber in the
 * filenumbers.fnb file. This file keeps track what
 * the latest filenumber is for all the tables.
 */
void update_latest_filenumber(string table, int filenumber) {
    vector<string> rows;
    ifstream myfile;
    ofstream newfile;
    string column;

    bool found = false;

    //Get the data that is already stored in the file
    myfile.open(storage_path + "filenumbers.fnb");
    while (getline(myfile, column, ';')) {
        rows.push_back(column);
        if (column.find(table) != string::npos) {
            getline(myfile, column, ';');
            rows.push_back(int_to_string(filenumber));
            found = true;
        }
    }

    //If the file didn't contain the table, add it
    if (!found) {
        rows.push_back(table);
        rows.push_back(int_to_string(filenumber));
    }

    myfile.close();

    //Write the old + new/updated data to the file
    newfile.open(storage_path + "filenumbers.fnb");
    for (int i = 0; i < rows.size(); i++) {
        newfile << rows[i] << ";";
    }

    newfile.close();
}

/*
 * @table -> table you want to last filenumber from
 *
 * Method that returns the filenumber of the last file
 * of a specific table
 */
int get_latest_filenumber(string table) {
    if (exist(storage_path + "filenumbers.fnb")) {
        string column;
        ifstream myfile;
        myfile.open(storage_path + "filenumbers.fnb");
        while (getline(myfile, column, ';')) {
            if (column.find(table) != string::npos) {
                getline(myfile, column, ';');
                myfile.close();
                return atoi(column.c_str());
            }
        }
        myfile.close();
        return 0;

    } else {
        return 0;
    }
}


/*
 * @table -> name of the table that should be indexed
 * @filenumber -> number of the file that should be indexed
 * @index_data -> the data that should be indexed
 *
 * This method checks what data should be indexed. If there
 * is data that should be indexed it updates the index of
 * the corresponding table.
 */
void create_index(string table, int filenumber, map<string, vector<string>> index_data) {
    vector<string> index_one, index_two, headers;
    string column;
    ofstream index;

    //Path to the index
    string path = storage_path + table + "-index.fdi";

    //Get the columns that should be indexed
    vector<string> indexed_columns = get_indexed_columns(get_table(table));

    //Combine the lists together
    for (map<string, vector<string>>::iterator ii = index_data.begin(); ii != index_data.end(); ii++) {
        if (ii->first.find(indexed_columns.front()) != string::npos) {
            index_one = combine_lists_dif(index_one, ii->second);
        }

        if (ii->first.find(indexed_columns.back()) != string::npos) {
            index_two = combine_lists_dif(index_two, ii->second);
        }
    }

    //If the index file does not exist, create a new one
    if (!exist(path)) {
        index.open(path);
        index << "file" << ";";
        for (int j = 0; j < indexed_columns.size(); j++) {
            index << indexed_columns[j] << ";";
        }
        index << endl;
        index << EOH << ";" << endl;
    } else {
        index.open(path, std::fstream::app);
    }

    //Add the data to the index file
    index << filenumber << ";";
    index << list_to_string(remove_duplicates(index_one)) << ";";
    index << list_to_string(remove_duplicates(index_two)) << ";";
    index << endl;

    index.close();
}

/*
 * @rows -> The data that should be converted to fdb files
 * @table -> The name of the table where the data should be inserted
 *
 * This method creates fdb files and fills them with the data.
 * It devides the data over multiple files, so reading the files
 * shouldn't take too long.
 */
void insert(vector<map<string, string>> rows, string table) {
    ofstream myfile;
    vector<string> headers = get_table(table);
    vector<string> indexed_columns = get_indexed_columns(headers);
    map<string, vector<string>> index;
    vector<string> index_one, index_two;

    cout << "start converting to .fdb" << endl;

    int fileversion;

    //Iterate over the data. Each entry is a column.
    for (int i = 0; i < rows.size(); i++) {

        //Make a new file after every x lines
        if (i % 100000 == 0) {
            fileversion = i / 100000 + 1 + get_latest_filenumber(table);

            //If it isn't the first file, the last file should be indexed
            if (i > 0) {
                index.insert(pair<string, vector<string>>(indexed_columns.front(), index_one));
                index.insert(pair<string, vector<string>>(indexed_columns.back(), index_two));
                thread first(create_index, table, fileversion - 1, index);
                first.detach();
                index_one.clear();
                index_two.clear();
                index.clear();
            }

            //Create new file
            stringstream ss;
            ss << fileversion;
            myfile.close();
            myfile.open(storage_path + table + "-" + ss.str() + ".fdb");

            //Add headers to the new file
            for (int i = 0; i < headers.size(); i++) {
                myfile << headers[i] << ";";
            }
            myfile << endl;
            myfile << EOH << endl;
        }

        //Fill the file with the data
        for (map<string, string>::iterator ii = rows.at(i).begin(); ii != rows.at(i).end(); ii++) {

            myfile << ii->second << ";";

            //Keep track of the data that should be indexed
            for (int j = 0; j < 2; ++j) {
                if (indexed_columns[j].find(ii->first) != string::npos && j == 0)
                    index_one.push_back(ii->second);
                if (indexed_columns[j].find(ii->first) != string::npos && j == 1)
                    index_two.push_back(ii->second);
            }
        }
        myfile << endl;
    }
    myfile.close();

    index.insert(pair<string, vector<string>>(indexed_columns.front(), index_one));
    index.insert(pair<string, vector<string>>(indexed_columns.back(), index_two));

    //Create index
    create_index(table, fileversion, index);

    index_one.clear();
    index_two.clear();
    index.clear();

    //Update the last filenumber file
    update_latest_filenumber(table, fileversion);

    cout << "end of converting" << endl;
}


#endif
