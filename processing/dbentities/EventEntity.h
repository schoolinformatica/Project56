//
// Created by steve on 6-12-2015.
//

#ifndef INPUT_PROCESS_EVENTENTITY_H
#define INPUT_PROCESS_EVENTENTITY_H

#include "../pqcon/pgsqlcon.h"
#include <sstream>
#include <string>
#include <iostream>


class EventEntity{
private:
    string date_time;
    string unit_id;
    string port;
    int value;
    int countOfValue;

public:
    // Database management functions
    void insert_in_database();

    //Setters
    void set_date_time(string);

    void set_unit_id(string);

    void set_port(string);

    void set_value(int);

    void set_countOfValue(int);

    //Getters
    string get_date_time();

    string get_unit_id();

    string get_port();

    int get_value();

    int get_countOfValue();

};

// Database management functions
void EventEntity::insert_in_database() {
    ostringstream insert_query;

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

void EventEntity::set_countOfValue(int countValue) { countOfValue = countValue; }

// Getters
const string EventEntity::get_date_time() { return date_time; }

const string EventEntity::get_unit_id() { return unit_id; }

const string EventEntity::get_port() { return port; }

const int EventEntity::get_value() { return value; }

const int EventEntity::get_countOfValue() { return countOfValue; }




#endif //INPUT_PROCESS_EVENTENTITY_H
