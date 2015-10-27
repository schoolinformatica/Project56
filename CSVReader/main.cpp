#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>
#include <map>

using std::vector;
using std::cout;
using std::endl;

std::vector<std::string> csv_read_row(std::istream &in, char delimiter);


using namespace std;

vector<string> csv_read_row(istream &in, char delimiter);

vector<string> headers;

int main(int argc, char *argv[]) {

    time_t t = time(0);
    vector<map<string, string>> mylist2;
    vector<string> mylist1;

    ifstream in("C:/something.csv");

    if (in.fail()) return (cout << "File not found" << endl) && 0;

    while (in.good()) {
        //getting the header
        vector<string> row = csv_read_row(in, ',');
        //the first row is the header
        string header = row[0];
        stringstream headerstream(header);
        string headerpart;

        //pushing it into headers array
        while (getline(headerstream, headerpart, ';')) {
            headers.push_back(headerpart);
        }
        break;
    }

    ifstream in2("C:/something.csv");
    while (in2.good()) {

        //reading the rest of the CSV file
        vector<string> row = csv_read_row(in2, ';');

        //looping through the rest of the file. except the headers (i = 1)
        for (int i = 0, leng = row.size(); i < leng; i++) {

            mylist1.push_back(row[i]);

        }


    }
    in.close();

    for (int i = headers.size(); i < mylist1.size(); i++) {
        map<string, string> rows;
        rows.insert(pair<string, string>(headers.at(i % headers.size()), mylist1.at(i)));

        mylist2.push_back(rows);
    }
    time_t t1 = time(0);
    cout << t1 << " < t1 t > " << t << endl ;
    cout << t1 - t ;
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