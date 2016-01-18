//
// Created by steve on 11-1-2016.
//

#include "UnitTest++/UnitTest++.h"
#include "../pqcon/pgsqlcon.h"

/*
 *  Tests for pgsqlcon.h file
 */
TEST(pgsqlcon_exec_non_trans_good) {

        //Expected result
        int expected_return_value = 1;
        const string query = "SELECT * FROM connections LIMIT 1";
        Pgsqlcon p;
        p.exec_none_transaction(query);

        int return_value = p.getErrorCode();

        CHECK_EQUAL(expected_return_value, return_value);
};

TEST(pgsqlcon_exec_non_trans_bad) {

        //Expected result
        int expected_return_value = 0;
        const string query = "SELECTT * FROOM connections LIMEIT 1";
        Pgsqlcon p;
        p.exec_none_transaction(query);

        int return_value = p.getErrorCode();

        CHECK_EQUAL(expected_return_value, return_value);
};

TEST(pgsqlcon_exec_trans_good) {

        //Expected result
        int expected_return_value = 1;
        const string query = "SELECT * FROM connections LIMIT 1";
        vector<string> queries;
        queries.push_back(query);
        Pgsqlcon p;
        p.exec_transaction(queries);

        int return_value = p.getErrorCode();

        CHECK_EQUAL(expected_return_value, return_value);
};

TEST(pgsqlcon_exec_trans_bad) {

        //Expected result
        int expected_return_value = 0;
        const string query = "SELECTT * FROOM connections LIOMIT 1";
        vector<string> queries;
        queries.push_back(query);
        Pgsqlcon p;
        p.exec_transaction(queries);

        int return_value = p.getErrorCode();

        CHECK_EQUAL(expected_return_value, return_value);
};


int main(int, const char *[]) {
    return UnitTest::RunAllTests();
}

