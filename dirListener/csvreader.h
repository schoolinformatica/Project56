#ifndef CSVReader
#define CSVReader


#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

vector<string> csv_read_row(istream &in, char delimiter);

vector<string> headers;

int csvreader(string path) {

    cout << path << endl;
    vector<map<string, string>> mylist2;
    vector<string> mylist1;

    ifstream in("/home/cooperatio/something.csv");

    if (in.fail()) return (cout << "File not found" << endl) && 0;

    while (in.good()) {
        //getting the header
        cout << "file is ok" << endl;
        vector<string> row = csv_read_row(in, ',');
        cout << "csvreader started4.2" << endl;
        cout << path << endl;
        //the first row is the header
        cout << row.size() << endl;
        string header = row[0];
        cout << "csvreader started4.3" << endl;
        stringstream headerstream(header);
        cout << "csvreader started4.4" << endl;
        string headerpart;
        cout << "csvreader started4.5" << endl;

        //pushing it into headers array
        while (getline(headerstream, headerpart, ';')) {
            cout << "csvreader started4.6" << endl;
            headers.push_back(headerpart);
        }
        cout << "csvreader started4.7" << endl;
        for (int i = 0; i < headers.size(); i++) {
            cout << headers.at(i) << endl;
        }
        break;
    }



    ifstream in2("/home/cooperatio/something.csv");
    while (in2.good()) {

        //reading the rest of the CSV file
        vector<string> row = csv_read_row(in2, ';');

        //looping through the rest of the file. except the headers (i = 1)
        for (int i = 0, leng = row.size(); i < leng; i++) {
            mylist1.push_back(row[i]);
        }
    }
    in.close();

    //map for the rows
    map<string, string> rows;
    //looping through the list to put all the items in the map
    for (int i = headers.size(); i < mylist1.size(); i++) {

        rows.insert(pair<string, string>(headers.at(i % headers.size()), mylist1.at(i)));
        //if its the end of the row, add it to the list and clear the map
        if (i % headers.size() == headers.size() - 1) {
            mylist2.push_back(rows);
            rows.clear();
        }
    }

    //this code can be removed. Its to show that in the list the rows are
    for (int i = 0; i < mylist2.size(); i++) {
        for (map<string, string>::iterator ii = mylist2.at(i).begin(); ii != mylist2.at(i).end(); ii++) {
            cout << " " << ii->first << " : " << ii->second << " ";
        }
        cout << endl;
    }

    return 0;
}

vector<string> csv_read_row(istream &in, char delimiter) {
    stringstream ss;
    bool inquotes = false;
    vector<string> row;//relying on RVO
    while (in.good()) {
        char c = in.get();
        if (!inquotes && c == '"') //beginquotechar
        {
            inquotes = true;
        }
        else if (inquotes && c == '"') //quotechar
        {
            if (in.peek() == '"')//2 consecutive quotes resolve to 1
            {
                ss << (char) in.get();
            }
            else //endquotechar
            {
                inquotes = false;
            }
        }
        else if (!inquotes && c == delimiter) //end of field
        {
            row.push_back(ss.str());
            ss.str("");
        }
        else if (!inquotes && (c == '\r' || c == '\n')) {
            if (in.peek() == '\n') { in.get(); }
            row.push_back(ss.str());
            return row;
        }
        else {
            ss << c;
        }
    }
}

#endif