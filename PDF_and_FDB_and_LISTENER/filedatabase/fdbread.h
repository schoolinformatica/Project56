#ifndef fdbread
#define fdbread

#include "fdbhelperfunc.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <thread>

using namespace std;

vector<map<string, string>> data;

vector<string> get_files_index(string index, string table) {
    vector<string> files;
    int index_place;
    string filenumber;
    string column;
    ifstream file;

    string path_to_index = storage_path + table + "-index.fdi";
    vector<string> index_list = toList(index, ',');
    vector<string> header = read_header(path_to_index);
    bool startheader = false;

    for (int i = 0; i < header.size(); i++) {
        if (header[i].find(index_list[0]) != string::npos)
            index_place = i;
    }

    index_place = 3;

    file.open(path_to_index);
    for (int i = 0; getline(file, column, ';'); i++) {
        if (startheader) {
            if (i % 3 == 0)
                filenumber = column;
            if (i % index_place == 1) {
                if (in_list(toList(column, ','), index))
                    files.push_back(filenumber);
            }
        }

        if (column.find(EOH) != string::npos) {
            startheader = true;
            i = -1;
        }
    }

    return files;
}

vector<string> get_files_to_read(string table, string index_one, string index_two) {
    vector<string> files;

    if (index_one != "*" && index_two != "*")
        files = combine_lists_same(get_files_index(index_one, table),
                                   get_files_index(index_two, table));
    else if (index_one != "*")
        files = get_files_index(index_one, table);
    else
        files = get_files_index(index_two, table);

    return files;
}


void push_data_to_list(string file) {
    vector<map<string, string>> temp_data = read_data(file);
    data.insert(data.end(), temp_data.begin(), temp_data.end());
    temp_data.clear();
}


vector<map<string, string>> select(string table, string index_one, string index_two) {
    vector<string> files = get_files_to_read(table, index_one, index_two);

    for (int i = 0; i < files.size(); i++) {
        string path = storage_path + table + "-" + trim_string(files[i]) + ".fdb";
        push_data_to_list(path);
    }


    return data;
};


#endif