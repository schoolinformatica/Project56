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
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <time.h>



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

// ---------------------------------------------------
// Demonstrate:
//
//    - text wrapping
//    - drawing and filling of circles and ellipses
//    - drawing and filling of rectangles and polygons
//    - drawing lines, using different line widths
//    - use of images
// ---------------------------------------------------

static void demoOne(PDF &p) {
    p.setFont(PDF::HELVETICA, 12);

    string s = "  \t\t   fee \r\nxxxxxxxxxxxxx\r\n\"fi\"fo fum";

    s += " a aa aaa aaaa bbb bb b c cc ccc dddd eeeee ";
    s += " foo bar baz foo bar baz ";
    s += " mairzy doats and doazy doats and little lambsey divey";
    s += " a kiddley divey too, wouldn't you? ";
    s += " a b c d e f g h i jj kkk llll mmmmmm nnnnnnn oooooooooooo ";
    s += "----------------------- -------------------------- ";
    s += "$$$ $$$$$$$$$$$$$$ $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ ";
    s += "******************** ************************ ***** ";

    vector<string> sv = p.wrapText(s, 100, true);

    for (int i = 0, n = sv.size(); i < n; i++) {
        // cout << "sv[" << i << "][" << sv[i] << "]\n";
        p.showTextXY(sv[i], 80, 745 - 20 * i);
    }

    p.drawLine(80, 760, 80, 300);
    p.drawLine(180, 760, 180, 300);

    // cout << endl;

    p.drawEllipse(400, 550, 150, 75);

    p.setFillColor(255, 255, 0);
    p.fillEllipse(400, 550, 40, 65);

    p.drawEllipse(400, 550, 40, 65);

    for (int i = 0; i < 12; i++) {
        unsigned char value = (unsigned char) (20 * i);

        p.setFillColor(value, value, value);

        p.fillCircle(480, 310 + 10 * i, 2 * i);

        p.drawCircle(480, 310 + 10 * i, 3 * i);
    }

    p.setLineColor(255, 0, 0);
    p.setFillColor(0, 0, 255);

    for (int i = 0; i < PDF::N_FONTS; i++) {
        PDF::Font theFont = (PDF::Font) (i + 1);
        int fontSize = 9;
        int x = 10;
        int y = 36 + (2 * fontSize) * i;

        string s =
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
                        "!@#$%^&*()_-=+[]{};:<>,./?";

        drawBoundedText(s, x, y, theFont, fontSize, p);
    }

    p.fillRect(300, 700, 40, 40);
    p.drawRect(400, 700, 40, 40);

    p.newPage();
    p.setLineColor(255, 0, 0);

    for (int i = 0; i < PDF::N_FONTS; i++) {
        p.setFont((PDF::Font) (i + 1), 20);
        p.showTextXY(PDF::FONTS[i], 100, 100 + 40 * i);
    }

    p.newPage();
    p.setLineColor(255, 0, 0);

    for (int i = 0; i < 20; i++) {
        p.drawLine(0, 0, 30 * (1 + i), 500 - 15 * i);
        p.setLineWidth(i / 2 + 1);
    }

    vector<XY> points;

    points.push_back(XY(300, 500));
    points.push_back(XY(325, 550));
    points.push_back(XY(350, 480));
    points.push_back(XY(375, 570));
    points.push_back(XY(400, 460));
    points.push_back(XY(425, 590));
    points.push_back(XY(450, 450));

    p.setLineColor(0, 255, 0);
    p.drawLine(points);

    points.clear();

    points.push_back(XY(100, 540));
    points.push_back(XY(150, 700));
    points.push_back(XY(80, 700));

    p.setFillColor(200, 200, 200);
    p.fillPolygon(points);

    p.setLineColor(0, 0, 255);
    p.drawPolygon(points);

    p.newPage();

    // Make an image

    ImageRow row1;
    ImageRow row2;

    row1.push_back(RGB(255, 255, 0));
    row1.push_back(RGB(255, 0, 255));
    row1.push_back(RGB(0, 255, 0));

    row2.push_back(RGB(0, 0, 255));
    row2.push_back(RGB(255, 0, 0));
    row2.push_back(RGB(0, 0, 255));

    Image anImage;

    anImage.push_back(row1);
    anImage.push_back(row2);

    ImageInfo info = p.processImage(anImage);
    double scale = 50.0;

    for (int i = 0; i < 10; i++) {
        int xValue = 120 + 30 * i;
        int yValue = 220 + 40 * i;

        p.showImage(info, xValue, yValue, scale);

        p.drawRect(
                xValue,
                yValue,
                (int) (scale * info.mWidth + 0.5),
                (int) (scale * info.mHeight + 0.5)
        );
    }
}

