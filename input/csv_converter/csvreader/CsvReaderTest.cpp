/*
* Created by robert on 12/5/15.
*
* These test files test the CSVReader, and the CSVReader only.
*
*/

#include <iostream>
#include "CuTest.c"
#include "CuTest.h"
#include "csvreader.h"

void TestCsvReaderForNullParams(CuTest *tc) 
{
    string param = "";
    int actual = csvreader(param, param);
    int expected = 0;

    CuAssertIntEquals(tc, expected, actual);
}

void TestCsvReaderForGoodParams(CuTest *tc)
{
    string goodParam1 = "/home/robert/Desktop/Hogeschool/Project56/Project56/input/csv_converter/connections.csv";
    string goodParam2 = "/home/robert/Desktop/Hogeschool/Project56/Project56/input/csv_converter/tables.ss";
    int actual = csvreader(goodParam1, goodParam2);
    int expected = 1;

    CuAssertIntEquals(tc, expected, actual);
}

CuSuite* StrUtilGetSuite() 
{
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestCsvReaderForNullParams);
    SUITE_ADD_TEST(suite, TestCsvReaderForGoodParams);
    return suite;
}
