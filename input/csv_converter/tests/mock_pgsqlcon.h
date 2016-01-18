//
// Created by steve on 11-1-2016.
//

#ifndef DBCON_MOCK_PGSQLCON_H
#define DBCON_MOCK_PGSQLCON_H

#include <pqxx/pqxx>

class mock_pgsqlcon {
    int errorCode;
public:
    result exec_none_transaction(const string&); // Execute query in non-transaction mode
    int getErrorCode(){return errorCode; }; //0 meaning failure, 1 meaning sucess
};


result mock_pgsqlcon::exec_none_transaction(const ::mock_pgsqlcon::string &) {
    result r;
    return r;

}


#endif //DBCON_MOCK_PGSQLCON_H
