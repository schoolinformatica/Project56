#ifndef configreader
#define configreader

#include <iostream>
#include <fstream>
#include <map>
#include "../helperfunc/helperfunc.h"

using namespace std;

#define PATH_TO_CONFIG_FILE "/home/steve/csv_converter/credentials.pgconf"
#define HOST "hostip"
#define PORT "port"
#define DATABASE "database"
#define USER "user"
#define PASSWORD "password"


/*
 * Reads the postgreSQL config file. This file
 * contains the connection credentials to the
 * database.
 */
map<string, string> read_config_file() {

    string column;
    map<string, string> credentials;
    if(PATH_TO_CONFIG_FILE != "")
    {}

    ifstream config_file (PATH_TO_CONFIG_FILE);

    while(getline(config_file, column, ':')) {
        if(equals(column, HOST)) {
            getline(config_file, column, '\n');
            credentials.insert(pair<string, string>(HOST,trim(column)));
        }
        else if(equals(column, PORT)) {
            getline(config_file, column, '\n');
            credentials.insert(pair<string, string>(PORT,trim(column)));
        }
        else if(equals(column, DATABASE)) {
            getline(config_file, column, '\n');
            credentials.insert(pair<string, string>(DATABASE,trim(column)));
        }
        else if(equals(column, USER)) {
            getline(config_file, column, '\n');
            credentials.insert(pair<string, string>(USER,trim(column)));
        }
        else if(equals(column, PASSWORD)) {
            getline(config_file, column, '\n');
            credentials.insert(pair<string, string>(PASSWORD,trim(column)));
        }
    }
    config_file.close();
    return credentials;

}

#endif
