//
// Created by ceesjan on 15-12-2015.
//

#ifndef PROCESSING_ENTITYMANAGER_H
#define PROCESSING_ENTITYMANAGER_H


#include "../pqcon/pgsqlcon.h"
#include <pqxx/pqxx>

using namespace pqxx;
using namespace std;

class EntityManager {
public:
    result select(string table, string what, string where);
};

result EntityManager::select(string table, string what, string where) {
    ostringstream os;
    os << "SELECT " << what << " FROM " << table << " WHERE " << where;
    string query = os.str();
    cout << query << endl;
    Pgsqlcon pgsqlcon;
    return pgsqlcon.exec_none_transaction(query);
}



#endif //PROCESSING_ENTITYMMANAGER_H
