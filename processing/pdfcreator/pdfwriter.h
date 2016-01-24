//
// Created by robert on 1/16/16.
//

#ifndef PROCESSING_PDFWRITER_H
#define PROCESSING_PDFWRITER_H


/**********************************
* VARIOUS KINDS OF PDF CREATIONS *
**********************************/

#include "dataAggregator.h"
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


class pdfwriterClass
{
    string startDate;
    string endDate;
    string email;

private:
    int connectPDFToUser(string);
    bool pdf_writer(PDF&);
    int sendDirToPHP(const char *);

public:
    void connections_to_pdf(vector<ConnectionEntity>);
    void events_to_pdf(vector<EventEntity>);
    void monitoring_to_pdf(vector<MonitoringEntity>);
    void positions_to_pdf(vector<PositionEntity>);
    void setClassValues(string startDateParam, string endDateParam, string emailParam)
    {
        startDate = startDateParam;
        endDate = endDateParam;
        email = emailParam;
        cout << "Classvalues set!" << endl;
    };
};

/**************************
 * PDF WRITER
 **************************/


//this function connects the email to the filename of the created PDF, so we can store who downloaded which report
int pdfwriterClass::connectPDFToUser(string filename)
{
    cout << "connection user to pdf" << endl;
    Pgsqlcon pgsqlcon;

    //create insert query
    string insert_query = "INSERT INTO userhaspdfs (filename, email) VALUES ('" + filename + "' , '" + email + "');";

    //create vector with the query
    vector<string> queries;
    queries.push_back(insert_query);

    //execute the query
    pgsqlcon.exec_transaction(queries);

    cout << "succesfully created connection" << endl;

    return 1;
}


