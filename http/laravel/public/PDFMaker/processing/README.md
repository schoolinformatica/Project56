/***********************
* PROCESSING SUBSYSTEM
************************/

The processing subsystems' main job is creating PDF-reports from a postgres-database
containg the CSV data in its' tables.

/DBEntities defines an entitymanager and an entity class for each type of .CSV file.
The entitymanager defines several methods that call the psql_exec_none_transaction() method with
certain types of PostgreSQL queries, retrieving or rows from the Postgres database.

Each of these methods returns a Result Object which contains rows of a certain kind of entity. Each
entity has several getters and setter methods associated with it, which are used by /DBreader: Dbreader
has several methods that take as input a Psql result object and convert it to an actual entity (or list of entities)
by calling the setter methods of the entity.

Example:
--------------------------
EntityManager em;

/*
The various convert_to method in dbreader.h convert the result 
from the entitymanager methods to actual entities by calling their setters.
*/

Vector<ConnectionEntity> listOfConnectionEntities = convert_to_connections(em.anyQueryMethod());

for(ConnectionEntity c : listOfConnectinEntities)
{
   cout << c.get_unit_id() << endl;
} 
---------------------------

The /pdfcreator folder contains the crucial file pdfcreator.h, which contains the following type of methods.

 - Calculators: Methods like getStopsPerCoordinate() that calculate certain averages and statistics using the data
provided within the various entity-objects.

- Helpers: Smaller Methods like writeFrontPage() that do little things. helperfunctions.h contains more usefull
auxilliary methods. 

- to Pdf Converters: For each type of CSV file a report can be created. Each report has a convert_typeOfCsv_to_pdf()
method, which calls various calculators for that type of CSV and writes their values onto a PDF object.

/Pqcon contains methods that interact with the postgres to c++ interface pqxx, as mentioned earlier.

main.cpp is called by downloadFormHandler.php with a CSV type and an email adress.
A report is then created of the given CSV file and it is automatically emailed to the given emailadress
(The email just contains a link to a download directory.) 
