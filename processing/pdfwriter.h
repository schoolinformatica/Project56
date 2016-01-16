//
// Created by robert on 1/16/16.
//

#ifndef PROCESSING_PDFWRITER_H
#define PROCESSING_PDFWRITER_H


/**********************************
* VARIOUS KINDS OF PDF CREATIONS *
**********************************/

#include "pdfcreator.h"
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

void connections_to_pdf(vector<ConnectionEntity> connectionEntities, string email) {
    PDF pdf = writePdfFrontPage("Connections");

    pair<double, double> TimePercentages = getAverages(connectionEntities);
    
    string bestTimePercentageString = checkIfDataAvailable(std::to_string(get<0>(TimePercentages)));
    string worstTimePercentageString = checkIfDataAvailable(std::to_string(get<1>(TimePercentages)));

    string worstCar = checkIfDataAvailable(getCarWithBestOrWorstDataLoss(true, "connections"));
    string bestCar = checkIfDataAvailable(getCarWithBestOrWorstDataLoss(false, "connections"));


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
    vector<string> carsAndDowns = getCarsAndDowntimes("connections");
    int YCounter = 510;
    for(int i = 0; i < carsAndDowns.size(); i++)
    {
        YCounter -= 15;
        pdf.showTextXY(checkIfDataAvailable(carsAndDowns[i]), 70, YCounter);
    }

    pdf_writer(pdf, email);
}


//Note: This method is the "receiver" from main.cpp.
void events_to_pdf(vector<EventEntity> eventEntities, string email) {

    PDF pdf = writePdfFrontPage("Events");

    pair<double, double> IgnitionPercentages = getAverages(eventEntities);

    string bestIgnitionPercentageString = checkIfDataAvailable(std::to_string(get<0>(IgnitionPercentages)));
    string worstIgnitionPercentageString = checkIfDataAvailable(std::to_string(get<1>(IgnitionPercentages)));

    string worstCar = checkIfDataAvailable(getCarWithBestOrWorstDataLoss(true, "events"));
    string bestCar = checkIfDataAvailable(getCarWithBestOrWorstDataLoss(false, "events"));


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
    vector<string> carsAndDowns = getCarsAndDowntimes("events");
    int YCounter = 510;
    for(int i = 0; i < carsAndDowns.size(); i++)
    {
        YCounter -= 15;
        pdf.showTextXY(checkIfDataAvailable(carsAndDowns[i]), 70, YCounter);
    }

    pdf_writer(pdf, email);
}

void positions_to_pdf(vector<PositionEntity> positionEntities, string email) {
    PDF pdf = writePdfFrontPage("Positions");

    string bestHDOPString = checkIfDataAvailable(getCarConnectionDataAverage(false, "HDOP"));
    string worstHDOPString = checkIfDataAvailable(getCarConnectionDataAverage(true, "HDOP"));

    string bestSatString = checkIfDataAvailable(getCarConnectionDataAverage(false, "Quality"));
    string worstSatString = checkIfDataAvailable(getCarConnectionDataAverage(true, "Quality"));

    string worstConnectionString = checkIfDataAvailable(getCarConnectionDataAverage(true, "Satellites"));
    string bestConnectionString = checkIfDataAvailable(getCarConnectionDataAverage(false, "Satellites"));

    string worstCar = checkIfDataAvailable(getCarWithBestOrWorstDataLoss(true, "events"));
    string bestCar = checkIfDataAvailable(getCarWithBestOrWorstDataLoss(false, "events"));

    string worstStoppage = checkIfDataAvailable(getCarWithMostStoppage(true));
    string bestStoppage = checkIfDataAvailable(getCarWithMostStoppage(false));

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

    pdf_writer(pdf, email);
}


#endif //PROCESSING_PDFWRITER_H
