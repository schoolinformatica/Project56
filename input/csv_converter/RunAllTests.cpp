//
// Created by robert on 12/10/15.
//

// main.cpp -- take 2
#include "UnitTest++/UnitTest++.h"
#include "pqcon/pgsqlcon.h"

TEST(testExecNoneTransBadParam)
{
    cout << "Testing pgsqlcon::exec_none_trans with empty param..." << endl;

    string param = "";
    int expectedResult = 0;
    Pgsqlcon* instance = new Pgsqlcon();

    instance->exec_none_transaction(param);
    int actualResult = instance->getErrorCode();

    CHECK_EQUAL(expectedResult, actualResult);
}

TEST(testExecTransBadParam)
{
    cout << "Testing pgsqlcon::exec_trans with empty param..." << endl;

    vector<string> param;
    param.push_back("");
    int expectedResult = 0;
    Pgsqlcon* instance = new Pgsqlcon();

    instance->exec_transaction(param);
    int actualResult = instance->getErrorCode();

    CHECK_EQUAL(expectedResult, actualResult);
}
int main(int, const char *[])
{
    return UnitTest::RunAllTests();
}



