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
    string dir = "http://145.24.222.182/downloads/" + filename;
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
    addr.sin_port = htons(80);
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
    cout << requeststr << endl;
    //We send our request
    send(s, requeststr.c_str(), requeststr.length(), 0);
    //And close our socket to the server
    close(s);

    return 1;
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

//GENERIFIED FOR USE WITH BOTH HDOP AND NUMOFSATELLITES
string getCarConnectionDataAverage(bool searchForWorst, string typeOfSearch)
{
    EntityManager em;
    //Note! We do not use the standard converting method, because our query does not return all columns!

    if (typeOfSearch.compare("HDOP") == 0)
    {
        vector<PositionEntity> positionsEntities = convert_to_positionsHDOP(em.getHDOPPerCar());
        vector<string> unitIDs;
        vector<int> totalHDOPValue;
        vector<int> totalCarCount;
        ostringstream returnvalue;

        for(PositionEntity p : positionsEntities)
        {
            unitIDs.push_back(p.get_unit_id());
            totalHDOPValue.push_back(p.get_hdop());
            totalCarCount.push_back(p.get_countOfUnitID());
        }

        if(searchForWorst == true)
        {
            //get index for biggest HDOP sum-value (big is bad)
            int index;
            index = distance(totalHDOPValue.begin(), max_element(totalHDOPValue.begin(), totalHDOPValue.end()));
            int averageHDOPValue = fabs((int) totalHDOPValue[index] / (int) totalCarCount[index]);

            returnvalue << "Car no. " + unitIDs[index]
            << " had an average HDOP value of " + to_string(averageHDOPValue);
            return returnvalue.str();
        }
        else
        {
            //get index for smallest HDOP sum-value (small is bad)
            int index;
            index = distance(totalHDOPValue.begin(), min_element(totalHDOPValue.begin(), totalHDOPValue.end()));
            int averageHDOPValue = fabs((int) totalHDOPValue[index] / (int) totalCarCount[index]);

            returnvalue << "Car no. " + unitIDs[index]
            << " had an average HDOP value of " + to_string(averageHDOPValue);
            return returnvalue.str();
        }
    }
    else if (typeOfSearch.compare("Satellites") == 0)
    {
        vector<PositionEntity> positionsEntities = convert_to_positionsSats(em.getNumSatellitesPerCar());
        vector<string> unitIDs;
        vector<int> totalSatsValue;
        vector<int> totalCarCount;
        ostringstream returnvalue;

        for(PositionEntity p : positionsEntities)
        {
            unitIDs.push_back(p.get_unit_id());
            totalSatsValue.push_back(p.get_num_satelites());
            totalCarCount.push_back(p.get_countOfUnitID());
        }

        if(searchForWorst == true)
        {
            //get index for smallest amount of satellite connections
            int index;
            index = distance(totalSatsValue.begin(), min_element(totalSatsValue.begin(), totalSatsValue.end()));
            int averageSatValue = fabs((int) totalSatsValue[index] / (int) totalCarCount[index]);

            returnvalue << "Car no. " + unitIDs[index]
            << " was connected to an average of " + to_string(averageSatValue) + " satellites at any given time.";
            return returnvalue.str();
        }
        else
        {
            //get index for biggest amount of satellite connections
            int index;
            index = distance(totalSatsValue.begin(), max_element(totalSatsValue.begin(), totalSatsValue.end()));
            int averageSatsValue = fabs((int) totalSatsValue[index] / (int) totalCarCount[index]);

            returnvalue << "Car no. " + unitIDs[index]
            << " was connected to an average of " + to_string(averageSatsValue) + " satellites at any given time.";
            return returnvalue.str();
        }
    }
    else if (typeOfSearch.compare("Quality") == 0)
    {
        vector<PositionEntity> positionsEntities = convert_to_positionsQuality(em.getQualityPerCar());
        vector<string> unitIDs;
        vector<int> totalQualityValue;
        ostringstream returnvalue;

        for(PositionEntity p : positionsEntities)
        {
            unitIDs.push_back(p.get_unit_id());
            totalQualityValue.push_back(p.get_qualityCount());
        }

        if(searchForWorst == true)
        {
            //get index for smallest count of dGPS quality values
            int index;
            index = distance(totalQualityValue.begin(), min_element(totalQualityValue.begin(), totalQualityValue.end()));
            returnvalue << "Car no. " + unitIDs[index]
            << " had a GPS quality value of 'dGPS' a total of " + to_string(totalQualityValue[index]) + " times.";

            return returnvalue.str();
        }
        else
        {
            //get index for biggest count of dGPS quality values
            int index;
            index = distance(totalQualityValue.begin(), max_element(totalQualityValue.begin(), totalQualityValue.end()));
            returnvalue << "Car no. " + unitIDs[index]
            << " had a GPS quality value of 'dGPS' a total of " + to_string(totalQualityValue[index]) + " times.";

            return returnvalue.str();
        }
    }
    else
    {
        cout << "Type of query not recognized!" << endl;
        return "unknown";
    }
}

