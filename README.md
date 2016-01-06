# Project56 - CityGis Data 
This project was proudly produced by the "Cooperatio" team, consisting of 5 Computer Science students at the Hogeschool Rotterdam:

- Cees-Jan Nolen
- Steven Schenk
- Robert Kraaijeveld
- William de Visser
- Robin Bakker

This project was made using C/C++ and PHP (inc. The Laravel Framework).

_______________________________________________________

#Goal of this project

The goal of this projects was to create a system that could take as input large CSV-files from CityGis (http://www.digmap.com/products/citygis.htm)
containg all kinds of information about (goverment) vehicles outfited with CityGis communication devices. The system should also be able to
run statistical analysis' and enable the user to download (pdf) reports about these analysis', among others.

#System structure 

The system is comprised of 3 subsystems, that could potentially run independently from each other. 
These subsystems are:

- <b>Input:</b> The input-subsystem is responsible for receiving CityGis CSV files as they are uploaded, and insert them into our 
postgres-database as quickly as possible. The input subsystem is made completely in C/C++, and consists of a listener that monitors a given directory for added CSV files. If the listener detects a new CSV file, it will automatically call the database-pusher on this file.The database-pusher (which uses Pqxx, a library for interacting with a postgres-style database through C++) constructs and executes a COPY FROM-query on the given CSV file.

  The input-subsystem uses threading, so it can handle multiple CSV files at the same time. The average processing speed for a CSV file (from the listener detecting the change to the query finishing) is <i>+- 15 seconds for a 100mb file.</i>

- <b>Processing:</b> The processing subsystem is mainly responsible for calculating measurements out of the CityGis-data in our database, and creating PDF-reports and other visualizations of these measurements. The processing subsystem is also made in C/C++, with a few functions being embedded within the Output-subsystem.

  PDF reports are created on demand when a request from the Output-subsystem is made by the user (in simpler words: When you click the   big button that says "Download a PDF report") and depending on which CSV file the user wants a report on, a PDF file with certain measurements is created an placed in a special directory on our server. Afterwards, an email is sent to the emailadress the user specified in the downloadpage, containing a link to the requested report. 

- <b>Output:</b> The output-subsystem is a laravel-website, containing a login and registration-system and various ways for the user to interact with the input and output-subsystems. The user can upload (multiple) CSV files that are then picked up by the input-subsystem. The user can download PDF-reports via email, or look at vehicle-health via the website itself.

You can read details about each subsystem in their respective folders: input/, processing/, http/.





