//
// Created by steve on 11-1-2016.
//

#ifndef DBCON_MOCK_PGSQLCON_H
#define DBCON_MOCK_PGSQLCON_H

#include "pqxx/pqxx"
#include <unistd.h>


using namespace pqxx;
using namespace std;

class mock_pgsqlcon {
    int errorCode;
public:
    result mock_exec_none_transaction(const string&); // Execute query in non-transaction mode
    int getErrorCode(){return errorCode; }; //0 meaning failure, 1 meaning sucess
};

result mock_pgsqlcon::mock_exec_none_transaction(const string & query) {

    result result;
    return  result;
}


#endif //DBCON_MOCK_PGSQLCON_H
