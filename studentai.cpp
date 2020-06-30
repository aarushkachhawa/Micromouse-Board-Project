
#include "micromouseserver.h"
#include <string>

using namespace std;

string path = "";

void microMouseServer::studentAI()
{
/*
 * The following are the eight functions that you can call. Feel free to create your own fuctions as well.
 * Remember that any solution that calls moveForward more than once per call of studentAI() will have points deducted.
 *
 *The following functions return if there is a wall in their respective directions
 *bool isWallLeft();
 *bool isWallRight();
 *bool isWallForward();
 *
 *The following functions move the mouse. Move forward returns if the mouse was able to move forward and can be used for error checking
 *bool moveForward();
 *void turnLeft();
 *void turnRight();
 *
 * The following functions are called when you need to output something to the UI or when you have finished the maze
 * void foundFinish();
 * void printUI(const char *mesg);
*/

    // Follows the wall on the left side of the mouse around the maze

    if(path.length()>=7 && path.substr(path.length()-7)=="FRFRFRF"){
        foundFinish();
    }
    else if(!isWallLeft()){
        turnLeft();
        moveForward();
        path += "LF";
    }

    else if(!isWallForward()){
        moveForward();
        path += "F";
    }
    else {
        turnRight();
        path += "R";
    }
}