string getCarWithMostStoppage(bool searchForWorstCar)
{
    EntityManager em;
    //Note! We do not use the standard converting method, because our query does not return all columns!
    vector<PositionEntity> positionsEntities = convert_to_positionsStops(em.getStopsPerCoordinate());
    vector<string> coordinatesAndStops;
    vector<string> stopsCount;

    for(PositionEntity p : positionsEntities)
    {
        coordinatesAndStops.push_back
                ("At coordinates " + to_string(p.get_rdx()) + ", "
                 + to_string(p.get_rdy()) +  " Car no. " + to_string(p.get_unit_id()) + " was stopped " + to_string(p.get_speed()) + " times.");
        stopsCount.push_back(to_string(p.get_speed()));
    }
    //Get the index of the biggest element, return the element at that index in the coordinatesAndStops-vector.
    int index;
    if(searchForWorstCar == true)
        index = distance(stopsCount.begin(), max_element(stopsCount.begin(), stopsCount.end()));
    else
        index = distance(stopsCount.begin(), min_element(stopsCount.begin(), stopsCount.end()));

    return coordinatesAndStops[index];
}


vector<string> getCoordinatesWithMostStoppage()
{
    EntityManager em;
    //Note! We do not use the standard converting method, because our query does not return all columns!
    vector<PositionEntity> positionsEntities = convert_to_positionsStops(em.getStopsPerCoordinate());
    vector<string> coordinatesAndStops;

    for(PositionEntity p : positionsEntities)
    {
        coordinatesAndStops.push_back
                ("At coordinates " + to_string(p.get_rdx()) + ", "
                 + to_string(p.get_rdy()) + " cars were stopped " + to_string(p.get_speed()) + " times.");
    }
    return coordinatesAndStops;
}


void positions_to_pdf(vector<PositionEntity> positionsEntities, string email) {
    PDF pdf = writePdfFrontPage("Positions");

    //DIVIDING LINE
    pdf.newPage();
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Satellite-connection performance: ", 70, 720);
    pdf.drawLine(70, 710, 300, 710);

    //bad HDOP
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Worst HDOP performance (Bigger is worse) " , 70, 690);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(getCarConnectionDataAverage(true, "HDOP"), 70, 670);

    //good HDOP
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Best HDOP performance (Smaller is better) " , 70, 650);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(getCarConnectionDataAverage(false, "HDOP"), 70, 630);

    //bad quality
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Worst average satellite-connection quality: " , 70, 610);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(getCarConnectionDataAverage(true, "Quality"), 70, 590);

    //good quality
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Best average satellite-connection quality: " , 70, 570);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(getCarConnectionDataAverage(false, "Quality"), 70, 550);

    //Bad Sats
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Worst Satellite-connection amount (Smaller is worse) " , 70, 530);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(getCarConnectionDataAverage(true, "Satellites"), 70, 510);

    //good Sats
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Best Satellite-connection amount (Bigger is better) " , 70, 490);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(getCarConnectionDataAverage(false, "Satellites"), 70, 470);

    //DIVIDING LINE
    pdf.setFont(PDF::Font(6), 12);
    pdf.drawLine(70, 440, 300, 440);
    pdf.showTextXY("Stoppage analysis: ", 70, 430);
    pdf.drawLine(70, 410, 300, 410);

    //Worst car
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Car with most stoppage: ", 70, 390);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(getCarWithMostStoppage(true), 70 ,370);

    //Best car
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Car with least stoppage: ", 70, 350);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(getCarWithMostStoppage(false), 70 ,330);

    pdf_writer(pdf, email);
}


/*********************************
 * CONNECTIONS
 * *******************************
 */

//GENERIFIED FOR USE IN BOTH CONNECTIONS AND EVENTS
//Average loss and gain of T in percentage

template <typename T>
pair<double,double> getAverages(vector<T> listOfEntities)
{
    vector<bool> allTruePortValues;
    vector<bool> allFalsePortValues;

    string typeOfVector = typeid(listOfEntities[0]).name();
    typeOfVector.erase(typeOfVector.begin(), typeOfVector.begin() + 2);

    if(typeOfVector.compare("ConnectionEntity") == 0 || typeOfVector.compare("EventEntity") == 0)
    {
        for (T e : listOfEntities)
        {
            if (e.get_value() == true)
                allTruePortValues.push_back(e.get_value());
            else
                allFalsePortValues.push_back(e.get_value());
        }
    }
    else
    {
        cout << "Not a valid entitytype." << endl;
        return make_pair(0.0, 0.0);
    }

    //fabs returns an absolute, non-rounded value (IE. 0.5463 instead of 0.)
    double averageUpTimePercentage = fabs((double) allTruePortValues.size() / (double) listOfEntities.size()) * 100;
    double averageDownTimePercentage = fabs((double) allFalsePortValues.size() / (double)listOfEntities.size()) * 100;

    return make_pair(averageUpTimePercentage, averageDownTimePercentage);
}

