
#include "micromouseserver.h"
#include <string>
#include <stack>

using namespace std;

string path = "";
string lastPath = "";
string differenceOfPaths = "";
string mode = "discover";
bool inReverse = false;
stack<string> pathStack;

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

    if(path.length()>=7 && path.substr(path.length()-7)=="FRFRFRF"){
            foundFinish();
        }
    else if(mode=="discover"){
        if(!(isWallLeft() && isWallRight() && isWallForward())){
            lastPath = pathStack.top();
            mode = "backtrack";
            backtrack();
        }
    }
    else {
        backtrack();
    }
}


void microMouseServer::backtrack(){
    if(inReverse){
        char newPath = lastPath[lastPath.length()-1];
        //string pathCopy = path.substr(0);
        for(int i=path.length()-1; i>=lastPath.length()-1; i--){
            differenceOfPaths += path[i];
        }
        if(differenceOfPaths.length()==0){
            //move in direction of newPath
            mode = "discover";
        }
        else if(differenceOfPaths[0]=='F'){
            moveForward();
            path = path.substr(0, path.length()-1);
        }
        else if(differenceOfPaths[0]=='R'){
            turnLeft();
            moveForward();
            path = path.substr(0, path.length()-1);
        }
        else{
            turnRight();
            moveForward();
            path = path.substr(0, path.length()-1);
        }
    }
    else {
        turnLeft();
        turnLeft();
        inReverse = true;
    }

}
