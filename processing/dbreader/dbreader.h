#ifndef dbreader
#define dbreader

#include "../pqcon/pgsqlcon.h"
#include "../helperfunc/helperfunc.h"
#include "../dbentities/PositionEntity.h"
#include "../dbentities/EventEntity.h"
#include "../dbentities/ConnectionEntity.h"
#include "../dbentities/MonitoringEntity.h"
#include "../dbentities/DBEntityManager.h"
#include "pqxx/pqxx"
#include "../pdfcreator/pdf.h"
#include "../pdfcreator/pdfcreator.h"

using namespace std;
using namespace pqxx;

vector<MonitoringEntity> convert_to_monitor(string where) {
    cout << "monitor" << endl;
    EntityManager manager;
    result result = manager.select("monitoring", where);
    vector<MonitoringEntity> monitoringEntities;
    for (result::const_iterator c = result.begin(); c != result.end(); ++c) {
        MonitoringEntity monitoringEntity;
        monitoringEntity.set_unit_id(c[0].as<string>());
        monitoringEntity.set_begin_time(c[1].as<string>());
        monitoringEntity.set_end_time(c[2].as<string>());
        monitoringEntity.set_type(c[3].as<string>());
        monitoringEntity.set_min(c[4].as<float>());
        monitoringEntity.set_max(c[5].as<float>());
        monitoringEntity.set_sum(c[6].as<float>());
        monitoringEntities.push_back(monitoringEntity);
    }
    return monitoringEntities;
}

/*********************
 * EVENTS
 *********************/

vector<EventEntity> convert_to_events(string where) {
    cout << "events" << endl;
    EntityManager manager;
    result result = manager.select("events", where);
    vector<EventEntity> eventEntities;
    for (result::const_iterator c = result.begin(); c != result.end(); ++c) {
        EventEntity eventEntity;
        eventEntity.set_date_time(c[0].as<string>());
        eventEntity.set_unit_id(c[1].as<string>());
        eventEntity.set_port(c[2].as<string>());
        eventEntity.set_value(c[3].as<bool>());

        eventEntities.push_back(eventEntity);
    }
    return eventEntities;
}

vector<EventEntity> convert_to_events(result result1) {
    cout << "events" << endl;
    vector<EventEntity> eventEntities;
    for (result::const_iterator c = result1.begin(); c != result1.end(); ++c) {
        EventEntity eventEntity;
        eventEntity.set_date_time(c[0].as<string>());
        eventEntity.set_unit_id(c[1].as<string>());
        eventEntity.set_port(c[2].as<string>());
        eventEntity.set_value(c[3].as<bool>());

        eventEntities.push_back(eventEntity);
    }
    return eventEntities;
}

vector<EventEntity> convert_to_eventsLite(result result1) {
    cout << "eventsLite" << endl;
    vector<EventEntity> eventEntities;

    //The query that uses this metod only returns two columns: Distinct UnitIDs and Counts of
    for (result::const_iterator e = result1.begin(); e != result1.end(); ++e) {
        EventEntity EventEntity;
        EventEntity.set_unit_id(e[0].as<string>());
        EventEntity.set_countOfValue(e[1].as<int>());
        eventEntities.push_back(EventEntity);
    }
    return eventEntities;
}

/*********************
 * CONNECTIONS
 *********************/

vector<ConnectionEntity> convert_to_connectionsLite(result result1) {
    cout << "connectionsLite" << endl;
    vector<ConnectionEntity> connectionEntities;

    //The query that uses this metod only returns two columns: Distinct UnitIDs and Counts of
    for (result::const_iterator c = result1.begin(); c != result1.end(); ++c) {
        ConnectionEntity connectionEntity;
        connectionEntity.set_unit_id(c[0].as<string>());
        connectionEntity.set_countOfValue(c[1].as<int>());
        connectionEntities.push_back(connectionEntity);
    }
    return connectionEntities;
}


vector<ConnectionEntity> convert_to_connections(result result1) {
    cout << "connections" << endl;
    vector<ConnectionEntity> connectionEntities;

    for (result::const_iterator c = result1.begin(); c != result1.end(); ++c) {
        ConnectionEntity connectionEntity;
        connectionEntity.set_date_time(c[0].as<string>());
        connectionEntity.set_unit_id(c[1].as<string>());
        connectionEntity.set_port(c[2].as<string>());
        connectionEntity.set_value(c[3].as<bool>());
        connectionEntities.push_back(connectionEntity);
    }
    return connectionEntities;
}

