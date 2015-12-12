#ifndef dbpusher
#define dbpusher

#include "../pqcon/pgsqlcon.h"
#include "../helperfunc/helperfunc.h"
#include <algorithm>
#include <string.h>
#include <thread>

using namespace std;

void push_list_to_database(vector<string> &rows, string &table) {
    vector<string> queries;
    Pgsqlcon p;

    if (equals(table, "positions")) {
        stringstream query;
        for (int i = 9; i < rows.size(); i += 9) {
            query.str(string());

            query << "INSERT INTO positions VALUES ('";
            query << rows[i] << "','";
            query << rows[i + 1] << "',";
            query << atoi(rows[i + 2].c_str()) << ",";
            query << atoi(rows[i + 3].c_str()) << ",";
            query << atoi(rows[i + 4].c_str()) << ",";
            query << atoi(rows[i + 5].c_str()) << ",";
            query << atoi(rows[i + 6].c_str()) << ",";
            query << atoi(rows[i + 7].c_str()) << ",'";
            query << rows[i + 8] << "');";


            queries.push_back(query.str());


        }
    }
    p.exec_transaction(queries);
}


#endif
