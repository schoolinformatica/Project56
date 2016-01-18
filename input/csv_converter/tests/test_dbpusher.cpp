//
// Created by steve on 11-1-2016.
//

#include "UnitTest++/UnitTest++.h"
#include "mock_dbpusher.h"
#include "UnitTest++/XmlTestReporter.h"


/*
 * Tests for DBPusher.h
 */

/*
 * #succes condition
 *
 * Tests dbpusher->createQuery method
 *
 */
TEST(dbpusher_createQuery_good){

        string parameter_one = "/path/to/file.csv";
        string parameter_two = "connections.csv";
        string expected_return_value = "DELETE FROM connections; COPY connections FROM '/path/to/file.csv' DELIMITER ';' CSV HEADER";

        string return_value = createQuery(parameter_one, parameter_two);

        CHECK_EQUAL(expected_return_value, return_value);
}

/*
 * #fail condition
 *
 * Tests dbpusher->createQuery method
 *
 */
TEST(dbpusher_createQuery_bad){

        string parameter_one = "/path/to/file";
        string parameter_two = "connections.csv";
        string expected_return_value = "DELETE FROM connections; COPY connections FROM '/path/to/file' DELIMITER ';' CSV HEADER";

        string return_value = createQuery(parameter_one, parameter_two);

        CHECK_EQUAL(expected_return_value, return_value);
}

/*
 * #succes condition
 *
 * Tests dbpusher->extractCsvFileName method
 *
 */
TEST(dbpusher_extractCsvFileName_good) {
        string parameter_one = "/full/path/to/csv/file.csv";
        string expected_return_value = "file.csv";

        string return_value = extractCsvFileName(parameter_one);

        CHECK_EQUAL(expected_return_value, return_value);
}


/*
 * #fail condition
 *
 * Tests dbpusher->extractCsvFileName method
 *
 */
TEST(dbpusher_extractCsvFileName_bad) {
        string parameter_one = "";
        string expected_return_value = "";

        string return_value = extractCsvFileName(parameter_one);

        CHECK_EQUAL(expected_return_value, return_value);
}


/*
 * #succes condition
 *
 * Tests dbpusher->push_list_to_database method
 *
 */
TEST(dbpusher_push_list_to_database_good) {
        string parameter_one = "path/to/file.csv";
        int expected_return_value = 1;

        int return_value = push_list_to_database(parameter_one);

        CHECK_EQUAL(expected_return_value, return_value);


}


/*
 * #fail condition
 *
 * Tests dbpusher->push_list_to_database method
 *
 */
TEST(dbpusher_push_list_to_database_bad) {
        string parameter_one = "";
        int expected_return_value = 0;

        int return_value = push_list_to_database(parameter_one);

        CHECK_EQUAL(expected_return_value, return_value);


}

int main(int, const char *[]) {
    std::ofstream f("testreport.xml");
    UnitTest::XmlTestReporter reporter(f);

    UnitTest::TestRunner runner(reporter);

    return runner.RunTestsIf(UnitTest::Test::GetTestList(), NULL, UnitTest::True(), 0);
}

