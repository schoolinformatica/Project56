#ifndef fdbhelperfunc
#define fdbhelperfunc

#include <vector>
#include <sstream>
#include <map>
#include <fstream>
#include <algorithm>
#include <sys/stat.h>
#include <string.h>
#include <cctype>

#define EOI "end of info" /* End of info section */
#define EOH "--------" /* End of header section */

using namespace std;

/* Path to the folder where all the database files will be stored */
string storage_path = "/home/ubuntu-0902130/filedatabase/";
//string storage_path = "C:/Users/steve/Homestead/projects/project56/filebasedstorage/";


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
 * @str -> the string that has to be trimmed
 *
 * This method removes all characters, except
 * alphabatic characters from the string and
 * returns it.
 */
string trim_string(string str) {
    size_t i = 0;
    size_t len = str.length();
    while(i < len){
        if (!isalnum(str[i]) || str[i] == ' '){
            str.erase(i,1);
            len--;
        }else
            i++;
    }

    return str;
}

/*
 * @item -> item that you want to find in the list
 * @list -> the list you want to search
 *
 * This method returns the index of the item in
 * the list if founded.
 */
int find_list(string item, vector<string> list) {
    for(int i = 0; i < list.size(); i++) {
        if(item.find(list[i]) != string::npos) {
            return i;
        }
    }
    return -1;
}

/*
 * @file -> full path to the file you want the header from
 *
 * This method reads a delimitter seperated value files
 * and stops when it has rode the header. It returns
 * the header columns.
 */
vector<string> read_header(string file) {
    ifstream in(file);
    vector<string> headerlist;
    string column;
    bool startheader = false;

    while (getline(in, column, ';')) {

        if (column.find(EOH) != string::npos)
            break;

        headerlist.push_back(column);

    }
    in.close();
    return headerlist;
}


/*
 * @list -> string that you want to covert to a vector
 * @delim -> character that you want to use as delimitter
 *
 * This method converts a string to a list splitted by
 * the delimitter char.
 */
vector<string> toList(string list, char delim) {
    istringstream iss(list);
    vector<string> newlist;
    string entry;

    while (getline(iss, entry, delim)) {
        newlist.push_back(entry);
    }

    return newlist;
}

/*
 * @header -> Vector containing the header columns
 *
 * This method checks the header columns for the
 * "#" character. If it contains an # than it is a
 * indexed columns. It returns the indexed columns.
 */
vector<string> get_indexed_columns(vector<string> header) {
    vector<string> indexed_columns;

    for (int i = 0; i < header.size(); ++i) {
        if (header.at(i).find("#") != string::npos)
            indexed_columns.push_back(header[i]);
    }

    return indexed_columns;
}

/*
 * @table -> name of the table you want to get data from
 *
 * This method searches in the tables.ss file for
 * the columns of the @table. It returns the columns.
 */
vector<string> get_table(string table) {
    ifstream in(storage_path + "tables.ss");

    vector<string> columns;
    vector<string> headerlist;
    string column;

    while (getline(in, column, ';')) {
        if (column.find(EOH) != string::npos) {
            headerlist.push_back(column);
            break;
        }
    }
    while (getline(in, column, ';')) {
        if (column.find(table) != string::npos) {
            getline(in, column, ';');
            columns = toList(column, ',');
        }
    }
    in.close();
    return columns;
}


/*
 * @file -> full path to the file you want data from
 *
 * This method reads a dsv file and returns the data.
 */
vector<map<string, string>> read_data(string file) {
    vector<string> header_list = read_header(file);
    vector<map<string, string>> all_rows;
    map<string, string> row;
    string column;
    const unsigned int length = 10000;
    char Buffer[length];


    ifstream index;
    index.rdbuf()->pubsetbuf(Buffer, length);
    index.open(file);

    while (getline(index, column, ';')) {
        if (column.find(EOH) != string::npos)
            break;
    }
    int x = 0;
    while (getline(index, column, ';')) {
        row.insert(pair<string, string>(header_list.at(x), column));
        if (x == header_list.size() - 1) {
            all_rows.push_back(row);
            row.clear();
            x = 0;
        }

        x++;
    }
    index.close();
    return all_rows;
}

/*
 * @s -> string you want to check
 *
 * This method checks if a string is a numeric character.
 */
