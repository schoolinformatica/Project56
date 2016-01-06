#ifndef helperfunc
#define helperfunc

#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>

using namespace std;

/*
 * @name -> full path to the file
 *
 * This method checks if the file the path is
 * pointing to exists.
 */
inline bool exist(const string &file) {
    struct stat buffer;
    return (stat(file.c_str(), &buffer) == 0);
}


/*
 * @string_one -> first string
 * @string_two -> second string
 *
 * compares string_one with string_two and
 * returns TRUE if the are equal. Otherwise
 * it returns FALSE.
 *
 */
bool equals(string string_one, string string_two) {
    if(string_one.compare(string_two) == 0)
        return true;
    return false;
}

/*
 * @str -> string that you want to trim
 *
 * Trims all the whitespaces off the string
 * and returns the new string.
 *
 */
string trim(string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}

/*
 * @&file -> File that you want to check existance of
 *
 * Returns true if exists, false otherwise.
 *
 */

bool CheckIfFileExists(const char * filename) 
{
    if (FILE * file = fopen(filename, "r")) {
    	fclose(file);
	return true;
    }
    return false;
}

#endif
