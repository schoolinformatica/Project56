//
// Created by robert on 12/10/15.
//

// main.cpp -- take 2
#include "UnitTest++/UnitTest++.h"
#include "pqcon/pgsqlcon.h"
#include "csvreader/csvreader.h"

TEST(testCsvReaderNullParams)
{
    cout << "Testing csvreader() with both params empty..." << endl;

    string csvFileParam = "";
    string tableParam = "";
    int expectedResult = 0;

    int actualResult = csvreader(csvFileParam, tableParam);

    CHECK_EQUAL(expectedResult, actualResult);
}

TEST(testCsvReaderFirstParamGood)
{
    cout << "Testing csvreader() with table param empty..." << endl;

    string csvFileParam = "/home/robert/Hogeschool/Project56/Project56/input/csv_converter/positions.csv";
    string tableParam = "";
    int expectedResult = 0;

    int actualResult = csvreader(csvFileParam, tableParam);

    CHECK_EQUAL(expectedResult, actualResult);
}

TEST(testCsvReaderSecondParamGood)
{
    cout << "Testing csvreader() with csvfile param empty..." << endl;

    string csvFileParam = "";
    string tableParam = "positions";
    int expectedResult = 0;

    int actualResult = csvreader(csvFileParam, tableParam);

    CHECK_EQUAL(expectedResult, actualResult);
}

TEST(testCsvReaderBothParamsGood)
{
    cout << "Testing csvreader() with both params good..." << endl;

    string csvFileParam = "/home/robert/Desktop/Hogeschool/Project56/Project56/input/csv_converter/positions.csv";
    string tableParam = "positions";
    int expectedResult = 1;

    int actualResult = csvreader(csvFileParam, tableParam);

    CHECK_EQUAL(expectedResult, actualResult);
}
//exec none trans en normale trans, good n bad param

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



