#ifndef fdbread
#define fdbread

#include "fdbhelperfunc.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <thread>

using namespace std;

// Vector containg all the selected data
vector<string> data;

/*
 * @index -> index values you want to get the rows from
 * @table -> what table you want to get
 *
 * This method gets the files that has te be read
 * to retreive the selected data.
 */
vector<string> get_files_index(string index, string table) {
    vector<string> files;
    int index_place;
    string filenumber;
    string column;
    ifstream file;

    string path_to_index = storage_path + table + "-index.fdi";

    bool endheader = false;

    // Open index file
    file.open(path_to_index);

    // Get the file corresponding to the index
    for (int i = 0; getline(file, column, ';'); i++) {
        if (endheader) {
            if(i % 3 == 0)
                filenumber = column;
            else if (i % 2 == 0) {
                if (in_list(toList(column, ','), index) || index.find("*") != string::npos)
                    files.push_back(filenumber);
            }

        }

        // Find the end of the header
        if (column.find(EOH) != string::npos) {
            endheader = true;
            i = -1;
        }
    }

    return files;
}

/*
 * @table -> table you want to get the files from
 * @index_one -> index one
 * @index_two -> index two
 *
 * This method gets the files that has te be read.
 * It combines the two indexes together.
 */
vector<string> get_files_to_read(string table, string index_one, string index_two) {
    vector<string> files;

    if (index_one != "*" && index_two != "*")
        files = combine_lists_same(get_files_index(index_one, table),
                                   get_files_index(index_two, table));
    else if (index_one != "*")
        files = get_files_index(index_one, table);
    else if (index_two != "*")
        files = get_files_index(index_two, table);
    else
        files = get_files_index("*", table);

    return files;
}
//TODO:  Make list of indexes
/*
 * @file -> the file you want to select data from
 *
 * This method reads the data from the file and adds it
 * to the vector.
 */
void push_data_to_list(string file) {

    vector<string> temp_data = read_data(file);
    data.insert(data.end(), temp_data.begin(), temp_data.end());
    temp_data.clear();
}

/*
 * @table -> table you want to select data from
 * @index_one -> index one (format: "value1, value2" or "*")
 * @index_two -> index two (format: "value1, value2" or "*")
 *
 * value1 => left boundarie
 * value2 => right boundarie
 * single_value => just that value
 * '*' => everything
 *
 * This method retreives the data from the given table
 * according to the given indexes. This method should
 * be called to select data.
 */
vector<string> select(string table, string index_one, string index_two) {
    vector<string> files = get_files_to_read(table, index_one, index_two);

    for (int i = 0; i < files.size(); i++) {
        string path = storage_path + table + "-" + trim_string(files[i]) + ".fdb";
        push_data_to_list(path);
    }


    return data;
};


#endif