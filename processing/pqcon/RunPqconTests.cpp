/*
 * Created by Robert.
 * This file runs all the tests that were added to the Suite using SUITE_ADD_TEST.
 *
 */
#include <stdio.h>
#include "CuTest.h"

CuSuite* StrUtilGetSuite();

void RunAllTests(void) {
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();

    CuSuiteAddSuite(suite, StrUtilGetSuite());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);

    printf("%s\n", output->buffer);
}

int main(void) {
    RunAllTests();
}