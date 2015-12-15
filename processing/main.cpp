#include <iostream>
//#include "pdfcreator.h"
#include "helperfunc/helperfunc.h"
#include "EntityManager.h"
#include "dbreader.h"

using namespace std;

//method start for making pdf 
int start(string file, string email){

	vector <dbEntity> results = read_from_database("positions", "*", "");
	//generating a PDF with the list. The email that is given is used
	//to send the PDF to the user.
	//pdfcreator(results, email);
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

	if (equals(file1, "positions") || equals(file1, "monitoring") || equals(file1, "connections") || equals(file1, "events")) {
		//calling method start
		start(file1, email1);
		return 0;
	}
	else {
		return -1;
	}

}


