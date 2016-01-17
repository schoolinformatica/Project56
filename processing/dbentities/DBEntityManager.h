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
    result port(string startDate, string endDate);
    result getConnectionFailuresPerCar(string startDate, string endDate);
    result getIgnitionFailuresPerCar(string startDate, string endDate);
    result getStopsPerCoordinate(string startDate, string endDate);
    result getHDOPPerCar(string startDate, string endDate);
    result getNumSatellitesPerCar(string startDate, string endDate);
    result getQualityPerCar(string startDate, string endDate);
    result select(string table,  string where);
};

/**************************
 * SPECIAL DIRECT QUERIES
 **************************
 */

result EntityManager::port(string startDate, string endDate) {
    ostringstream os;
    //Remember to wrap the column you are referencing in double escaped quotes!
    os << "SELECT * FROM events WHERE \"Port\" = 'Ignition'"
    << " BETWEEN \'" + startDate + "\'  AND \'" + endDate + "\';";

    string query = os.str();
    cout << query << endl;
    Pgsqlcon pgsqlcon;
    return pgsqlcon.exec_none_transaction(query);
}

result EntityManager::getConnectionFailuresPerCar(string startDate, string endDate)
{
    ostringstream os;
    //Remember to wrap the column you are referencing in double escaped quotes!
    os << "SELECT DISTINCT \"UnitId\", COUNT(\"Value\")"
    << " FROM connections"
    << " BETWEEN \'" + startDate + "\'  AND \'" + endDate + "\'"
    << " WHERE \"Value\" = 0"
    << " GROUP BY \"UnitId\""
    << " ORDER BY COUNT(\"Value\") ASC"
    << ";";

    string query = os.str();
    cout << query << endl;
    Pgsqlcon pgsqlcon;
    return pgsqlcon.exec_none_transaction(query);
}

result EntityManager::getIgnitionFailuresPerCar(string startDate, string endDate)
{
    ostringstream os;
    //Remember to wrap the column you are referencing in double escaped quotes!
    os << "SELECT DISTINCT \"UnitId\", COUNT(\"Value\")"
    << " FROM events"
    << " BETWEEN \'" + startDate + "\'  AND \'" + endDate + "\'"
    << " WHERE \"Value\" = 0"
    << " GROUP BY \"UnitId\""
    << " ORDER BY COUNT(\"Value\") ASC"
    << ";";

    string query = os.str();
    cout << query << endl;
    Pgsqlcon pgsqlcon;
    return pgsqlcon.exec_none_transaction(query);
}

result EntityManager::getStopsPerCoordinate(string startDate, string endDate)
{
    ostringstream os;
    //Remember to wrap the column you are referencing in double escaped quotes!
    os << "SELECT DISTINCT \"UnitId\", \"Rdx\", \"Rdy\", COUNT(\"Speed\")"
    << " FROM positions"
    << " BETWEEN \'" + startDate + "\'  AND \'" + endDate + "\'"
    << " WHERE \"Speed\" = 0"
    << " GROUP BY \"UnitId\", \"Rdx\", \"Rdy\""
    << " ORDER BY COUNT(\"Speed\") DESC"
    << ";";

    string query = os.str();
    cout << query << endl;
    Pgsqlcon pgsqlcon;
    return pgsqlcon.exec_none_transaction(query);
}

result EntityManager::getHDOPPerCar(string startDate, string endDate)
{
    ostringstream os;
    //Remember to wrap the column you are referencing in double escaped quotes!
    os << "SELECT DISTINCT \"UnitId\", SUM(\"HDOP\"), COUNT(\"UnitId\")"
    << " FROM positions"
    << " BETWEEN \'" + startDate + "\'  AND \'" + endDate + "\'"
    << " GROUP BY \"UnitId\", \"HDOP\""
    << ";";
    string query = os.str();
    cout << query << endl;
    Pgsqlcon pgsqlcon;
    return pgsqlcon.exec_none_transaction(query);
}

result EntityManager::getNumSatellitesPerCar(string startDate, string endDate)
{
    ostringstream os;
    //Remember to wrap the column you are referencing in double escaped quotes!
    os << "SELECT DISTINCT \"UnitId\", SUM(\"NumSatellites\"), COUNT(\"UnitId\")"
    << " FROM positions"
    << " BETWEEN \'" + startDate + "\'  AND \'" + endDate + "\'"
    << " GROUP BY \"UnitId\", \"NumSatellites\""
    << ";";
    string query = os.str();
    cout << query << endl;
    Pgsqlcon pgsqlcon;
    return pgsqlcon.exec_none_transaction(query);
}


result EntityManager::getQualityPerCar(string startDate, string endDate)
{
    ostringstream os;
    //Remember to wrap the column you are referencing in double escaped quotes!
    os << "SELECT DISTINCT \"UnitId\", COUNT(\"Quality\")"
    << " FROM positions"
    << " BETWEEN \'" + startDate + "\'  AND \'" + endDate + "\'"
    << " WHERE \"Quality\" LIKE \'%DGPS%\'"
    << " GROUP BY \"UnitId\", \"Quality\""
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