bool pdfwriterClass::pdf_writer(PDF &pdf) {
    //Create time_t object as param for Ctime, set filename to Ctime
    time_t rawtime;
    time(&rawtime);
    string filename = ctime(&rawtime);
    filename = filename + ".pdf";
    replace(filename.begin(), filename.end(), ' ', '_');
    filename.erase(remove(filename.begin(), filename.end(), '\n'), filename.end());


    //Remove underscores from filename and concat it with the server download dir
    string dir = "http://145.24.222.240/downloads/" + filename;
    const char *dirchar = dir.c_str();

    //writing the PDF to a location on the disk
    string errMsg;
    if (!pdf.writeToFile(filename, errMsg)) {
        cout << "Error writing PDF file!" << errMsg << endl;
        return false;
    }
    else {
        cout << "PDF File Successfully Written" << endl;

        //call function that connects the created pdf to the user-email
        connectPDFToUser(filename);

        //edit this next line when deploying on server
        if (sendDirToPHP(dirchar) != 0) {
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

int pdfwriterClass::sendDirToPHP(const char *directory)
{
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
    inet_aton("http://145.24.222.240", &addr.sin_addr);

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
    << email.c_str()
    << " HTTP/1.1\r\n"
    << "Host: 145.24.222.240\r\n"
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

void pdfwriterClass::connections_to_pdf(vector<ConnectionEntity> connectionEntities)
{
    dataAggregatorClass DataAggregator;
    DataAggregator.setClassValues(startDate, endDate);

    pair<string, string> dates = make_pair(startDate, endDate);
    PDF pdf = writePdfFrontPage("Connections", dates);

    pair<double, double> TimePercentages = DataAggregator.getAverages(connectionEntities);

    string bestTimePercentageString = checkIfDataAvailable(std::to_string(get<0>(TimePercentages)));
    string worstTimePercentageString = checkIfDataAvailable(std::to_string(get<1>(TimePercentages)));

    string worstCar = checkIfDataAvailable(DataAggregator.getCarWithBestOrWorstDataLoss(true, "connections"));
    string bestCar = checkIfDataAvailable(DataAggregator.getCarWithBestOrWorstDataLoss(false, "connections"));

    pdf.newPage();
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Averages: ", 70, 720);
    pdf.drawLine(70, 710, 300, 710);

    //Uptime averages
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Average connection-uptime percentage: " , 70, 690);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(bestTimePercentageString + "%.", 70, 670);

    //Downtime averages
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Average connection-downtime percentage: " , 70, 650);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(worstTimePercentageString + "%.", 70, 630);

    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Car performances: ", 70, 600);
    pdf.drawLine(70, 590, 300, 590);

    //Worst car
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Car with most loss of connection: ", 70, 575);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(worstCar, 70 ,560);

    //Best car
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Car with smallest loss of connection: ", 70, 545);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(bestCar, 70 ,530);


    //List of cars and failures
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Amount of connection failures for each car: ", 70, 510);
    pdf.setFont(PDF::Font(5), 12);
    vector<string> carsAndDowns = DataAggregator.getCarsAndDowntimes("connections");
    int YCounter = 510;
    for(int i = 0; i < carsAndDowns.size(); i++)
    {
        YCounter -= 15;
        pdf.showTextXY(checkIfDataAvailable(carsAndDowns[i]), 70, YCounter);
    }

    pdf_writer(pdf);
}

void pdfwriterClass::events_to_pdf(vector<EventEntity> eventEntities)
{
    dataAggregatorClass DataAggregator;
    DataAggregator.setClassValues(startDate, endDate);

    pair<string, string> dates = make_pair(startDate, endDate);
    PDF pdf = writePdfFrontPage("Events", dates);

    pair<double, double> IgnitionPercentages = DataAggregator.getAverages(eventEntities);

    string bestIgnitionPercentageString = checkIfDataAvailable(std::to_string(get<0>(IgnitionPercentages)));
    string worstIgnitionPercentageString = checkIfDataAvailable(std::to_string(get<1>(IgnitionPercentages)));

    string worstCar = checkIfDataAvailable(DataAggregator.getCarWithBestOrWorstDataLoss(true, "events"));
    string bestCar = checkIfDataAvailable(DataAggregator.getCarWithBestOrWorstDataLoss(false, "events"));


    pdf.newPage();
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Averages: ", 70, 720);
    pdf.drawLine(70, 710, 300, 710);

    //Uptime averages
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Average ignited engine percentage: " , 70, 690);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(bestIgnitionPercentageString + "%.", 70, 670);

    //Downtime averages
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Average stopped engine percentage: " , 70, 650);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(worstIgnitionPercentageString + "%.", 70, 630);

    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Car performances: ", 70, 600);
    pdf.drawLine(70, 590, 300, 590);

    //Worst car
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Car with most stops: ", 70, 575);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(worstCar, 70 ,560);

    //Best car
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Car with least stops: ", 70, 545);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(bestCar, 70 ,530);


    //List of cars and failures
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Amount of engine stops for each car: ", 70, 510);
    pdf.setFont(PDF::Font(5), 12);
    vector<string> carsAndDowns = DataAggregator.getCarsAndDowntimes("events");
    int YCounter = 510;
    for(int i = 0; i < carsAndDowns.size(); i++)
    {
        YCounter -= 15;
        pdf.showTextXY(checkIfDataAvailable(carsAndDowns[i]), 70, YCounter);
    }

    pdf_writer(pdf);
}

void pdfwriterClass::positions_to_pdf(vector<PositionEntity> positionEntities)
{
    dataAggregatorClass DataAggregator;
    DataAggregator.setClassValues(startDate, endDate);

    pair<string, string> dates = make_pair(startDate, endDate);
    PDF pdf = writePdfFrontPage("Positions" ,dates);

    string bestHDOPString = checkIfDataAvailable(DataAggregator.getCarConnectionDataAverage(false, "HDOP"));
    string worstHDOPString = checkIfDataAvailable(DataAggregator.getCarConnectionDataAverage(true, "HDOP"));

    string bestSatString = checkIfDataAvailable(DataAggregator.getCarConnectionDataAverage(false, "Quality"));
    string worstSatString = checkIfDataAvailable(DataAggregator.getCarConnectionDataAverage(true, "Quality"));

    string worstConnectionString = checkIfDataAvailable(DataAggregator.getCarConnectionDataAverage(true, "Satellites"));
    string bestConnectionString = checkIfDataAvailable(DataAggregator.getCarConnectionDataAverage(false, "Satellites"));

    string worstStoppage = checkIfDataAvailable(DataAggregator.getCarWithMostStoppage(true));
    string bestStoppage = checkIfDataAvailable(DataAggregator.getCarWithMostStoppage(false));

    //DIVIDING LINE
    pdf.newPage();
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Satellite-connection performance: ", 70, 720);
    pdf.drawLine(70, 710, 300, 710);

    //bad HDOP
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Worst HDOP performance (Bigger is worse) " , 70, 690);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(worstHDOPString,70, 670);

    //good HDOP
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Best HDOP performance (Smaller is better) " , 70, 650);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(bestHDOPString, 70, 630);

    //bad quality
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Worst average satellite-connection quality: " , 70, 610);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(worstSatString, 70, 590);

    //good quality
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Best average satellite-connection quality: " , 70, 570);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(bestSatString, 70, 550);

    //Bad Sats
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Worst Satellite-connection amount (Smaller is worse) " , 70, 530);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(worstConnectionString, 70, 510);

    //good Sats
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Best Satellite-connection amount (Bigger is better) " , 70, 490);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(bestConnectionString, 70, 470);

    //DIVIDING LINE
    pdf.setFont(PDF::Font(6), 12);
    pdf.drawLine(70, 440, 300, 440);
    pdf.showTextXY("Stoppage analysis: ", 70, 430);
    pdf.drawLine(70, 410, 300, 410);

    //Worst car
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Car with most stoppage: ", 70, 390);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(worstStoppage, 70 ,370);

    //Best car
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Car with least stoppage: ", 70, 350);
    pdf.setFont(PDF::Font(5), 12);
    pdf.showTextXY(bestStoppage, 70 ,330);

    pdf_writer(pdf);
}

/*********************************
 * MONITORING
 * *******************************
 */

void pdfwriterClass::monitoring_to_pdf(vector<MonitoringEntity> monitoringEntities)
{
    dataAggregatorClass DataAggregator;
    DataAggregator.setClassValues(startDate, endDate);
    PDF pdf;

    pdf_writer(pdf);
}

#endif //PROCESSING_PDFWRITER_H
