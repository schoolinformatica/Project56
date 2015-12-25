//
// Created by ceesjan on 15-12-2015.
//

#ifndef PROCESSING_DBENTITYMANAGER_H
#define PROCESSING_DBENTITYMANAGER_H


#include "../pqcon/pgsqlcon.h"
#include <pqxx/pqxx>
#include "../helperfunc/helperfunc.h"

using namespace pqxx;
using namespace std;

class EntityManager {
public:
    result port();
    result select(string table,  string where);
};

result EntityManager::port() {
    ostringstream os;
    os << "SELECT * FROM events WHERE 'Port' = 'Ignition'";

    string query = os.str();
    cout << query << endl;
    Pgsqlcon pgsqlcon;
    return pgsqlcon.exec_none_transaction(query);
}

result EntityManager::select(string table, string where) {
    ostringstream os;

    if(equals(where, "nothing")){
        os << "SELECT * FROM " << table ;
    }
    else {
        os << "SELECT * FROM " << table << " WHERE " << where;
    }

    string query = os.str();
    cout << query << endl;
    Pgsqlcon pgsqlcon;
    return pgsqlcon.exec_none_transaction(query);
}



#endif //PROCESSING_DBENTITYMMANAGER_H
