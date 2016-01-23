#ifndef dataAggregator
#define dataAggregator
/**************************
 * Headers
 **************************/

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
#include "pdf.cpp"
#include "pdf.h"
#include "pdfhelperfunctions.h"
#include "pdfwriter.h"
#include "../dbentities/PositionEntity.h"
#include "../dbentities/EventEntity.h"
#include "../dbentities/ConnectionEntity.h"
#include "../dbentities/MonitoringEntity.h"
#include "../dbentities/DBEntityManager.h"
#include "../dbreader/dbreader.h"



/**************************
 * Class Declarations
 **************************/

using namespace std;

class dataAggregatorClass
{
    string startDate;
    string endDate;

public:
    template <typename T> pair<double,double> getAverages(vector<T>);
    string getCarWithBestOrWorstDataLoss(bool, string);
    vector<string> getCarsAndDowntimes(string);
    string getCarConnectionDataAverage(bool, string);
    string getCarWithMostStoppage(bool);
    vector<string> getCoordinatesWithMostStoppage();
    void setClassValues(string startDateParam, string endDateParam)
    {
        startDate = startDateParam;
        endDate = endDateParam;
    };
};


/*********************************
 * POSITIONS
 * *******************************
 */

//GENERIFIED FOR USE WITH BOTH HDOP AND NUMOFSATELLITES
string dataAggregatorClass::getCarConnectionDataAverage(bool searchForWorst, string typeOfSearch)
{
    EntityManager em;
    //Note! We do not use the standard converting method, because our query does not return all columns!

    if (typeOfSearch.compare("HDOP") == 0)
    {
        vector<PositionEntity> positionsEntities = convert_to_positionsHDOP(em.getHDOPPerCar(this->startDate, this->endDate));
        vector<string> unitIDs;
        vector<int> totalHDOPValue;
        vector<int> totalCarCount;
        ostringstream returnvalue;

        for(PositionEntity p : positionsEntities)
        {
            if(positionsEntities.size() > 0)
            {
                unitIDs.push_back(p.get_unit_id());
                totalHDOPValue.push_back(p.get_hdop());
                totalCarCount.push_back(p.get_countOfUnitID());
            }
        }

        if(searchForWorst == true && totalHDOPValue.size() > 0)
        {
            //get index for biggest HDOP sum-value (big is bad)
            int index = getIndexForBiggestValue(totalHDOPValue);
            int averageHDOPValue = getAverageValueForTwoLists(totalHDOPValue, totalCarCount, index);

            returnvalue << "Car no. " + unitIDs[index]
            << " had an average HDOP value of " + to_string(averageHDOPValue);
            return returnvalue.str();
        }
        else if (searchForWorst == false && totalHDOPValue.size() > 0)
        {
            //get index for smallest HDOP sum-value (small is bad)
            int index;
            index = distance(totalHDOPValue.begin(), min_element(totalHDOPValue.begin(), totalHDOPValue.end()));
            int averageHDOPValue = fabs((int) totalHDOPValue[index] / (int) totalCarCount[index]);

            returnvalue << "Car no. " + unitIDs[index]
            << " had an average HDOP value of " + to_string(averageHDOPValue);
            return returnvalue.str();
        }
        else
            return "Error: Data did not contain any matching HDOP values!";
    }
    else if (typeOfSearch.compare("Satellites") == 0)
    {
        vector<PositionEntity> positionsEntities = convert_to_positionsSats(em.getNumSatellitesPerCar(this->startDate, this->endDate));
        vector<string> unitIDs;
        vector<int> totalSatsValue;
        vector<int> totalCarCount;
        ostringstream returnvalue;

        for(PositionEntity p : positionsEntities)
        {
            if(positionsEntities.size() > 0)
            {
                unitIDs.push_back(p.get_unit_id());
                totalSatsValue.push_back(p.get_num_satelites());
                totalCarCount.push_back(p.get_countOfUnitID());
            }
        }

        if(searchForWorst == true && totalSatsValue.size() > 0)
        {
            //get index for smallest amount of satellite connections
            int index = getIndexForSmallestValue(totalSatsValue);
            int averageSatsValue = getAverageValueForTwoLists(totalSatsValue, totalCarCount, index);

            returnvalue << "Car no. " + unitIDs[index]
            << " was connected to an average of " + to_string(averageSatsValue) + " satellites at any given time.";
            return returnvalue.str();
        }
        else if (searchForWorst == false && totalSatsValue.size() > 0)
        {
            //get index for smallest amount of satellite connections
            int index = getIndexForBiggestValue(totalSatsValue);
            int averageSatsValue = getAverageValueForTwoLists(totalSatsValue, totalCarCount, index);

            returnvalue << "Car no. " + unitIDs[index]
            << " was connected to an average of " + to_string(averageSatsValue) + " satellites at any given time.";
            return returnvalue.str();
        }
        else
            return "Error: Data did not contain any matching satellite values!";
    }
    else if (typeOfSearch.compare("Quality") == 0)
    {
        vector<PositionEntity> positionsEntities = convert_to_positionsQuality(em.getQualityPerCar(this->startDate, this->endDate));
        vector<string> unitIDs;
        vector<int> totalQualityValue;
        ostringstream returnvalue;

        for(PositionEntity p : positionsEntities)
        {
            if(positionsEntities.size() > 0)
            {
                unitIDs.push_back(p.get_unit_id());
                totalQualityValue.push_back(p.get_qualityCount());
            }
        }

        if(searchForWorst == true && totalQualityValue.size() > 0)
        {
            //get index for smallest count of dGPS quality values
            int index = getIndexForSmallestValue(totalQualityValue);

            returnvalue << "Car no. " + unitIDs[index]
            << " had a GPS quality value of 'dGPS' a total of " + to_string(totalQualityValue[index]) + " times.";

            return returnvalue.str();
        }
        else if(searchForWorst == false && totalQualityValue.size() > 0)
        {
            //get index for biggest count of dGPS quality values
            int index = getIndexForBiggestValue(totalQualityValue);

            returnvalue << "Car no. " + unitIDs[index]
            << " had a GPS quality value of 'dGPS' a total of " + to_string(totalQualityValue[index]) + " times.";

            return returnvalue.str();
        }
        else
            return "Error: Data did not contain any matching satellite values!";
    }
    else
    {
        cout << "Type of query not recognized!" << endl;
        return "unknown";
    }
}

