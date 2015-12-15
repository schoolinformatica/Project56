//
// Created by steve on 6-12-2015.
//

#ifndef INPUT_PROCESS_CONNECTIONENTITY_H
#define INPUT_PROCESS_CONNECTIONENTITY_H

#include "../pqcon/pgsqlcon.h"
#include "dbEntity.h"
#include <sstream>
#include <string>
#include <iostream>

class ConnectionEntity : public dbEntity {
private:
    string date_time; // Time stamp
    string unit_id; // ID of the vehicle
    string port; // Port type
    bool value; // Value of port type

public:

    // Database management functions
    void insert_in_database();

    // Setters
    void set_date_time(string);

    void set_unit_id(string);

    void set_port(string);

    void set_value(bool);

    // Getters
    string get_date_time();

    string get_unit_id();

    string get_port();

    bool get_value();
};

// Database management functions
void ConnectionEntity::insert_in_database() {
    ostringstream insert_query;

    insert_query << "INSERT INTO connection ";
    insert_query << "VALUES ('";
    insert_query << date_time << "','";
    insert_query << unit_id << "','";
    insert_query << port << "',";
    insert_query << value;
    insert_query << ");";

    Pgsqlcon p;
    p.exec_none_transaction(insert_query.str());
}

// Setters
void ConnectionEntity::set_date_time(string Date_time) { date_time = Date_time; }

void ConnectionEntity::set_unit_id(string Unit_id) { unit_id = Unit_id; }

void ConnectionEntity::set_port(string Port) { port = Port; }

void ConnectionEntity::set_value(bool Value) { value = Value; }

// Getters
string ConnectionEntity::get_date_time() { return date_time; }

string ConnectionEntity::get_unit_id() { return unit_id; }

string ConnectionEntity::get_port() { return port; }

bool ConnectionEntity::get_value() { return value; }

#endif //INPUT_PROCESS_CONNECTIONENTITY_H