vector<ConnectionEntity> convert_to_connections(string where) {
    cout << "connections" << endl;
    EntityManager manager;
    result result = manager.select("connections", where);
    vector<ConnectionEntity> connectionEntities;

    for (result::const_iterator c = result.begin(); c != result.end(); ++c) {
        ConnectionEntity connectionEntity;
        connectionEntity.set_date_time(c[0].as<string>());
        connectionEntity.set_unit_id(c[1].as<string>());
        connectionEntity.set_port(c[2].as<string>());
        connectionEntity.set_value(c[3].as<bool>());
        connectionEntities.push_back(connectionEntity);
    }
    return connectionEntities;
}

/*********************
 * POSITIONS
 *********************/

vector<PositionEntity> convert_to_positions(string where) {
    cout << "positions" << endl;
    EntityManager manager;
    result result = manager.select("positions", where);
    vector<PositionEntity> positionsEntities;

    for (result::const_iterator c = result.begin(); c != result.end(); ++c) {
        PositionEntity positionEntity;
        positionEntity.set_date_time(c[0].as<string>());
        positionEntity.set_unit_id(c[1].as<string>());
        positionEntity.set_rdx(c[2].as<double>());
        positionEntity.set_rdy(c[3].as<double>());
        positionEntity.set_speed(c[4].as<int>());
        positionEntity.set_course(c[5].as<int>());
        positionEntity.set_num_satelites(c[6].as<int>());
        positionEntity.set_hdop(c[7].as<int>());
        positionEntity.set_quality(c[8].as<string>());
        positionsEntities.push_back(positionEntity);
    }
    return positionsEntities;
}

vector<PositionEntity> convert_to_positions(result result1) {
    cout << "positions" << endl;
    vector<PositionEntity> positionsEntities;

    for (result::const_iterator c = result1.begin(); c != result1.end(); ++c) {
        PositionEntity positionEntity;
        positionEntity.set_date_time(c[0].as<string>());
        positionEntity.set_unit_id(c[1].as<string>());
        positionEntity.set_rdx(c[2].as<double>());
        positionEntity.set_rdy(c[3].as<double>());
        positionEntity.set_speed(c[4].as<int>());
        positionEntity.set_course(c[5].as<int>());
        positionEntity.set_num_satelites(c[6].as<int>());
        positionEntity.set_hdop(c[7].as<int>());
        positionEntity.set_quality(c[8].as<string>());
        positionsEntities.push_back(positionEntity);
    }
    return positionsEntities;
}

//This method is used for calculating the amount of 0-speeds at each coordinate
vector<PositionEntity> convert_to_positionsStops(result result1) {
    cout << "positions stops" << endl;
    vector<PositionEntity> positionsEntities;
    for (result::const_iterator c = result1.begin(); c != result1.end(); ++c) {
        PositionEntity positionEntity;
        positionEntity.set_unit_id(c[0].as<string>());
        positionEntity.set_rdx(c[1].as<double>());
        positionEntity.set_rdy(c[2].as<double>());
        positionEntity.set_speed(c[3].as<int>());
        positionsEntities.push_back(positionEntity);
    }
    return positionsEntities;
}

//This method is used for calculating the amount of HDOP per UnitId
vector<PositionEntity> convert_to_positionsHDOP(result result1) {
    cout << "positions HDOP" << endl;
    vector<PositionEntity> positionsEntities;
    for (result::const_iterator c = result1.begin(); c != result1.end(); ++c) {
        PositionEntity positionEntity;
        positionEntity.set_unit_id(c[0].as<string>());
        positionEntity.set_hdop(c[1].as<int>());
        positionEntity.set_countOfUnitID(c[2].as<int>());
        positionsEntities.push_back(positionEntity);
    }
    return positionsEntities;
}

//This method is used for calculating the amount of HDOP per UnitId
vector<PositionEntity> convert_to_positionsSats(result result1) {
    cout << "positions Satellites" << endl;
    vector<PositionEntity> positionsEntities;
    for (result::const_iterator c = result1.begin(); c != result1.end(); ++c) {
        PositionEntity positionEntity;
        positionEntity.set_unit_id(c[0].as<string>());
        positionEntity.set_num_satelites(c[1].as<int>());
        positionEntity.set_countOfUnitID(c[2].as<int>());
        positionsEntities.push_back(positionEntity);
    }
    return positionsEntities;
}

//This method is used for calculating the amount of HDOP per UnitId
vector<PositionEntity> convert_to_positionsQuality(result result1) {
    cout << "positions Quality" << endl;
    vector<PositionEntity> positionsEntities;
    for (result::const_iterator c = result1.begin(); c != result1.end(); ++c) {
        PositionEntity positionEntity;
        positionEntity.set_unit_id(c[0].as<string>());
        positionEntity.set_qualityCount(c[1].as<int>());
        positionEntity.set_countOfUnitID(c[2].as<int>());
        positionsEntities.push_back(positionEntity);
    }
    return positionsEntities;
}
#endif
