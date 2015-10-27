#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>
<<<<<<< HEAD

using std::vector;
using std::cout;
using std::endl;
 
std::vector<std::string> csv_read_row(std::istream &in, char delimiter);
std::vector<std::string> csv_read_row(std::string &in, char delimiter);
 
int main(int argc, char *argv[])
{
=======
#include <bits/stl_list.h>
>>>>>>> 6d65ffed9704e4c8f9963b28b049bc4d64ab7d0c

using namespace std;

vector<string> csv_read_row(istream &in, char delimiter);

int main(int argc, char *argv[]) {

    vector<string> mylist2;

    ifstream in("C:/something.csv");

    if (in.fail()) return (cout << "File not found" << endl) && 0;
<<<<<<< HEAD
    while(in.good())
    {
        std::vector<std::string> row = csv_read_row(in, ';');
        for(int i=0, leng=row.size(); i<leng; i++){}
            cout << row[i] << "\t";
        cout << endl;
=======
    while (in.good()) {
        vector<string> row = csv_read_row(in, ';');

        for (int i = 0, leng = row.size(); i < leng; i++) {

            mylist2.push_back(row[i]);

        }
        //cout << "[" << row[i] << "]" << "\t";
        //cout << endl;
>>>>>>> 6d65ffed9704e4c8f9963b28b049bc4d64ab7d0c
    }
    in.close();
    cout << "ok done" << endl;

<<<<<<< HEAD
    cout << mylist2.size() << endl;
=======
<<<<<<< HEAD



//    std::string line;
//    in.open("/home/robert/something.csv");
//    while(getline(in, line)  && in.good())
//    {
//        std::vector<std::string> row = csv_read_row(line, ';');
//        for(int i=0, leng=row.size(); i<leng; i++)
//            cout << "[" << row[i] << "]" << "\t";
//        cout << endl;
//    }
//    in.close();
 
=======
    cout << mylist2.size();
>>>>>>> f6b5d412d22751de1ada3c9c9144ba92afe1846a
    for (int y = 0 ; y < mylist2.size(); y++){
        cout << mylist2.at(y) << endl;
    }

>>>>>>> 6d65ffed9704e4c8f9963b28b049bc4d64ab7d0c
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