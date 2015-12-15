//
// Created by steve on 6-12-2015.
//

#ifndef INPUT_PROCESS_MONITORINGENTITY_H
#define INPUT_PROCESS_MONITORINGENTITY_H

#include "dbEntity.h"
#include "../pqcon/pgsqlcon.h"

class MonitoringEntity : dbEntity {
private:
    string unit_id;
    string begin_time;
    string end_time;
    string type;
    float min;
    float max;
    float sum;

public:

    //Database management function
    void insert_in_databse();


    // Setters
    void set_unit_id(string);

    void set_begin_time(string);

    void set_end_time(string);

    void set_type(string);

    void set_min(float);

    void set_max(float);

    void set_sum(float);

    // Getters
    string get_unit_id();

    string get_begin_time();

    string get_end_time();

    string get_type();

    float get_min();

    float get_max();

    float get_sum();

};

void MonitoringEntity::insert_in_databse() {
    string insert_query;

    insert_query << "INSERT INTO monitoring ";
    insert_query << "VALUES ('";

    insert_query << unit_id << "', '";
    insert_query << begin_time << "', '";
    insert_query << end_time << "', '";
    insert_query << type << "', '";
    insert_query << min << "', '";
    insert_query << max << "', '";
    insert_query << sum << "');";

    Pgsqlcon p;
    p.exec_none_transaction(insert_query.str());

}
// Setters
void MonitoringEntity::set_unit_id(string Unit_id){ unit_id = Unit_id;};

void MonitoringEntity::set_begin_time(string Begin_time){ begin_time = Begin_time;};

void MonitoringEntity::set_end_time(string End_time) { end_time = End_time; };

void MonitoringEntity::set_type(string Type){ type = Type;};

void MonitoringEntity::set_min(float Min){min = Min;};

void MonitoringEntity::set_max(float Max){max = Max;};

void MonitoringEntity::set_sum(float Sum){sum = Sum;};



// Getters
string MonitoringEntity::get_unit_id(){ return unit_id; } ;

string MonitoringEntity::get_begin_time(){ return begin_time; };

string MonitoringEntity::get_end_time(){ return end_time;};

string MonitoringEntity::get_type(){ return type;};

float MonitoringEntity::get_min(){ return min;};

float MonitoringEntity::get_max(){ return max;};

float MonitoringEntity::get_sum(){return sum;};


#endif //INPUT_PROCESS_MONITORINGENTITY_H
