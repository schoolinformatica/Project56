/**************************
 * Headers
 **************************/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <complex>
#include <random>
#include <cmath>
#include "pdf.h"

/**************************
 * Using Declarations
 **************************/

using std::ostringstream;
using std::ifstream;
using std::complex;
using std::cout;
using std::endl;
using std::ios;

/**************************
 * Local Functions
 **************************/

// ---------------------------------------------------
// Multiply degrees by (2 * pi / 360.0) to
// obtain radians
// ---------------------------------------------------

static double degreesToRadians(int degrees)
{
   return((3.14159 / 180.0) * degrees);
}

// ---------------------------------------------------
// Read 'fileName' and populate 'lines' with its
// contents (on success, return true).  On error,
// populate 'errMsg' and return false.
// ---------------------------------------------------

static bool getLines(
   const string   &fileName,
   vector<string> &lines,
   string         &errMsg
)
{
   ifstream in;

   in.open(fileName.c_str(), ios::binary);

   if(!in)
   {
      errMsg = "Could not open: [" + fileName + "]";
      return(false);
   }

   string line = "";

   for(;;)
   {
      char c = (char)in.get();

      if(in.eof())
      {
         if(line != "")
            lines.push_back(line);

         break;
      }

      line += c;

      if(c == '\n')
      {
         lines.push_back(line);
         line = "";
      }
   }

   in.close();

   return(true);
}

/***********************************
 * Graph Creator
 ***********************************/

void createGraph(int scale)
{
    //IMPORTANT: This int determines the scale/interval at which the line graph will be drawn. Set it to a whole number.
    int scaler;
    if(scale > 0)
    {
        scaler = scale;
    }
    else
    {
        cout << "Scaler not set or invalid!" << endl;
    }

    PDF pdf;
    string errMsg;
    pdf.setFont(PDF::Font(2), 10);

    //Sequential values for the Y part of the graph, these represent the values in our CSV.
    vector<int> seqYVector;
    for(int y = 0; y < 501; y++)
    {
        //we save every 100 values, including 0; 0 however do not get scaled to / scaler.
        if(y % 100 == 0 && y != 0) {
            seqYVector.push_back(y / scaler);
        }
    }

    //sequential values for the X part of the graph, these represent Date/Time
    vector<int> seqXVector;
    for(int x = 0; x < 501; x++)
    {
        //we save every 100 values, including 0; 0 however do not get scaled to / scaler.
        if(x % 100 == 0 && x != 0) {
            seqXVector.push_back(x / scaler);
        }
    }

    for(int z = 0; z < seqXVector.size(); z++)
    {
        //first x of first dot, first y of first dot, then same for second dot.
        pdf.setLineWidth(1);
        //0-values are not taken, only in the values to the side of the graph below.
        pdf.drawLine(seqXVector[z] + 100, seqYVector[z] + 100, seqXVector[z + 1] + 100, seqYVector[z + 1] + 100);
    }

    // We draw every hundred number on the x axis
    for(int xas =0; xas < seqXVector.size(); xas++)
    {
        // The +95 makes sure the line isnt drawn directly in the corner of the pdf.
        pdf.showTextXY(std::to_string(seqXVector[xas] * scaler), seqXVector[xas] + 95, 95);
    }
    //We draw every hundred number on the y axis.
    //NOTE: We add 0 manually so we can draw the line normally whilst still displaying 0. We only add it to one of the lists, else there would be 2 0's.
    vector<int>::iterator it = seqYVector.begin();
    seqYVector.insert(it, 0);
    for (int yas =0; yas < seqYVector.size(); yas++)
    {
        // The +95 makes sure the line isnt drawn directly in the corner of the pdf.
        pdf.showTextXY(std::to_string(seqYVector[yas] * scaler), 95, seqYVector[yas] + 95);
    }

    for(int i =0; i < seqYVector.size(); i++)
    {
        cout << seqYVector[i] << endl;
    }

    if(!pdf.writeToFile("graph.pdf", errMsg))
    {
        cout << errMsg << endl;
    }
    else
    {
        cout << "(File with graph Successfully Written)" << endl;
    }
    cout << endl;
}

/**************************
 * Main
 **************************/

int main()
{
      //NOTE: Vectors of ints that are used are declared inside the method ATM
      createGraph(5);
      return(0);
}