// ---------------------------------------------------
// Demonstrate:
//
//    - the use of 'drawLine' and trigonometry
//      to create a geometric line drawing
// ---------------------------------------------------

static void demoTwo(PDF &p) {
    int xc = p.getWidth() / 2;
    int yc = p.getHeight() / 2;

    int smaller = (xc < yc ? xc : yc);
    int radius = (int) (.9 * smaller);
    int step = 15;

    for (int i = 0; i < 360; i += step) {
        double angle = degreesToRadians(i);

        int x0 = xc + (int) (radius * cos(angle) + 0.5);
        int y0 = yc + (int) (radius * sin(angle) + 0.5);

        for (int j = 0; j < 360; j += step) {
            if (j != i) {
                double theAngle = degreesToRadians(j);

                int x1 = xc + (int) (radius * cos(theAngle) + 0.5);
                int y1 = yc + (int) (radius * sin(theAngle) + 0.5);

                p.drawLine(x0, y0, x1, y1);
            }
        }
    }
}

// ---------------------------------------------------
// Demonstrate:
//
//    - ability to embed program code (this function,
//      'demoThree' itself) in the pdf
//
//    - use of images to create and store a
//      generated fractal image
//
//  Note: The comments before and after the
//        'demoThree' function that look like this:
//
//           // begin: demoThree
//           // end: demoThree
//
//        are markers in the source so that the
//        code for the 'demoThree' function can
//        be extracted and written to the pdf file
//        file and that process will fail if those
//        comments are altered/removed
//
// ---------------------------------------------------

// begin: demoThree

static void demoThree(PDF &p) {
    // Create an image, 500 pixels square

    int width = 500;
    int height = 500;

    Image anImage;

    RGB theColor(0, 0, 0);

    for (int i = 0; i < height; i++) {
        ImageRow theRow;

        for (int j = 0; j < width; j++)
            theRow.push_back(theColor);

        anImage.push_back(theRow);
    }

    double yStart = -2.0;
    double yStop = 2.0;
    double yStep = (yStop - yStart) / (height - 1);

    double xStart = -2.0;
    double xStop = 2.0;
    double xStep = (xStop - xStart) / (width - 1);

    int maxIterations = 25;
    double maxDistance = 1000.0;

    typedef complex<double> Complex;

    int iValue = 0;

    for (double y = yStart; y <= yStop; y += yStep) {
        int jValue = 0;

        for (double x = xStart; x <= xStop; x += xStep) {
            Complex z(0.0, 0.0);
            Complex c(x, y);

            int iterations = 0;

            while (
                    iterations < maxIterations &&
                    sqrt(z.real() * z.real() + z.imag() * z.imag()) < maxDistance
                    ) {
                z = z * z + c;
                iterations++;
            }

            double v1 = (double) iterations / maxIterations;
            double v2 = sqrt(v1);
            double v3 = sqrt(v2);

            v1 *= 255.0;
            v2 *= 255.0;
            v3 *= 255.0;

            unsigned char red = (unsigned char) (v1 + 0.5);
            unsigned char green = (unsigned char) (v2 + 0.5);
            unsigned char blue = (unsigned char) (v3 + 0.5);

            RGB theColor(red, green, blue);

            anImage[iValue][jValue] = theColor;

            jValue++;
        }

        iValue++;
    }

    // Place the image, centered

    ImageInfo info = p.processImage(anImage);

    int xValue = (p.getWidth() / 2) - (width / 2);
    int yValue = (p.getHeight() / 2) - (height / 2);

    p.showImage(info, xValue, yValue, 1.0);

    p.newPage();

    string errMsg;
    vector<string> lines;

    if (!getLines(__FILE__, lines, errMsg)) {
        cout << errMsg;
    }
    else {
        static const int FONTSIZE = 8;
        static const int MARGIN = 36;
        static const int YSTART = 750;

        int y = YSTART;
        bool showLine = false;

        // Avoid false positive by buidling our
        // markerBegin and markerEnd strings up dynamically

        string tag = "demoThree";
        string markerBegin = "// begin: " + tag;
        string markerEnd = "// end: " + tag;

        bool needSetFont = true;

        for (int i = 0, n = lines.size(); i < n; i++) {
            if (!showLine) {
                if (lines[i].find(markerBegin) != string::npos)
                    showLine = true;
            }
            else {
                if (lines[i].find(markerEnd) != string::npos)
                    showLine = false;

                if (showLine) {
                    if (needSetFont) {
                        p.setFont(PDF::COURIER, FONTSIZE);
                        needSetFont = false;
                    }

                    p.showTextXY(lines[i], MARGIN, y);
                    y -= FONTSIZE;

                    if (y <= MARGIN) {
                        p.newPage();
                        needSetFont = true;
                        y = YSTART;
                    }
                }
            }
        }
    }
}

