/**************************
 * Headers
 **************************/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <complex>
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


/**************************
 * Main
 **************************/

int main()
{
      PDF pdf;
      string errMsg;
      pdf.setFont(PDF::Font(2), 10);

	  //Sequential values for the Y part of the graph, these represent the values in our CSV.
	  vector<int> seqYVector;
	  for(int y = 0; y < 500; y++)
	  {
		  seqYVector.push_back(y);
	  }

	  //sequential values for the X part of the graph, these represent Date/Time
	  vector<int> seqXVector;
	  for(int x = 0; x < 500; x++)
	  {
		  seqXVector.push_back(x);
	  }

	  for(int z = 0; z < seqXVector.size(); z++)
      {
          //first x of first dot, first y of first dot, then same for second dot.
          pdf.setLineWidth(1);
          // The +100 makes sure the line isnt drawn directly in the corner of the pdf.
          pdf.drawLine(seqXVector[z] + 100, seqYVector[z] + 100, seqXVector[z+1] + 100, seqYVector[z+1] + 100);
      }

      // We draw every hundred number on the x axis
      for(int xas =0; xas < seqXVector.size(); xas++)
      {
          if(xas % 100 == 0)
          pdf.showTextXY(std::to_string(seqXVector[xas]), seqXVector[xas] + 95, 95);
      }
      //We draw every hundred number on the y axis
      for (int yas =0; yas < seqYVector.size(); yas++)
      {
          if(yas % 100 == 0)
          pdf.showTextXY(std::to_string(seqYVector[yas]), 95, seqYVector[yas] + 95);
      }

      if(!pdf.writeToFile("graph.pdf", errMsg))
      {
         cout << errMsg << endl;
      }
      else
      {
         cout << "(File Successfully Written)" << endl;
      }
      cout << endl;

      return(0);
}
