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
#include "dbentities/DBEntityManager.h"
#include "dbreader.h"



/**************************
 * Using Declarations
 **************************/

using namespace std;
int sendDirToPHP(const char *directory, const char *email);

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
        vector<string> &lines,
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

/**********************************
 **********************************
 * STANDARD PDF FUNCTIONS         *
 **********************************
 **********************************/

/*********************************
 * AUXILIARY METHODS
 * *******************************
 */

string createPdfFileName() {
    //Use Current time and date, with spaces replaced by underscores as filename.
    time_t rawtime;
    time(&rawtime);

    string filename = ctime(&rawtime);
    filename = filename + ".pdf";
    replace(filename.begin(), filename.end(), ' ', '_');
    filename.erase(remove(filename.begin(), filename.end(), '\n'), filename.end());

    return filename;
}

string getCurrentDateTime() {
    //Use Current time and date, without spaces replaced by underscores as in filename.
    time_t rawtime;
    time(&rawtime);
    string filename = ctime(&rawtime);

    return filename;
}

PDF writePdfFrontPage(string typeOfReport)
{
    PDF pdf;
    pdf.setFont(PDF::Font(6), 27);
    string name = getCurrentDateTime();
    name.substr(0, name.find(".pdf"));

    pdf.showTextXY("CityGis "+ typeOfReport +" Data Report: ", 70, 650);
    pdf.showTextXY(name, 70, 600);

    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Provided by your friends at 'Cooperatio'!", 70, 80);

    return pdf;
}


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
 **********************************
 * VARIOUS KINDS OF PDF CREATIONS *
 **********************************
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

    vector<EventEntity> eventsEntities = convert_to_events(em.getAllWithIgnitedPort());
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
/*
    // We draw every hundred number on the x axis
    for (int xas = 0; xas < dates.size(); xas++) {
        // The +95 makes sure the line isnt drawn directly in the corner of the pdf.
        pdf.showTextXY(dates[xas * scale], xas + 95, 95);
    }

    for (int yas = 0; yas < ports.size(); yas++) {
        // The +95 makes sure the line isnt drawn directly in the corner of the pdf.
        //pdf.showTextXY(std::to_string(ports[yas] * scale), 95, yas + 95);
        pdf.showTextXY("derp", 95, yas + 95);
    }
*/
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

double getAverageConnectionUptime(vector<ConnectionEntity> connectionEntities)
{
    vector<bool> allTruePortValues;
    for (ConnectionEntity c : connectionEntities) {
        if (c.get_value() == true)
            allTruePortValues.push_back(c.get_value());
    }
    //fabs returns an absolute, non-rounded value (IE. 0.5463 instead of 0.)
    double averageUpTimePercentage = fabs((double) allTruePortValues.size() / (double) connectionEntities.size()) * 100;
    cout << averageUpTimePercentage << " is the average uptime. " << endl;
}


vector<string> getCarsAndConnectionDowntimes()
{
    EntityManager em;
    vector<ConnectionEntity> connectionEntities = convert_to_connections(em.getAllWithIgnitedPort());
    vector<string> carsAndDownTimes;

    for(ConnectionEntity c : connectionEntities)
    {
        carsAndDownTimes.push_back(c.get_unit_id(), c.get_value());
    }
    return carsAndDownTimes;
}



//Does the actual work of drawing everything connection.csv related to the pdf.
void connections_to_pdf(vector<ConnectionEntity> connectionEntities, string email) {
    PDF pdf = writePdfFrontPage("Connections");

    double averageUpTimePercentage = getAverageConnectionUptime(connectionEntities);

    pdf.newPage();
    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Connection-data: ", 70, 720);
    pdf.drawLine(70, 710, 300, 710);

    pdf.setFont(PDF::Font(7), 12);
    pdf.showTextXY("Average connection-uptime percentage: " + std::to_string(averageUpTimePercentage) + "%.", 70, 680);

    //DOING
    pdf.showTextXY("Amount of connection failure for each car: ", 70, 700);
    for(int i = 0)


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
