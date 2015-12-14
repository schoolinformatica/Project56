//
// Created by steve on 6-12-2015.
//

#ifndef INPUT_PROCESS_EVENTENTITY_H
#define INPUT_PROCESS_EVENTENTITY_H

#include "dbEntity.h"


class EventEntity : dbEntity {
private:
    string date_time;
    string unit_id;
    string port;
    int value;

public:
    // Database management functions
    void insert_into_database();

    //Setters
    void set_date_time(string);

    void set_unit_id(string);

    void set_port(string);

    void set_value(int);

    //Getters
    string get_date_time();

    string get_unit_id();

    string get_port();

    string get_value();
};

// Database management functions
void EventEntity::insert_in_database() {
    stringstream insert_query;

    insert_query << "INSERT INTO events ";
    insert_query << "VALUES ('";
    insert_query << date_time << "','";
    insert_query << unit_id << "','";
    insert_query << port << "','";
    insert_query << value;
    insert_query << "');";

    Pgsqlcon p;
    p.exec_none_transaction(insert_query.str());
}


//Setters
void EventEntity::set_date_time(string Date_time) { date_time = Date_time ;  }

void EventEntity::set_port(string Port) { port= Port; }

void EventEntity::set_unit_id(string Unit_id) { unit_id = Unit_id; }

void EventEntity::set_value(int Value) { value = Value; }

//Getters
string EventEntity::get_date_time() { return date_time; }

string EventEntity::get_port() { return port; }

string EventEntity::get_unit_id() { return unit_id; }

int EventEntity::get_value() { return value; }




#endif //INPUT_PROCESS_EVENTENTITY_H
