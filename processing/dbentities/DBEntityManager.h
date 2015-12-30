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
    result getConnectionFailuresPerCar();
    result getIgnitionFailuresPerCar();
    result getStopsPerCoordinate();
    result select(string table,  string where);
};

/**************************
 * SPECIAL DIRECT QUERIES
 **************************
 */

result EntityManager::port() {
    ostringstream os;
    //Remember to wrap the column you are referencing in double escaped quotes!
    os << "SELECT * FROM events WHERE \"Port\" = 'Ignition'";

    string query = os.str();
    cout << query << endl;
    Pgsqlcon pgsqlcon;
    return pgsqlcon.exec_none_transaction(query);
}

result EntityManager::getConnectionFailuresPerCar()
{
    ostringstream os;
    //Remember to wrap the column you are referencing in double escaped quotes!
    os << "SELECT DISTINCT \"UnitId\", COUNT(\"Value\")"
    << " FROM connections"
    << " WHERE \"Value\" = 0"
    << " GROUP BY \"UnitId\""
    << " ORDER BY COUNT(\"Value\") ASC"
    << ";";

    string query = os.str();
    cout << query << endl;
    Pgsqlcon pgsqlcon;
    return pgsqlcon.exec_none_transaction(query);
}

result EntityManager::getIgnitionFailuresPerCar()
{
    ostringstream os;
    //Remember to wrap the column you are referencing in double escaped quotes!
    os << "SELECT DISTINCT \"UnitId\", COUNT(\"Value\")"
    << " FROM events"
    << " WHERE \"Value\" = 0"
    << " GROUP BY \"UnitId\""
    << " ORDER BY COUNT(\"Value\") ASC"
    << ";";

    string query = os.str();
    cout << query << endl;
    Pgsqlcon pgsqlcon;
    return pgsqlcon.exec_none_transaction(query);
}

result EntityManager::getStopsPerCoordinate()
{
    ostringstream os;
    //Remember to wrap the column you are referencing in double escaped quotes!
    os << "SELECT DISTINCT \"UnitId\", \"Rdx\", \"Rdy\", COUNT(\"Speed\")"
    << " FROM positions"
    << " WHERE \"Speed\" = 0"
    << " GROUP BY \"UnitId\", \"Rdx\", \"Rdy\""
    << " ORDER BY COUNT(\"Speed\") DESC"
    << " LIMIT 100"
    << ";";

    string query = os.str();
    cout << query << endl;
    Pgsqlcon pgsqlcon;
    return pgsqlcon.exec_none_transaction(query);
}

/**************************
 * STANDARD QUERIES
 **************************
 */

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
