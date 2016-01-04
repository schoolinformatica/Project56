/*******************
* INPUT SUBSYSTEM
********************/

The input system monitors a given directory for any newly added CSV files that contain cityGis data.
If one of these files is added, the contents of this file are immediately copied to the Postgres database.

For a bit more detail:

(Note that listener.h is threaded, so the system can indeed handle multiple new CSV files at once.) 

listener.h uses the iNotify linux filemonitoring library to call dbpusher.h when it detects a new CSV file 
being added. dbpusher.h then checks wether or not the CSV file it gets is an actual valid CSV file. 
If the CSV file IS valid, a COPY FROM query is created on the specified CSV file. The query is then executed,
using the files within /Pqcon. These files define an interface from the Psql DBMS to C++ using the Pqxx library.

An average COPY FROM query on a 100 megabyte file took approxiametely 15 seconds to complete the whole
process from copying, listener.h registering the change to the database being updated. 
