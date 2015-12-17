//
// Created by robert on 12/10/15.
//

#include "pqcon/configreader.h"
#include "pqcon/pgsqlcon.h"
#include "dbpusher/dbpusher.h"
#include "UnitTest++/UnitTest++.h"
#include "UnitTest++/XmlTestReporter.h"

TEST(testExecNoneTransBadParam)
{
    cout << "Testing pgsqlcon::exec_none_trans with empty param..." << endl;

    string param = "";
    int expectedResult = 0;
    Pgsqlcon p;

    p.exec_none_transaction(param);
    int actualResult = p.getErrorCode();

    CHECK_EQUAL(expectedResult, actualResult);
}

TEST(testExecTransBadParam)
{
    cout << "Testing pgsqlcon::exec_trans with empty param..." << endl;

    vector<string> param;
    param.push_back("");
    int expectedResult = 0;

    Pgsqlcon p;

    p.exec_transaction(param);
    int actualResult = p.getErrorCode();

    CHECK_EQUAL(expectedResult, actualResult);
}

TEST(testPushListToDatabaseBadParam)
{
    cout << "Testing dbpusher::PushListToDatabase with empty param..." << endl;

    string param = "";
    int expectedResult = 0;

    int actualResult = push_list_to_database(param);

    CHECK_EQUAL(expectedResult, actualResult);
}

int main(int, const char *[])
{
    std::ofstream f("testreport.xml");
    UnitTest::XmlTestReporter reporter(f);

    UnitTest::TestRunner runner(reporter);

    return runner.RunTestsIf(UnitTest::Test::GetTestList(), NULL, UnitTest::True(), 0);
}



