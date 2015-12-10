//
// Created by robert on 12/7/15.
//

#include "pgsqlcon.h"
#include "CuTest.h"
#include "CuTest.c"


//And test with wrong credentials

void TestPsqlNoneTransactionForNullParams(CuTest *tc)
{
    Pgsqlcon * instance = new Pgsqlcon();
    const string & param = "";
    int expectedResult = 0;
    instance->exec_none_transaction(param);

    int actualResult = instance->getErrorCode();
    CuAssertIntEquals(tc, expectedResult, actualResult);
}

void TestPsqlTransactionForNullParams(CuTest *tc)
{
    Pgsqlcon * instance = new Pgsqlcon();
    vector<string> param;
    int expectedResult = 0;
    instance->exec_transaction(param);

    int actualResult = instance->getErrorCode();
    CuAssertIntEquals(tc, expectedResult, actualResult);
}


CuSuite* StrUtilGetSuite()
{
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestPsqlNoneTransactionForNullParams);
    SUITE_ADD_TEST(suite, TestPsqlTransactionForNullParams);

    return suite;
}