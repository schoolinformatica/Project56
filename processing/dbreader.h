#ifndef dbreader
#define dbreader

#include "pqcon/pgsqlcon.h"
#include "helperfunc/helperfunc.h"

using namespace std;

vector <object> read_from_database(string table, string what, string where) {

    if (equals(table, "positions")) {
        cout << table << endl;
    } else if (equals(table, "monitioring")) {
        cout << table << endl;
    } else if (equals(table, "connections")) {
        cout << table << endl;
    } else if (equals(table, "monitoring")) {
        cout << table << endl;
    }
    else {
        cout << "not a valid CityGis CSV Table" << endl;
    }
    Pgsqlcon pgsqlcon;

    return pgsqlcon.exec_none_transaction(query);
}

#endif