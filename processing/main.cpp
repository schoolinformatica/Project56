#include <iostream>

#include "pdfcreator/pdfwriter.h"
#include "pdfcreator/dataAggregator.h"
#include "helperfunc/helperfunc.h"
#include "dbentities/DBEntityManager.h"
#include "dbentities/ConnectionEntity.h"
#include "dbreader/dbreader.h"
#include "dbentities/PositionEntity.h"
#include "dbentities/EventEntity.h"
#include "dbentities/MonitoringEntity.h"
#include "dbreader/dbreader.h"


using namespace std;

//method start for making pdf 
int start(string file, string email, string startDate, string endDate) {

    vector<PositionEntity> vectorPositions;
    vector<MonitoringEntity> vectorMonitoring;
    vector<ConnectionEntity> vectorConnections;
    vector<EventEntity> vectorEvents;

    if (equals(file, "positions"))
    {
         vectorPositions = convert_to_positions("nothing");
         pdfwriterClass writer;
         cout << "writer class created" << endl;
         writer.setClassValues(startDate, endDate, email);
         writer.positions_to_pdf(vectorPositions);
    }
    else if (equals(file, "monitoring"))
    {
        vectorMonitoring = convert_to_monitor("nothing");
        pdfwriterClass writer;
        writer.setClassValues(startDate, endDate, email);
        writer.monitoring_to_pdf(vectorMonitoring);
    }
    else if (equals(file, "connections"))
    {
        vectorConnections = convert_to_connections("nothing");
        pdfwriterClass writer;
        writer.setClassValues(startDate, endDate, email);
        writer.connections_to_pdf(vectorConnections);
    }
    else if (equals(file, "events"))
    {
        vectorEvents = convert_to_events("nothing");
        pdfwriterClass writer;
        writer.setClassValues(startDate, endDate, email);
        writer.events_to_pdf(vectorEvents);
    }

    cout << "Done!" << endl;
    return 0;
}


//main method. 
int main(int argc, char *argv[]) {
    if (argv[1] != NULL && argv[2] != NULL && argv[3] != NULL && argv[4] != NULL) {
        //creating 2 string variables for the email and file
        string file1, email1, startDate, endDate;
        //getting email and file from the arguments of the main method.
        file1 = argv[1];
        email1 = argv[2];
        startDate = argv[3];
        endDate  = argv[4];

        if (equals(file1, "positions") || equals(file1, "monitoring") || equals(file1, "connections") ||
            equals(file1, "events")) {
            //calling method start
            start(file1, email1, startDate, endDate);
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


