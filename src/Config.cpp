#include "config.hpp"

using namespace std;

Config::Config(double initTubeLength) 
{
    tubeLength = initTubeLength;
}

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