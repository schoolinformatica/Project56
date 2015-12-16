#include <iostream>
//#include "listener.h"
//#include "dbpusher/dbpusher.h"
#include "pqcon/pgsqlcon.h"

using namespace std;

int main() {
    Pgsqlcon p;
    p.exec_none_transaction("SELECT * FROM connections");
//    push_list_to_database("connections.csv");
    //listener("/home/cooperatio/");
    return 0;
}