//GENERIFIED FOR USE IN BOTH CONNECTIONS AND EVENTS
//All downtimes for each car
vector<string> getCarsAndDowntimes(string typeOfCsv)
{
    if(typeOfCsv.compare("connections") == 0)
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
    else if(typeOfCsv.compare("events") == 0)
    {
        EntityManager em;
        //Note! We do not use the standard converting method, because our query does not return all columns!
        vector<EventEntity> eventEntities = convert_to_eventsLite(em.getIgnitionFailuresPerCar());
        vector<string> carsAndDownTimes;

        for(EventEntity e : eventEntities)
        {
            //We get the Distinct unitIds and the amount of 0 values for each unitID. (see dbreader.h and EntityManager.h for more details)
            carsAndDownTimes.push_back("Car no. : " + e.get_unit_id() + " has stopped " + to_string(e.get_countOfValue()) + " times.");
        }
        return carsAndDownTimes;
    }
}

//GENERIFIED FOR USE IN BOTH CONNECTIONS AND EVENTS
//Car with biggest/smallest connection/ignition loss number
string getCarWithBestOrWorstDataLoss(bool searchForWorst, string typeOfCsv)
{
    vector<string> carsAndDownTimes;
    vector<int> valuesOnly;

    if(typeOfCsv.compare("connections") == 0)
    {
        EntityManager em;

        //Note! We do not use the standard converting method, because our query does not return all columns!
        vector<ConnectionEntity> connectionEntities = convert_to_connectionsLite(em.getConnectionFailuresPerCar());

        for(ConnectionEntity c : connectionEntities)
        {
            //We get the Distinct unitIds and the amount of 0 values for each unitID. (see dbreader.h and EntityManager.h for more details)
            carsAndDownTimes.push_back("Car no. : " + c.get_unit_id() + " has lost connection " + to_string(c.get_countOfValue()) + " times.");
            valuesOnly.push_back(c.get_countOfValue());
        }
    }
    //Bit of duplication to make the code less complicated.
    else if(typeOfCsv.compare("events") == 0)
    {
        EntityManager em;

        //Note! We do not use the standard converting method, because our query does not return all columns!
        vector<EventEntity> eventEntities = convert_to_eventsLite(em.getIgnitionFailuresPerCar());

        for(EventEntity e : eventEntities)
        {
            //We get the Distinct unitIds and the amount of 0 values for each unitID. (see dbreader.h and EntityManager.h for more details)
            carsAndDownTimes.push_back("Car no. : " + e.get_unit_id() + " has stopped " + to_string(e.get_countOfValue()) + " times.");
            valuesOnly.push_back(e.get_countOfValue());
        }
    }
    else
    {
        cout << "Unknown CSV file." << endl;
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

    pair<double, double> TimePercentages = getAverages(connectionEntities);

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
    pdf.showTextXY(getCarWithBestOrWorstDataLoss(true, "connections"), 70 ,560);

    //Best car
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Car with smallest loss of connection: ", 70, 545);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(getCarWithBestOrWorstDataLoss(false, "connections"), 70 ,530);


    //List of cars and failures
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Amount of connection failures for each car: ", 70, 510);
    pdf.setFont(PDF::Font(5), 12);
    vector<string> carsAndDowns = getCarsAndDowntimes("connections");
    int YCounter = 510;
    for(int i = 0; i < carsAndDowns.size(); i++)
    {
        YCounter -= 15;
        pdf.showTextXY(carsAndDowns[i], 70, YCounter);
    }

    pdf_writer(pdf, email);
}

/*********************************
 * EVENTS
 * *******************************
 */

//Note: This method is the "receiver" from main.cpp.
void events_to_pdf(vector<EventEntity> eventEntities, string email) {

    PDF pdf = writePdfFrontPage("Events");

    pair<double, double> TimePercentages = getAverages(eventEntities);

    pdf.newPage();
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Averages: ", 70, 720);
    pdf.drawLine(70, 710, 300, 710);

    //Uptime averages
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Average ignited engine percentage: " , 70, 690);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(std::to_string(get<0>(TimePercentages)) + "%.", 70, 670);

    //Downtime averages
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Average stopped engine percentage: " , 70, 650);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(std::to_string(get<1>(TimePercentages)) + "%.", 70, 630);

    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Car performances: ", 70, 600);
    pdf.drawLine(70, 590, 300, 590);

    //Worst car
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Car with most stops: ", 70, 575);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(getCarWithBestOrWorstDataLoss(true, "events"), 70 ,560);

    //Best car
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Car with least stops: ", 70, 545);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(getCarWithBestOrWorstDataLoss(false, "events"), 70 ,530);


    //List of cars and failures
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Amount of engine stops for each car: ", 70, 510);
    pdf.setFont(PDF::Font(5), 12);
    vector<string> carsAndDowns = getCarsAndDowntimes("events");
    int YCounter = 510;
    for(int i = 0; i < carsAndDowns.size(); i++)
    {
        YCounter -= 15;
        pdf.showTextXY(carsAndDowns[i], 70, YCounter);
    }

    pdf_writer(pdf, email);
}
#endif
