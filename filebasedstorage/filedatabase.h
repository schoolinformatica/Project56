#ifndef filedatabase
#define filedatabase

#define EOI "end of info" /* End of info section */
#define EOH "end of header" /* End of header section */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;


void readInfo() {

    ifstream in("/home/steve/test.ss");

    vector<string> infolist;
    vector<string> headerlist;
    string column;

    while (getline(in, column, ';')) {
        if (column.find(EOI) != string::npos) {
            infolist.push_back(column);
        }
        else if (column.find(EOH) != string::npos) {
            infolist.push_back(column);
            break;
        }
    }
    in.close();
}

void insert(vector<map<string, string>> rows) {
//    ofstream myfile;
//
//    myfile.open("/home/steve/test.ss", std::ios_base::app);
//    myfile << "writing this to the files;" << endl;
//    myfile.close();
    //readInfo();
    cout << "start converting to .ss" << endl;
        //this code can be removed. Its to show that in the list the rows are
    for (int i = 0; i < listrows.size(); i++) {
        for (map<string, string>::iterator ii = listrows.at(i).begin(); ii != listrows.at(i).end(); ii++) {
            cout << " " << ii->first << " : " << ii->second << " ";
        }
        cout << endl;
    }


}

#endif