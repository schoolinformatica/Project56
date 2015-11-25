#include <iostream>
//#include "listener.h"
#include "csvreader.h"
//#include "filedatabase/fdbhelperfunc.h"
#include "filedatabase/fdbread.h"

using namespace std;

int main() {

    // start the map listener
    //listener("/var/www/laravel/storage/uploads/");
    //csvreader(storage_path + "positions.csv", "positions");
    vector<map<string, string>> data = select("positions", "*", "*");
    cout << data.size() << endl;

    return 0;
}

