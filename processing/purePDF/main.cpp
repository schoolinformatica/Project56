#include <iostream>
#include "pdfcreator.h"
#include "fdbread.h"
#include "fdbhelperfunc.h"
#include "filedatabase.h"

using namespace std;

//method start for making pdf 
int start(string file, string email){
	//getting a list with maps containing data about a table
	vector<map <string, string> > result = select(file, "*", "*");
	//generating a PDF with the list. The email that is given is used
	//to send the PDF to the user.
	pdfcreator(result, email);
	cout << "Done" << endl;
	return 0;
}


//main method. 
int main(int argc, char *argv[]) {
	//creating 2 string variables for the email and file
	string file1, email1;
	//getting email and file from the arguments of the main method.
	email1 = argv[2];
	file1 = argv[1];

	//calling method start 
	start(file1, email1);

    	return 0;
}

