#ifndef PDFCreator
#define PDFCreator
/**************************
 * Headers
 **************************/

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <map>
#include <sstream>
#include <fstream>
#include <complex>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <utility>
#include "pdf.cpp"
#include "pdf.h"
#include "pdfhelperfunctions.h"
#include "../dbentities/PositionEntity.h"
#include "../dbentities/EventEntity.h"
#include "../dbentities/ConnectionEntity.h"
#include "../dbentities/MonitoringEntity.h"
#include "../dbentities/DBEntityManager.h"
#include "../dbreader/dbreader.h"


/**************************
 * Using Declarations
 **************************/

using namespace std;
int sendDirToPHP(const char *directory, const char *email);


/**************************
 * PDF WRITER
 **************************/


bool pdf_writer(PDF &pdf, string email) {
    //Create time_t object as param for Ctime, set filename to Ctime
    time_t rawtime;
    time(&rawtime);
    string filename = ctime(&rawtime);
    filename = filename + ".pdf";
    replace(filename.begin(), filename.end(), ' ', '_');
    filename.erase(remove(filename.begin(), filename.end(), '\n'), filename.end());

    //Remove underscores from filename and concat it with the server download dir
    string dir = "http://145.24.222.182:8000/downloads/" + filename;
    const char *dirchar = dir.c_str();
    const char *emailchar = email.c_str();

    //writing the PDF to a location on the disk
    string errMsg;
    if (!pdf.writeToFile(filename, errMsg)) {
        cout << "Error writing PDF file!" << errMsg << endl;
        return false;
    }
    else {
        cout << "PDF File Successfully Written" << endl;
        //edit this next line when deploying on server
        if (sendDirToPHP(dirchar, emailchar) != 0) {
            cout << "Your report can be found at: <a target='_blank' href='" << dirchar << "'> " << dirchar <<
            "</a> " << endl;
            return true;
        }
        else {
            cout << "Error in sendDirToPHP() ocurred." << endl;
            return false;
        }
    }
}


 /**********************************
 * VARIOUS KINDS OF PDF CREATIONS *
 **********************************/


/*********************************
 * MONITORING
 * *******************************
 */

void monitor_to_pdf(vector<MonitoringEntity> monitoringEntities, string email) {
    PDF pdf;
}

/*********************************
 * POSITIONS
 * *******************************
 */

void positions_to_pdf(vector<PositionEntity> positionsEntities, string email) {
    PDF pdf;
}

/*********************************
 * EVENTS
 * *******************************
 */

void events_show_ports_by_date(string email) {
    //IMPORTANT: Create the front page first!:)
    PDF pdf = writePdfFrontPage("Events");
    pdf.newPage();

    EntityManager em;

    vector<EventEntity> eventsEntities = convert_to_events(em.port());
    vector<int> ports;
    vector<string> dates;

    for (EventEntity e : eventsEntities) {
        ports.push_back(atoi(e.get_port().c_str()));
        dates.push_back(e.get_date_time());
    }

    int scale = 10;

    string errMsg;
    pdf.setFont(PDF::Font(2), 10);

    /*
    * Segmentation fault caused by Z+1 and xas*scale: They both reference
    * to indexes that do not yet exist.
    * Todo: Draw X and Y points and their values: 3 for-loops in total.
     *
     *
     * val        X
     * val   X
     * val   X
     * val X
     * date date date date
    */

    for (int z = 0; z < ports.size(); z++) {
        //first x of first dot, first y of first dot, then same for second dot.
        pdf.setLineWidth(1);
        pdf.drawLine(z+100, ports[z] + 100, z + 1 + 100, ports[z + 1] + 100 );
    }
    pdf_writer(pdf, email);
}

//Note: This method is the "receiver" from main.cpp.
void events_to_pdf(vector<EventEntity> eventEntities, string email) {
    //events_show_ports etc creates a written-on Pdf object, that is further processed by the pdf_writer.
    events_show_ports_by_date(email);
}


/*********************************
 * CONNECTIONS
 * *******************************
 */

//Average loss and gain of connection in percentage
pair<double, double> getAverageConnectionTimes(vector<ConnectionEntity> connectionEntities)
{
    vector<bool> allTruePortValues;
    vector<bool> allFalsePortValues;

    for (ConnectionEntity c : connectionEntities) {
        if (c.get_value() == true)
            allTruePortValues.push_back(c.get_value());
        else
            allFalsePortValues.push_back(c.get_value());
    }
    //fabs returns an absolute, non-rounded value (IE. 0.5463 instead of 0.)
    double averageUpTimePercentage = fabs((double) allTruePortValues.size() / (double) connectionEntities.size()) * 100;
    double averageDownTimePercentage = fabs((double) allFalsePortValues.size() / (double) connectionEntities.size()) * 100;

    return make_pair(averageUpTimePercentage, averageDownTimePercentage);
}

