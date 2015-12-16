//
// Created by ceesjan on 15-12-2015.
//

#ifndef PROCESSING_ENTITYMANAGER_H
#define PROCESSING_ENTITYMANAGER_H


#include "../pqcon/pgsqlcon.h"
#include <pqxx/pqxx>
#include "../helperfunc/helperfunc.h"

using namespace pqxx;
using namespace std;

class EntityManager {
public:
    result select(string table, string what, string where);
};

result EntityManager::select(string table, string where) {
    ostringstream os;

    if(equals(where, "nothing"){
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



#endif //PROCESSING_ENTITYMMANAGER_H
