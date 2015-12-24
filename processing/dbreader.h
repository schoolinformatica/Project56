#ifndef dbreader
#define dbreader

#include "pqcon/pgsqlcon.h"
#include "helperfunc/helperfunc.h"
#include "dbentities/PositionEntity.h"
#include "dbentities/EventEntity.h"
#include "dbentities/ConnectionEntity.h"
#include "dbentities/MonitoringEntity.h"
#include "dbentities/DBEntityManager.h"
#include "pqxx/pqxx"
#include "pdf.h"
#include "pdfcreator.h"

using namespace std;
using namespace pqxx;

vector<MonitoringEntity> convert_to_monitor(string where) {
    cout << "monitor" << endl;
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
    for (result1::const_iterator c = result1.begin(); c != result1.end(); ++c) {
        EventEntity eventEntity;
        eventEntity.set_date_time(c[0].as<string>());
        eventEntity.set_unit_id(c[1].as<string>());
        eventEntity.set_port(c[2].as<string>());
        eventEntity.set_value(c[3].as<bool>());

        eventEntities.push_back(eventEntity);
    }
    return eventEntities;
}

void x(PDF &pdf) {
    EntityManager em;
    vector<EventEntity> eventsEntities = convert_to_events(em.port());
    vector<int> ports;
    vector<string> datums;

    for (EventEntity e : eventsEntities) {
        ports.push_back(atoi(e.get_port().c_str()));
        datums.push_back(e.get_date_time());
    }


    int scale = 10;

    string errMsg;
    pdf.setFont(PDF::Font(2), 10);

    for (int z = 0; z < ports.size(); z++) {
        //first x of first dot, first y of first dot, then same for second dot.
        pdf.setLineWidth(1);
        //0-values are not taken, only in the values to the side of the graph below.
        //pdf.drawLine(ports[z] + 100, z + 100, ports[z + 1] + 100, z + 1 + 100);
        pdf.drawLine(z+100, ports[z] + 100, z + 1 + 100, ports[z + 1] + 100 );
    }

    // We draw every hundred number on the x axis
    for (int xas = 0; xas < datums.size(); xas++) {
        // The +95 makes sure the line isnt drawn directly in the corner of the pdf.
        pdf.showTextXY(datums[xas * scale], datums[xas] + 95, 95);
    }


    for (int yas = 0; yas < ports.size(); yas++) {
        // The +95 makes sure the line isnt drawn directly in the corner of the pdf.
        pdf.showTextXY(std::to_string(ports[yas] * scaler), 95, ports[yas] + 95);

    }

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

vector<PositionEntity> convert_to_positions(string where) {
    cout << "positions" << endl;
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
