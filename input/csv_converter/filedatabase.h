#ifndef filedatabase
#define filedatabase

#include <iostream>
#include <fstream>

void insert() {
    ofstream myfile;
    myfile.open("home/test.ste");
    myfile << "writing this to the file \n";
    myfile.close();
}

#endif