// end: demoThree

static void demoFour(PDF &pdf, vector<map<string, string>> list) {

    //setting up some settings for the PDF
    pdf.setLineColor(0, 5, 150);
    pdf.setFont(PDF::COURIER, 12);

    int sizePDF = 0;
    // we loop through the list
    for (int i = 0; i < list.size(); i++) {
        int horizontalPosition = 0;
        //we get the map from the list and loop over it.
        for (map<string, string>::iterator ii = list.at(i).begin(); ii != list.at(i).end(); ii++) {

            //Only show 2 columns
            if (horizontalPosition < 2) {
                //if the PDF comes to the end of the page we create a new page
                if (sizePDF % 45 == 0 && sizePDF > 0) {
                    sizePDF = 0;
                    pdf.newPage();
                    pdf.setLineColor(0, 5, 150);
                    pdf.setFont(PDF::COURIER, 12);
                }
                //we show text in the pdf
                pdf.showTextXY(ii->first, 50 + 200 * horizontalPosition, 745);
                pdf.showTextXY(ii->second, 50 + 200 * horizontalPosition, 730 - 15 * sizePDF);

                //we increment the horizontal position and the length of the PDF
                horizontalPosition++;

            }
        }
        sizePDF++;
    }
}




/**************************
 * Send directory to PHP script. Call this with "dir=<your dir to the PDF file in the var/www/html/public folder>"
 **************************/

int sendDirToPHP(const char * directory)
{
    //declaring vars +  a struct (chunk of memory) for our socket
    int s, error;
    struct sockaddr_in addr;

    if((s = socket(AF_INET,SOCK_STREAM,0))<0)
    {
        cout<<"Error 01: creating socket failed!\n";
        close(s);
        return 1;
    }

    //Setting server destination
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);
    inet_aton("145.24.222.182", &addr.sin_addr);

    //Try to connect to socket
    error = connect(s,(sockaddr*)&addr,sizeof(addr));
    if(error!=0)
    {
        cout<<"Error 02: conecting to server failed!\n";
        close(s);
        return 1;
    }

    //We create a stringstream with the necessary URL and header values.Connection: close make sure the connection to the url is closed.
    stringstream ss;
    ss << "GET /mailer.php?dir=" << directory << " HTTP/1.1\r\n"
    << "Host: 145.24.222.182\r\n"
    << "Connection: close\r\n"
    << "\r\n";
    string requeststr = ss.str();
    //We send our request
    send(s,requeststr.c_str(),requeststr.length(),0);
    //And close our socket to the server
    close(s);

    return 0;

}


/**************************
 * Main
 **************************/

int pdfcreator(vector<map<string, string>> list) {

    PDF pdf;

    demoFour(pdf, list);

    string errMsg;

    //Create time_t object as param for Ctime, set filename to Ctime
    time_t rawtime;
    time (&rawtime);
    string filename = ctime(&rawtime);
    replace(filename.begin(), filename.end(), ' ', '_');

    //Remove underscores from filename and concat it with the server download dir
    string dir = "http://145.24.222.182:8000/downloads/" + filename;
    const char * dirchar = dir.c_str();

    //writing the PDF to a location on the disk
    if (!pdf.writeToFile(filename, errMsg)) {
        cout << errMsg << endl;
    }
    else {
        cout << "PDF File Successfully Written" << endl;
        //edit this next line when deploying on server
        sendDirToPHP(dirchar);
        cout << "Mailer called" << endl;
    }


    cout << "All done" << endl;


    return (0);
}

#endif
