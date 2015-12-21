#include <iostream>

//#include "pdfcreator.h"
#include "helperfunc/helperfunc.h"
#include "dbentities/DBEntityManager.h"
#include "dbentities/ConnectionEntity.h"
#include "dbreader.h"


using namespace std;

//method start for making pdf 
int start(string file, string email) {
    cout << "ok " << endl;
    if (equals(file, "positions")) {
        vector<PositionEntity> vectorPositions = convert_to_positions("nothing");
    } else if (equals(file, "monitoring")) {
        vector<MonitoringEntity> vectorMonitoring = convert_to_monitor("nothing");
    } else if (equals(file, "connections")) {
        vector<ConnectionEntity> vectorConnections = convert_to_connections("nothing");
    } else if (equals(file, "events")) {
        vector<EventEntity> vectorEvents = convert_to_events("nothing");
    }
    //vector<dbEntity> results = read_from_database(file, "nothing");
    cout << vectorConnections.size();
    for( ConnectionEntity connectionEntity : vectorConnections){
        cout << connectionEntity.get_date_time() << " " << connectionEntity.get_port() << " " <<
                connectionEntity.get_unit_id() << connectionEntity.get_value() << endl;
    }
//generating a PDF with the list. The email that is given is used
//to send the PDF to the user.
    //pdfcreator(results, email);
    cout << "Done" <<
    endl;
    return 0;
}


//main method. 
int main(int argc, char *argv[]) {
    if (argv[1] != NULL && argv[2] != NULL) {
        //creating 2 string variables for the email and file
        string file1, email1;
        //getting email and file from the arguments of the main method.
        email1 = argv[2];
        file1 = argv[1];

        if (equals(file1, "positions") || equals(file1, "monitoring") || equals(file1, "connections") ||
            equals(file1, "events")) {
            //calling method start
            start(file1, email1);
            return 0;
        }
        else {
            return -1;
        }
    }
    else {
        cout << "No input found." << endl;
        return -1;
    }
}


