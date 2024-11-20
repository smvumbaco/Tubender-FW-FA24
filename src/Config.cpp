#include "config.hpp"

using namespace std;

//constructor for config object includes initial tube length in inches
Config::Config(double initTubeLength) 
{
    tubeLength = initTubeLength;
}

// addNewBend adds a bend to the config file and subtracts it from the length
// @param newBendType(string) Must be "kick" or "offset"
// @param bendNum(int) the bend number. Max number is 30.
// @param newBendAngle(double) The angle of the new bend.
// @param newBendHeight(double) Height of new bend.
// @param newBendLength(double, optional) Length of new bend. Used in offset bends.
int Config::addNewBend(string newBendType, int bendNum, double newBendAngle, double newBendHeight, double newBendLength = 0.0) 
{
    if (tubeLength - newBendHeight - newBendLength < 0.0)
    {
        return -1;
    }
    else if (newBendType != "kick" && newBendType != "offset") 
    {
        return -1;
    }
    bendType[bendNum] = newBendType;
    bendAngles[bendNum] = newBendAngle;
    bendHeight[bendNum] = newBendHeight;
    tubeLength -= newBendHeight;

    if (newBendLength > 0.0)
    {
        bendLength[bendNum] = newBendLength;
        tubeLength -= newBendLength;
    }
    
    return 0;
}

void Config::removeBend(int bendNum) 
{
    bendType[bendNum] = "";
    bendAngles[bendNum] = 0.0;
    bendHeight[bendNum] = 0.0;
    bendLength[bendNum] = 0.0;
}

Config::~Config() 
{

}