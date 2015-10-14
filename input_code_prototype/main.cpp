#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <dirent.h>
#include <iostream>

using namespace std;

//DIRECTORY LISTENING

//Nota: In C++ moet je als een methode een andere methode callt, de methode die gecallt word BOVEN de "caller" zetten
static vector <string> getFileList()
{
	//define pointer + list 
	DIR *dpdf;
	struct dirent *epdf;
	vector <string> dlist;

	//check current dir
	dpdf = opendir("csv/");

	//if not empty
	if (dpdf != NULL)
	{
	   //loop through dir
	   while (epdf = readdir(dpdf))
	   {
		  //push every file into list
		  dlist.push_back(epdf->d_name);
	   }
	}
	closedir(dpdf);
	return dlist;
}

static string checkEvery2Secs()
{
    string filePath;
	//start clock, create vector(basically the same as a Java-style list) with files at 00:00
	clock_t time;
	vector <string> oldlist = getFileList();
    time = clock();
	
	//every 2 secs check if folder got new files
	if(time % 100 == 2)
	{
		//create new list with folder size at 02:00
		vector <string> newlist = getFileList();
		if(newlist.size() > oldlist.size())
		{
			//get last elem: cant select elem like this
			filePath = newlist[newlist.size()];
			//TODO: send file of that elem through to cj
			//reset the oldlist
			oldlist = newlist;
		}
	}
	return filePath;
}

//CSV PARSING

class CSVRow {
public:
    std::string const &operator[](std::size_t index) const {
        return m_data[index];
    }

    std::size_t size() const {
        return m_data.size();
    }

    void readNextRow(std::istream &str) {
        std::string line;
        std::getline(str, line);

        std::stringstream lineStream(line);
        std::string cell;

        m_data.clear();
        while (std::getline(lineStream, cell, ',')) {
            m_data.push_back(cell);
        }
    }

private:
    std::vector<string> m_data;
};

istream & operator >>(std::istream & str, CSVRow& data){
    data.readNextRow(str);
    return str;
}

int main() {


    ifstream file(checkEvery2Secs());

    CSVRow row;
    while (file >> row){
        cout << "(" << row[0] << ") "   << endl;
    }

    cout << "--" << endl;

    int i = 0 ;
    cin >> i;

    ifstream file1(checkEvery2Secs());

    CSVRow row1;
    while (file1 >> row1){
        cout << "(" << row1[0] << ") "   << endl;
    }

    cout << "--" << endl;


	return 0;
}