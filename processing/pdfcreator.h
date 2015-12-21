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
#include "pdf.cpp"
#include "pdf.h"
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include "dbentities/PositionEntity.h"
#include "dbentities/EventEntity.h"
#include "dbentities/ConnectionEntity.h"
#include "dbentities/MonitoringEntity.h"



/**************************
 * Using Declarations
 **************************/

using namespace std;

/**************************
 * Local Functions
 **************************/

// ---------------------------------------------------
// Multiply degrees by (2 * pi / 360.0) to
// obtain radians
// ---------------------------------------------------

static double degreesToRadians(int degrees) {
    return ((3.14159 / 180.0) * degrees);
}

// ---------------------------------------------------
// Read 'fileName' and populate 'lines' with its
// contents (on success, return true).  On error,
// populate 'errMsg' and return false.
// ---------------------------------------------------

static bool getLines(
        const string &fileName,
        vector <string> &lines,
        string &errMsg
) {
    ifstream in;

    in.open(fileName.c_str(), ios::binary);

    if (!in) {
        errMsg = "Could not open: [" + fileName + "]";
        return (false);
    }

    string line = "";

    for (; ;) {
        char c = (char) in.get();

        if (in.eof()) {
            if (line != "")
                lines.push_back(line);

            break;
        }

        line += c;

        if (c == '\n') {
            lines.push_back(line);
            line = "";
        }
    }

    in.close();

    return (true);
}

// ---------------------------------------------------
// Draw 'theText' at: [x, y] (using the specified
// font and font size) with a box around it
// ---------------------------------------------------

static void drawBoundedText(
        const string &theText,
        int x,
        int y,
        PDF::Font theFont,
        int fontSize,
        PDF &p
) {
    p.setFont(theFont, fontSize);

    p.showTextXY(theText, x, y);

    int width = PDF::stringWidth(
            theFont, fontSize, theText
    );

    int offset = (int) (0.4 * fontSize + 0.5);

    p.drawRect(x, y - offset, width, fontSize + offset);
}

/*
**************************************
* CREATE AND FILL PDF WITH ALL VALUES
*************************************
*/



static void createAndFillPDF(PDF &pdf, vector <string> list, string table) {

    //setting up some settings for the PDF
    pdf.setLineColor(0, 5, 150);
    pdf.setFont(PDF::COURIER, 12);

    //vector <string> headers = get_table(table);

    int sizePDF = 0;
    int horizontalPosition = 0;
    for (int i = 0; i < list.size(); i++) {
        //we create a new page if it reaches the end of the page
        if (horizontalPosition < 2) {
            if (sizePDF % 45 == 0 && sizePDF > 2) {
                sizePDF = 0;
                pdf.newPage();
                pdf.setLineColor(0, 5, 150);
                pdf.setFont(PDF::COURIER, 12);
            }
            //we show text in the pdf
            pdf.showTextXY(list.at(i), 50 + 200 * horizontalPosition, 745 - 15 * sizePDF);
            horizontalPosition++;
        }
        sizePDF++;
    }

}


/***********************************
 * FILL PDF WITH GRAPH
 ***********************************/

//pointer to pdf as param: We want an actual pdf, not a new one
void createGraph(PDF &pdf, int scale, vector<int> y, vector<int> x) {
    //IMPORTANT: This int determines the scale/interval at which the line graph will be drawn. Set it to a whole number.
    int scaler;
    if (scale > 0) {
        scaler = scale;
    }
    else {
        cout << "Scaler not set or invalid!" << endl;
    }
    string errMsg;
    pdf.setFont(PDF::Font(2), 10);

    for (int z = 0; z < x.size(); z++) {
        //first x of first dot, first y of first dot, then same for second dot.
        pdf.setLineWidth(1);
        //0-values are not taken, only in the values to the side of the graph below.
        pdf.drawLine(x[z] + 100, y[z] + 100, x[z + 1] + 100, y[z + 1] + 100);
    }

    // We draw every hundred number on the x axis
    for (int xas = 0; xas < x.size(); xas++) {
        // The +95 makes sure the line isnt drawn directly in the corner of the pdf.
        pdf.showTextXY(std::to_string(x[xas] * scaler), x[xas] + 95, 95);
    }
    //We draw every hundred number on the y axis.
    //NOTE: We add 0 manually so we can draw the line normally whilst still displaying 0. We only add it to one of the lists, else there would be 2 0's.
    vector<int>::iterator it = y.begin();
    y.insert(it, 0);
    for (int yas = 0; yas < y.size(); yas++) {
        // The +95 makes sure the line isnt drawn directly in the corner of the pdf.
        pdf.showTextXY(std::to_string(y[yas] * scaler), 95, y[yas] + 95);
    }
}


/**************************
 * Send directory to PHP script. Call this with "dir=<your dir to the PDF file in the var/www/html/public folder>"
 **************************/

int sendDirToPHP(const char *directory, const char *email) {
    //declaring vars +  a struct (chunk of memory) for our socket
    int s, error;
    struct sockaddr_in addr;

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cout << "Error 01: creating socket failed!\n";
        close(s);
        return 0;
    }

    //Setting server destination
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);
    inet_aton("145.24.222.182", &addr.sin_addr);

    //Try to connect to socket
    error = connect(s, (sockaddr * ) & addr, sizeof(addr));
    if (error != 0)
    {
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


/**************************
 * Main
 **************************/


bool pdf_writer(PDF pdf, string email){
    //Create time_t object as param for Ctime, set filename to Ctime
    time_t rawtime;
    time(&rawtime);
    string errMsg;
    string filename = ctime(&rawtime);
    filename = filename + ".pdf";
    replace(filename.begin(), filename.end(), ' ', '_');
    filename.erase(remove(filename.begin(), filename.end(), '\n'), filename.end());

    //Remove underscores from filename and concat it with the server download dir
    string dir = "http://145.24.222.182:8000/downloads/" + filename;
    const char *dirchar = dir.c_str();
    const char *emailchar = email.c_str();

    //writing the PDF to a location on the disk
    if (!pdf.writeToFile(filename, errMsg)) {
        cout << errMsg << endl;
        return false;
    }
    else {
        cout << "PDF File Successfully Written" << endl;
        //edit this next line when deploying on server
        sendDirToPHP(dirchar, emailchar);
        cout << "Your report can be found at: <a target='_blank' href='" << dirchar << "'> " << dirchar << "</a> " <<
        endl;
        return true;
    }
}


void monitor_to_pdf(vector <MonitoringEntity> monitoringEntities){
    PDF pdf;


}

void events_to_pdf(vector<EventEntity> eventEntities){
    PDF pdf;


}

void positions_to_pdf(vector<PositionEntity> positionsEntities){
    PDF pdf;

}

void connections_to_pdf(vector<ConnectionEntity> connectionEntities){
    PDF pdf;
    //this returns 0, though it shouldnt

    vector<bool> allTruePortValues;
    for(ConnectionEntity c : connectionEntities)
    {
        if(c.get_value() == true)
        allTruePortValues.push_back(c.get_value());
    }

    int averageUpTimePercentage = allTruePortValues.size()/connectionEntities.size();
    cout << averageUpTimePercentage << endl;
    pdf.setFont(PDF::Font(2), 10);
    pdf.showTextXY(std::to_string(averageUpTimePercentage), 100, 100);

    pdf_writer(pdf, "0890289@hr.nl");
}
#endif