//All downtimes for each car
vector<string> getCarsAndConnectionDowntimes()
{
    EntityManager em;
    //Note! We do not use the standard converting method, because our query does not return all columns!
    vector<ConnectionEntity> connectionEntities = convert_to_connectionsLite(em.getConnectionFailuresPerCar());
    vector<string> carsAndDownTimes;

    for(ConnectionEntity c : connectionEntities)
    {
        //We get the Distinct unitIds and the amount of 0 values for each unitID. (see dbreader.h and EntityManager.h for more details)
        carsAndDownTimes.push_back("Car no. : " + c.get_unit_id() + " has lost connection " + to_string(c.get_countOfValue()) + " times.");
    }
    return carsAndDownTimes;
}

//Car with biggest connection loss number
string getCarWithBestOrWorstConnectionLoss(bool searchForWorst)
{
    EntityManager em;
    //Note! We do not use the standard converting method, because our query does not return all columns!
    vector<ConnectionEntity> connectionEntities = convert_to_connectionsLite(em.getConnectionFailuresPerCar());

    vector<string> carsAndDownTimes;
    vector<int> valuesOnly;

    for(ConnectionEntity c : connectionEntities)
    {
        //We get the Distinct unitIds and the amount of 0 values for each unitID. (see dbreader.h and EntityManager.h for more details)
        carsAndDownTimes.push_back("Car no. : " + c.get_unit_id() + " has lost connection " + to_string(c.get_countOfValue()) + " times.");
        valuesOnly.push_back(c.get_countOfValue());
    }

    int index;
    //Return the index in valuesOnly (which has the same length as carsAndDownTimes so it can be used directly)
    //For the biggest or smallest value.
    if(searchForWorst == true)
        //Measure the distance between the beginning of the array and the location of the biggest or smallest element.
        index = distance(valuesOnly.begin(), max_element(valuesOnly.begin(), valuesOnly.end()));
    else
        index = distance(valuesOnly.begin(), min_element(valuesOnly.begin(), valuesOnly.end()));

    return carsAndDownTimes[index];
}



//Does the actual work of drawing everything connection.csv related to the pdf.
void connections_to_pdf(vector<ConnectionEntity> connectionEntities, string email) {
    PDF pdf = writePdfFrontPage("Connections");

    pair<double, double> TimePercentages = getAverageConnectionTimes(connectionEntities);

    pdf.newPage();
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Averages: ", 70, 720);
    pdf.drawLine(70, 710, 300, 710);

    //Uptime averages
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Average connection-uptime percentage: " , 70, 690);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(std::to_string(get<0>(TimePercentages)) + "%.", 70, 670);

    //Downtime averages
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Average connection-downtime percentage: " , 70, 650);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(std::to_string(get<1>(TimePercentages)) + "%.", 70, 630);


    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Car performances: ", 70, 600);
    pdf.drawLine(70, 590, 300, 590);


    //Worst car
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Car with most loss of connection: ", 70, 575);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(getCarWithBestOrWorstConnectionLoss(true), 70 ,560);

    //Best car
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Car with smallest loss of connection: ", 70, 545);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(getCarWithBestOrWorstConnectionLoss(false), 70 ,530);


    //List of cars and failures
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Amount of connection failures for each car: ", 70, 510);
    pdf.setFont(PDF::Font(5), 12);
    vector<string> carsAndDowns = getCarsAndConnectionDowntimes();
    int YCounter = 510;
    for(int i = 0; i < carsAndDowns.size(); i++)
    {
        YCounter -= 15;
        pdf.showTextXY(carsAndDowns[i], 70, YCounter);
    }

    //Todo: Worst car
    pdf_writer(pdf, email);
}


/**************************
 * Send directory to PHP script. Call this with "dir=<your dir to the PDF file in the var/www/html/public folder>"
 **************************/

int sendDirToPHP(const char *directory, const char *email) {
    //declaring vars +  a struct (chunk of memory) for our socket
    int s, error;
    struct sockaddr_in addr;

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cout << "Error 01: creating socket failed!\n";
        close(s);
        return 0;
    }

    //Setting server destination
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);
    inet_aton("145.24.222.182", &addr.sin_addr);

    //Try to connect to socket
    error = connect(s, (sockaddr *) &addr, sizeof(addr));
    if (error != 0) {
        cout << "Error 02: conecting to server failed!\n";
        close(s);
        return 0;
    }

    //We create a stringstream with the necessary URL and header values.Connection: close makes sure the connection to the url is closed.
    stringstream ss;
    ss << "GET /mailer.php?dir="
    << directory
    << "&emailadress="
    << email
    << " HTTP/1.1\r\n"
    << "Host: 145.24.222.182\r\n"
    << "Connection: close\r\n"
    << "\r\n";
    string requeststr = ss.str();
    //We send our request
    send(s, requeststr.c_str(), requeststr.length(), 0);
    //And close our socket to the server
    close(s);

    return 1;
}
#endif