string dataAggregatorClass::getCarWithMostStoppage(bool searchForWorstCar)
{
    EntityManager em;
    //Note! We do not use the standard converting method, because our query does not return all columns!
    vector<PositionEntity> positionsEntities = convert_to_positionsStops(em.getStopsPerCoordinate(this->startDate, this->endDate));
    vector<string> coordinatesAndStops;
    vector<string> stopsCount;

    for(PositionEntity p : positionsEntities)
    {
        if(positionsEntities.size() > 0)
        {
            coordinatesAndStops.push_back
                    ("At coordinates " + to_string(p.get_rdx()) + ", "
                     + to_string(p.get_rdy()) + " Car no. " + to_string(p.get_unit_id())
                     + " was stopped " + to_string(p.get_speed()) + " times.");
            stopsCount.push_back(to_string(p.get_speed()));
        }
        else
        {
            coordinatesAndStops.push_back("Error: No data found!");
            stopsCount.push_back(0);
        }
    }
    //Get the index of the biggest element, return the element at that index in the coordinatesAndStops-vector.
    int index;
    if(searchForWorstCar == true && stopsCount.size() > 0)
        index = getIndexForSmallestValue(stopsCount);
    else if (searchForWorstCar == false && stopsCount.size() > 0)
        index = getIndexForBiggestValue(stopsCount);
    else
        index = 0;

    return coordinatesAndStops[index];
}


vector<string> dataAggregatorClass::getCoordinatesWithMostStoppage()
{
    EntityManager em;
    //Note! We do not use the standard converting method, because our query does not return all columns!
    vector<PositionEntity> positionsEntities = convert_to_positionsStops(em.getStopsPerCoordinate(this->startDate, this->endDate));
    vector<string> coordinatesAndStops;

    for(PositionEntity p : positionsEntities)
    {
        if(positionsEntities.size() > 0)
        {
            coordinatesAndStops.push_back
                    ("At coordinates " + to_string(p.get_rdx()) + ", "
                     + to_string(p.get_rdy()) + " cars were stopped " + to_string(p.get_speed()) + " times.");
        }
        else
            coordinatesAndStops.push_back("Error: No data found!");
    }
    return coordinatesAndStops;
}


/*********************************
 * CONNECTIONS
 * *******************************
 */

//GENERIFIED FOR USE IN BOTH CONNECTIONS AND EVENTS
//Average loss and gain of T in percentage


template <typename T> pair<double,double> dataAggregatorClass::getAverages(vector<T> listOfEntities)
{
    vector<bool> allTruePortValues;
    vector<bool> allFalsePortValues;

    string typeOfVector = typeid(listOfEntities[0]).name();
    typeOfVector.erase(typeOfVector.begin(), typeOfVector.begin() + 2);

    if(typeOfVector.compare("ConnectionEntity") == 0 || typeOfVector.compare("EventEntity") == 0)
    {
        for (T e : listOfEntities)
        {
            if (e.get_value() == true && listOfEntities.size() > 0)
                allTruePortValues.push_back(e.get_value());
            else if(e.get_value() == false && listOfEntities.size() > 0)
                allFalsePortValues.push_back(e.get_value());
            else
            {
                cout << "Empty list in dataAggregator::getAverages()" << endl;
                return make_pair(0.0, 0.0);
            }
        }
    }
    else
    {
        cout << "Not a valid entitytype." << endl;
        return make_pair(0.0, 0.0);
    }

    //fabs returns an absolute, non-rounded value (IE. 0.5463 instead of 0.)
    double averageUpTimePercentage = fabs((double) allTruePortValues.size() / (double) listOfEntities.size()) * 100;
    double averageDownTimePercentage = fabs((double) allFalsePortValues.size() / (double)listOfEntities.size()) * 100;

    return make_pair(averageUpTimePercentage, averageDownTimePercentage);
}

