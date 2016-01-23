//
// Created by robert on 12/28/15.
//

#ifndef PROCESSING_PDFHELPERFUNCTIONS_H
#define PROCESSING_PDFHELPERFUNCTIONS_H

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

using namespace std;

/****************************************
 * AUXILIARY METHODS USED BY PDFCREATOR.H
 * ***************************************/

template <typename T> int getIndexForBiggestValue(vector<T> valueList)
{
    return distance(valueList.begin(), max_element(valueList.begin(), valueList.end()));
}

template <typename T> int getIndexForSmallestValue(vector<T> valueList)
{
    return distance(valueList.begin(), min_element(valueList.begin(), valueList.end()));
}

int getAverageValueForTwoLists(vector<int> valueList, vector<int> carCountList, int index)
{
    if(valueList.size() > 0)
    {
        int index = getIndexForSmallestValue(valueList);
        int averageValue = fabs((int) valueList[index] / (int) carCountList[index]);
    }
    else
        return 0;
}

const char * computeHttpRequestLength(string parameter1, string parameter2)
{
    int parametersLength = parameter1.length() + parameter2.length();
    parametersLength += 17;
    return to_string(parametersLength).c_str();
}

string checkIfDataAvailable(string stringToCheck)
{
    if(stringToCheck.empty() == true)
        return "Error: No data available";
    else
        return stringToCheck;
}

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

PDF writePdfFrontPage(string typeOfReport, pair<string,string> dates)
{
    PDF pdf;
    pdf.setFont(PDF::Font(6), 27);
    string name = getCurrentDateTime();
    name.substr(0, name.find(".pdf"));

    pdf.showTextXY("CityGis "+ typeOfReport +" Data Report: ", 70, 650);
    pdf.showTextXY(name, 70, 600);

    pdf.setFont(PDF::Font(6), 20);
    pdf.showTextXY("Data gathered from " + dates.first + " to " + dates.second, 70, 570);

    pdf.setFont(PDF::Font(6), 12);
    pdf.showTextXY("Provided by your friends at 'Cooperatio'!", 70, 80);

    return pdf;
}
#endif //PROCESSING_PDFHELPERFUNCTIONS_H
