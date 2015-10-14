// dirListener.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <cstdio>
#include <ctime>
#include <filesystem>
#include <iostream>
#include <dirent.h>
#include <vector>

using namespace std;
using namespace std::tr2::sys;

//Nota: In C++ moet je als een methode een andere methode callt, de methode die gecallt word BOVEN de "caller" zetten
static vector <string> getFileList()
{
	//define pointer + list 
	DIR *dpdf;
	struct dirent *epdf;
	vector <string> dlist;

	//check current dir
	dpdf = opendir("./");

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

static void checkEvery2Secs()
{
	//start clock, create vector(basically the same as a Java-style list) with files at 00:00
	std::clock_t time;
	vector <string> oldlist = getFileList();
    time = std::clock();
	
	//every 2 secs check if folder got new files
	if(time % 100 == 2)
	{
		//create new list with folder size at 02:00
		vector <string> newlist = getFileList();
		if(newlist.size() > oldlist.size())
		{
			//get last elem: cant select elem like this
			string mystr = newlist[newlist.size()];
			//TODO: send file of that elem through to cj
			//reset the oldlist
			oldlist = newlist;
		}
	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	checkEvery2Secs();
	return 0;
}





