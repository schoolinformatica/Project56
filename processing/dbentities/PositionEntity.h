//
// Created by steve on 6-12-2015.
//

#ifndef INPUT_PROCESS_POSITIONENTITY_H
#define INPUT_PROCESS_POSITIONENTITY_H

#include "../pqcon/pgsqlcon.h"
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

class PositionEntity{
private:
    string date_time;
    string unit_id;
    int rdx;
    int rdy;
    int speed;
    int course;
    int num_satelites;
    int hdop;
    int countOfUnitID;
    string quality;
    int qualityInt;

public:
    // Database management functions
    void insert_in_database();

    // Setters
    void set_date_time(string);

    void set_unit_id(string);

    void set_rdx(int);

    void set_rdy(int);

    void set_speed(int);

    void set_course(int);

    void set_num_satelites(int);

    void set_hdop(int);

    void set_quality(string);

    void set_countOfUnitID(int);

    void set_qualityCount(int);


    // Getters
    string get_date_time();

    string get_unit_id();

    int get_rdx();

    int get_rdy();

    int get_speed();

    int get_course();

    int get_num_satelites();

    int get_hdop();

    string get_quality();

    int get_countOfUnitID();

    int get_qualityCount();

};

// Database management functions
void PositionEntity::insert_in_database() {
    ostringstream insert_query;

    insert_query << "INSERT INTO positions ";
    insert_query << "VALUES ('";
    insert_query << date_time << "','";
    insert_query << unit_id << "','";
    insert_query << rdx << "','";
    insert_query << rdy << "',";
    insert_query << speed << ",";
    insert_query << course << ",";
    insert_query << num_satelites << ",";
    insert_query << hdop << ",'";
    insert_query << quality;
    insert_query << "');";

    Pgsqlcon p;
    p.exec_none_transaction(insert_query.str());
}

// Setters
void PositionEntity::set_date_time(string Date_time) { date_time = Date_time; }

void PositionEntity::set_unit_id(string Unit_id) { unit_id = Unit_id; }

void PositionEntity::set_rdx(int Rdx) { rdx = Rdx; }

void PositionEntity::set_rdy(int Rdy) { rdy = Rdy; }

void PositionEntity::set_speed(int Speed) { speed = Speed; }

void PositionEntity::set_course(int Course) { course = Course; }

void PositionEntity::set_num_satelites(int Num_satelites) { num_satelites = Num_satelites; }

void PositionEntity::set_hdop(int Hdop) { hdop = Hdop; }

void PositionEntity::set_quality(string Quality) { quality = Quality; }

void PositionEntity::set_countOfUnitID(int count) { countOfUnitID = count; }

void PositionEntity::set_qualityCount(int count) { qualityCount = count; }

// Getters
string PositionEntity::get_date_time() { return date_time; }

string PositionEntity::get_unit_id() { return unit_id; }

int PositionEntity::get_rdx() { return rdx; }

int PositionEntity::get_rdy() { return rdy; }

int PositionEntity::get_speed() { return speed; }

int PositionEntity::get_course() { return course; }

int PositionEntity::get_num_satelites() { return num_satelites; }

int PositionEntity::get_hdop() { return hdop; }

string PositionEntity::get_quality() { return quality; }

int PositionEntity::get_countOfUnitID() { return countOfUnitID; }

int PositionEntity::set_qualityCount() { return qualityCount; }

#endif //INPUT_PROCESS_POSITIONENTITY_H
