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
 * @param bendType: Type of bends - "kick" or "offset".
 * 
 * @param bendAngles: Array of bend angles.
 * 
 * @param tubeAdvancement: Advancement of the tube before each bend.
 * 
 * @param tubeLength Length of the tube.
 */
class Config {
    
    public:
    
        Config(double initTubeLength);
        Config();
        //TODO: Confirm max number of bends
        string bendType[30];
        double bendAngles[30];
        double bendHeight[30];
        double bendLength[30];
        double tubeAdv[30];
        double tubeLength;
        int addNewBend(string newBendType, int bendNum, double newBendAngle, double newBendHeight, double newBendLength);
        void removeBend(int bendNum);

        ~Config();

};

#endif