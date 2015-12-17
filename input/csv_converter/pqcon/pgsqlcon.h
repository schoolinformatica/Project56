//
// Created by steve on 5-12-2015.
//

#ifndef DBCON_PGSQLCON_H
#define DBCON_PGSQLCON_H

#include "configreader.h"
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

// Get the credentials to connect to the PostgreSQL database
static map<string, string> credentials = read_config_file();
static string connection_string = "dbname=" + credentials[DATABASE] + " user=" + credentials[USER] +
                                  " password=" + credentials[PASSWORD] + " hostaddr=" + credentials[HOST] +
                                  " port=" + credentials[PORT];

/*
 * Class Pgsqlcon
 *
 * This class is made for connection to the
 * PostgreSQL database.
 */

class Pgsqlcon
{
    int errorCode;
public:
    result exec_transaction(vector<string>&); // Ececute query in transaction mode
    result exec_none_transaction(const string&); // Execute query in non-transaction mode
    int getErrorCode(){return errorCode; }; //0 meaning failure, 1 meaning sucess

};

/*
 * @query -> Single SQL query
 *
 * Executes the given query on the database and
 * retreives the result (if any)
 *
 */


result Pgsqlcon::exec_none_transaction(const string & query) {
    //0 means the string being compared are equal
    if(query.compare("") != 0)
    {
        try {
            connection C(connection_string); // Connect to database
            nontransaction N(C); // Nontransaction to database
            result result = N.exec(query); // Execute the query
            C.disconnect(); // Disconnect from the database
            errorCode = 1;
            cout << "Query complete." << endl;
            return result; // Return result from the query

        }
        catch (const std::exception &e) {
            errorCode = 0;
            cerr << e.what() << endl;
        }
    }
    else
    {
        cout << "Error: Query string was empty.";
        errorCode = 0;
    }
}

/*
 * @queries -> Vector containing all the queries
 *
 * Executes all the queries in vector "queries"
 *
 */
result Pgsqlcon::exec_transaction(vector<string> & queries) {
    if(queries.size() > 0)
    {
        try {
            connection C(connection_string); // Connection to database
            work W(C); // Transaction to database

            //Add all queries to the transaction
            for (string &query : queries)
            {
                //0 means the string being compared are equal
                if(query.compare("") != 0)
                {
                    errorCode = 1;
                    W.exec(query);
                }
                else
                {
                    cout << "Error: Queries vector contained empty strings.";
                    errorCode = 0;
                }
            }
            W.commit(); // Commit the transaction
            C.disconnect(); // Disconnect from database
        }
        catch (const std::exception &e) {
            errorCode = 0;
            cerr << e.what() << endl;
        }
    }
    else
    {
        cout << "Error: Queries vector was empty.";
        errorCode = 0;
    }
}



#endif //DBCON_PGSQLCON_H