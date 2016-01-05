#include <iostream>

#include "pdfcreator/pdfcreator.h"
#include "helperfunc/helperfunc.h"
#include "dbentities/DBEntityManager.h"
#include "dbentities/ConnectionEntity.h"
#include "dbreader/dbreader.h"


using namespace std;

//method start for making pdf 
int start(string file, string email) {

    vector<PositionEntity> vectorPositions;
    vector<MonitoringEntity> vectorMonitoring;
    vector<ConnectionEntity> vectorConnections;
    vector<EventEntity> vectorEvents;

    if (equals(file, "positions"))
    {
         vectorPositions = convert_to_positions("nothing");
         positions_to_pdf(vectorPositions, email);
    }
    else if (equals(file, "monitoring"))
    {
         vectorMonitoring = convert_to_monitor("nothing");
         monitor_to_pdf(vectorMonitoring, email);
    }
    else if (equals(file, "connections"))
    {
         vectorConnections = convert_to_connections("nothing");
         connections_to_pdf(vectorConnections, email);
    }
    else if (equals(file, "events"))
    {
         vectorEvents = convert_to_events("nothing");
         events_to_pdf(vectorEvents, email);
    }

    cout << "Done!" << endl;
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


