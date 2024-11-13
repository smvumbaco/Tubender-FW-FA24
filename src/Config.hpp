#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <string>

using namespace std;
/*!
 *
 * \class Config
 * \brief This class contains parameters for bends and tubes.
 *
 * 
 * @param bendType: Type of the bend.
 * 
 * @param bendAngles: Array of bend angles.
 * 
 * @param tubeAdvancement: Advancement of the tube.
 * 
 * @param tubeLength Length of the tube.
 */
class Config {
    
    public:
    
        Config(double initTubeLength);

        string bendType[5];
        double bendAngles[5];
        double bendHeight[5];
        double bendLength[5];
        //TODO find the max number of angles
        double tubeAdv;
        double tubeLength;
        void addNewBend(string newBendType, int bendNum, double newBendAngle, double newBendHeight, double newBendLength = 0.0);
        void removeBend(int bendNum);
        void setBendAngle(double);

        ~Config();

};

#endif