//GENERIFIED FOR USE IN BOTH CONNECTIONS AND EVENTS
//All downtimes for each car
vector<string> dataAggregatorClass::getCarsAndDowntimes(string typeOfCsv)
{
    if(typeOfCsv.compare("connections") == 0)
    {
        EntityManager em;
        //Note! We do not use the standard converting method, because our query does not return all columns!
        vector<ConnectionEntity> connectionEntities = convert_to_connectionsLite(em.getConnectionFailuresPerCar(this->startDate, this->endDate));
        vector<string> carsAndDownTimes;

        for(ConnectionEntity c : connectionEntities)
        {
            if(connectionEntities.size() > 0)
                //We get the Distinct unitIds and the amount of 0 values for each unitID. (see dbreader.h and EntityManager.h for more details)
                carsAndDownTimes.push_back("Car no. : " + c.get_unit_id() + " has lost connection " + to_string(c.get_countOfValue()) + " times.");
            else
                carsAndDownTimes.push_back("Error: No data found!");
        }
        return carsAndDownTimes;
    }
    else if(typeOfCsv.compare("events") == 0)
    {
        EntityManager em;
        //Note! We do not use the standard converting method, because our query does not return all columns!
        vector<EventEntity> eventEntities = convert_to_eventsLite(em.getIgnitionFailuresPerCar(this->startDate, this->endDate));
        vector<string> carsAndDownTimes;

        for(EventEntity e : eventEntities)
        {
            if(eventEntities.size() > 0)
                //We get the Distinct unitIds and the amount of 0 values for each unitID. (see dbreader.h and EntityManager.h for more details)
                carsAndDownTimes.push_back("Car no. : " + e.get_unit_id() + " has stopped " + to_string(e.get_countOfValue()) + " times.");
            else
                carsAndDownTimes.push_back("Error: No data found!");
        }
        return carsAndDownTimes;
    }
}

//GENERIFIED FOR USE IN BOTH CONNECTIONS AND EVENTS
//Car with biggest/smallest connection/ignition loss number
string dataAggregatorClass::getCarWithBestOrWorstDataLoss(bool searchForWorst, string typeOfCsv)
{
    vector<string> carsAndDownTimes;
    vector<int> valuesOnly;

    if(typeOfCsv.compare("connections") == 0)
    {
        EntityManager em;

        //Note! We do not use the standard converting method, because our query does not return all columns!
        vector<ConnectionEntity> connectionEntities = convert_to_connectionsLite(em.getConnectionFailuresPerCar(this->startDate, this->endDate));

        for(ConnectionEntity c : connectionEntities)
        {
            if(connectionEntities.size() > 0)
            {
                //We get the Distinct unitIds and the amount of 0 values for each unitID. (see dbreader.h and EntityManager.h for more details)
                carsAndDownTimes.push_back("Car no. : " + c.get_unit_id() + " has lost connection " + to_string(c.get_countOfValue()) + " times.");
                valuesOnly.push_back(c.get_countOfValue());
            }
            else
            {
                carsAndDownTimes.push_back("Error: No data found!");
                valuesOnly.push_back(0);
            }
        }
    }
    //Bit of duplication to make the code less complicated.
    else if(typeOfCsv.compare("events") == 0)
    {
        EntityManager em;

        //Note! We do not use the standard converting method, because our query does not return all columns!
        vector<EventEntity> eventEntities = convert_to_eventsLite(em.getIgnitionFailuresPerCar(this->startDate, this->endDate));

        for(EventEntity e : eventEntities)
        {
            if(eventEntities.size() > 0)
            {
                //We get the Distinct unitIds and the amount of 0 values for each unitID. (see dbreader.h and EntityManager.h for more details)
                carsAndDownTimes.push_back("Car no. : " + e.get_unit_id() + " has stopped " + to_string(e.get_countOfValue()) + " times.");
                valuesOnly.push_back(e.get_countOfValue());
            }
            else
            {
                carsAndDownTimes.push_back("Error: No data found!");
                valuesOnly.push_back(0);
            }
        }
    }
    else
    {
        cout << "Unknown CSV file." << endl;
    }

    int index;
    //Return the index in valuesOnly (which has the same length as carsAndDownTimes so it can be used directly)
    //For the biggest or smallest value.
    if(searchForWorst == true)
        //Measure the distance between the beginning of the array and the location of the biggest or smallest element.
        index = getIndexForBiggestValue(valuesOnly);
    else
        index = getIndexForSmallestValue(valuesOnly);
    return carsAndDownTimes[index];
}



#endif
