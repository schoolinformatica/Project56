#ifndef dbreader
#define dbreader

#include "pqcon/pgsqlcon.h"
#include "helperfunc/helperfunc.h"
#include "dbentities/dbEntity.h"
#include "dbentities/PositionEntity.h"
#include "dbentities/EventEntity.h"
#include "dbentities/ConnectionEntity.h"
#include "dbentities/MonitoringEntity.h"
#include "dbentities/DBEntityManager.h"
#include "pqxx/pqxx"

using namespace std;
using namespace pqxx;

vector<MonitoringEntity> convert_to_monitor() {
    cout << table << endl;
    EntityManager manager;
    result result = manager.select("monitor", where);
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

vector<EventEntity> convert_to_events() {
    cout << table << endl;
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

vector<ConnectionEntity> convert_to_connections() {
    cout << table << endl;
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

vector<PositionEntity> convert_to_positions() {
    cout << table << endl;
    EntityManager manager;
    result result = manager.select("positions", where);
    vector<PositionEntity> positionsEntities;
    for (result::const_iterator c = result.begin(); c != result.end(); ++c) {
        PositionEntity positionEntity;
        positionEntity.set_date_time(c[0].as<string>());
        positionEntity.set_unit_id(c[1].as<string>());
        positionEntity.set_rdx(c[2].as<int>());
        positionEntity.set_rdy(c[3].as<int>());
        positionEntity.set_speed(c[4].as<int>());
        positionEntity.set_course(c[5].as<int>());
        positionEntity.set_num_satelites(c[6].as<int>());
        positionEntity.set_hdop(c[7].as<int>());
        positionEntity.set_quality(c[8].as<string>());
        positionsEntities.push_back(positionEntity);
    }
    return positionsEntities;
}

#endif
