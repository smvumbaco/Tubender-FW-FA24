#include "config.hpp"

using namespace std;

Config::Config(double initTubeLength) {
    //TODO should config be a big object for all possible bends?
    // or should there be a config for each bend?
    
}

void Config::addNewBend(string newBendType, int bendNum, double newBendAngle, double newBendHeight, double newBendLength) {
    bendType[bendNum] = newBendType;
    bendAngles[bendNum] = newBendAngle;
    bendHeight[bendNum] = newBendHeight;
    tubeLength -= newBendHeight;

    if (newBendLength > 0)
    {
        bendLength[bendNum] = newBendLength;
        tubeLength -= newBendLength;
    }
}

void Config::removeBend(int bendNum) {
    bendType[bendNum] = "";
    bendAngles[bendNum] = 0.0;
    bendHeight[bendNum] = 0.0;
    bendLength[bendNum] = 0.0;
}

Config::~Config() {

}