bool is_number(const string &s) {
    return !s.empty() && find_if(s.begin(), s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

/*
 * @str -> string you want to check
 *
 * This method checks if a string is in date format
 * (yyyy-mm-dd)
 */
bool is_date(string str) {
    if (str.length() != 10)
        return false;

    for (int i = 0; i < str.length(); i++) {
        if ((i == 4) || (i == 7)) {
            if (!(str[i] == '-'))
                return false;
            else
                continue;
        }
        if (!isdigit(str[i]))
            return false;
    }

    return true;
}

/*
 * @d1 -> date 1
 * @d2 -> date 2
 *
 * This method checks which of the two dates is
 * later/earlier. It returns the difference.
 */
int compare_date(const char *d1, const char *d2) {
    int rc;
    // compare years
    rc = strncmp(d1, d2, 4);
    if (rc != 0)
        return rc;

    // compare months
    rc = strncmp(d1 + 5, d2 + 5, 2);
    if (rc != 0)
        return rc;

    // compare days
    return strncmp(d1 + 8, d2 + 8, 2);
}

/*
 * @i -> integer to be converted to string
 *
 * This method converts a integer to a string
 */
string int_to_string(int i) {
    stringstream ss;
    ss << i;
    string str = ss.str();

    return str;
}

/*
 * @list -> the vector you want to remove the duplicates from
 *
 * This method removes all the duplicates from a vector
 * and then returns the vector without duplicates values
 */
vector<string> remove_duplicates(vector<string> list) {
    vector<string> newlist;
    string column;
    for (int i = 0; i < list.size(); ++i) {
        stringstream ss(list[i]);

        int x = 0;
        while (getline(ss, column, ' ')) {
            if (x == 0) {
                newlist.push_back(column);
                x += 1;
            } else {
                x = 0;
            }

        }
    }

    sort(newlist.begin(), newlist.end());
    newlist.erase(unique(newlist.begin(), newlist.end()), newlist.end());

    return newlist;
}

/*
 * @list -> vector you want to convert to string
 *
 * This method converts a list to a string.
 * Format: item 0, item 1, item 2, etc.
 */
string list_to_string(vector<string> list) {
    string s = "";
    for (int i = 0; i < list.size(); ++i) {
        s += list.at(i);

        if (i != list.size() - 1)
            s += ",";
    }
    return s;
}

/*
 * @v_one -> vector one
 * @v_two -> vector two
 *
 * This method takes 2 vectors and combines them to
 * 1 vector. Indentical values are not removed.
 */
vector<string> combine_lists_dif(vector<string> v_one, vector<string> v_two) {
    for (int i = 0; i < v_two.size(); i++) {
        for (int x = 0; x < v_one.size(); i++) {
            if (v_two.at(i).find(v_one.at(x)) != string::npos)
                v_two.erase(v_two.begin() + i);
        }
    }

    for (int j = 0; j < v_two.size(); ++j) {
        v_one.push_back(v_two.at(j));
    }

    return v_one;
}

/*
 * @v_one -> vector one
 * @v_two -> vector two
 *
 * This method takes 2 vectors and combines them to
 * 1 vector. Indentical values are removed.
 */
vector<string> combine_lists_same(vector<string> v_one, vector<string> v_two) {
    for (int i = 0; i < v_two.size(); i++) {
        for (int x = 0; x < v_one.size(); i++) {
            if (v_two.at(i).find(v_one.at(x)) == string::npos)
                v_two.erase(v_two.begin() + i);
        }
    }

    for (int j = 0; j < v_two.size(); ++j) {
        v_one.push_back(v_two.at(j));
    }

    return remove_duplicates(v_one);
}

/*
 * @list -> list you want to check
 * @values -> values you want to check
 *
 * This method checks string values seperated by
 * a ',' if they exist in the vector.
 */
bool in_list(vector<string> list, string values) {
    vector<string> limits = toList(values, ',');

    if (is_number(limits[0])) {
        for (int i = 0; i < list.size(); i++) {
            if (atoi(list[i].c_str()) >= atoi(limits.front().c_str())
                && atoi(list[i].c_str()) <= atoi(limits.end()->c_str()))
                return true;
        }
    }

    else if (is_date(limits[0])) {
        for (int i = 0; i < list.size(); i++) {
            if (compare_date(list[i].c_str(), limits[0].c_str()) >= 0
                && compare_date(list[i].c_str(), limits.back().c_str()) <= 0)
                return true;
        }
    }

    else {
        return false;
    }
    return false;
}


#endif
