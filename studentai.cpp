
#include "micromouseserver.h"
#include <string>
#include <queue>

using namespace std;

string path = "";
string lastPath = "";
string mode = "discover";
string pathDifferenceOfPaths = "";
string lastPathDifferenceOfPaths = "";
bool inReverse = false;
bool backtrackPartTwo = false;
int counter = 0;
int counter2 = 0;
queue <string> pathQueue;

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
    if(mode=="shortest path"){
        printUI("hi");
    }
    else if(path.size()>=4 && path.substr(path.size()-4)=="FRRR"){
        foundFinish();
        //for now
    }
    else if(mode=="discover"){
        findNeighbors();
        mode = "backtrack";
        path = lastPath;
        if(!pathQueue.empty()){
            lastPath = pathQueue.front();
            pathQueue.pop();
        }
    }
    else {
        if(!path.empty()){
            int i;
            for(i=0;i<(int)path.size();i++) {
                if(path[i]!=lastPath[i]) break;
            }
            if(i==(int)path.size()) inReverse = true;
        } else inReverse = true;
        backtrack();
    }
}


void microMouseServer::backtrack(){
    int i=0;
    if(inReverse){
        if(!path.empty()){
            for(i=0;i<(int)path.size();i++) {
                if(!(path[i]==lastPath[i])) break;
            }
        }
        if(path.empty() || (i==(int)path.size())){
            if(lastPath[lastPath.size()-1]=='F'){
                moveForward();
            } else if(lastPath[lastPath.size()-1]=='L'){
                turnLeft();
                moveForward();
            } else if(lastPath[lastPath.size()-1]=='R'){
                turnRight();
                moveForward();
            }
            mode = "discover";
            path = lastPath;
            inReverse = false;
        } else {

            for(i=0;i<(int)path.size();i++) {
                if(!(path[i]==lastPath[i])) break;
            }
            //pathDifferenceOfPaths = path.substr(i, path.size()-1-counter);
            pathDifferenceOfPaths = path.substr(i);          
            for(int j=0;j<counter;j++) {
                pathDifferenceOfPaths.pop_back();
            }
            reverse(pathDifferenceOfPaths.begin(), pathDifferenceOfPaths.end());
            //lastPathDifferenceOfPaths = lastPath.substr(i+counter2, lastPath.size()-1);
            lastPathDifferenceOfPaths = lastPath.substr(i+counter2);

            if(pathDifferenceOfPaths.empty()){
                if(lastPathDifferenceOfPaths.empty()){
                    path = lastPath;
                    mode = "discover";
                    inReverse = false;
                    backtrackPartTwo = false;
                    counter = 0;
                    counter2 = 0;
                }
                else if(backtrackPartTwo){
                    if(lastPathDifferenceOfPaths[0]=='F'){
                        moveForward();
                    } else if(lastPathDifferenceOfPaths[0]=='L'){
                        turnLeft();
                        moveForward();
                    } else if(lastPathDifferenceOfPaths[0]=='R'){
                        turnRight();
                        moveForward();
                    }
                    counter2++;
                } else{
                    if(lastPathDifferenceOfPaths[0]=='F'){
                        turnLeft();
                        turnLeft();
                        moveForward();
                        counter2++;
                        backtrackPartTwo = true;
                    } else if(lastPathDifferenceOfPaths[0]=='L'){
                        turnRight();
                        moveForward();
                        counter2++;
                        backtrackPartTwo = true;
                    } else if(lastPathDifferenceOfPaths[0]=='R'){
                        turnLeft();
                        moveForward();
                        counter2++;
                        backtrackPartTwo = true;
                    }
                }
            }
        else if(pathDifferenceOfPaths[0]=='F'){
            moveForward();
            counter++;
        }
        else if(pathDifferenceOfPaths[0]=='R'){
            moveForward();
            turnLeft();
            counter++;
        }
        else {
            moveForward();
            turnRight();
            counter++;
            }
        }
    } else {
        turnRight();
        turnRight();
        inReverse = true;
    }
}


void microMouseServer::findNeighbors(){
    string neighbors;
    if(!isWallLeft()) neighbors += 'L';
    if(!isWallForward()) neighbors += 'F';
    if(!isWallRight()) neighbors += 'R';
    /* optimize this and make it one loop */
    if(neighbors.size()==1){
        pathQueue.push((path + neighbors[0]));
    }
    else if(neighbors.size()==2){
        pathQueue.push((path + neighbors[0]));
        pathQueue.push((path + neighbors[1]));
    }
    else if(neighbors.size()==3){
        pathQueue.push((path + neighbors[0]));
        pathQueue.push((path + neighbors[1]));
        pathQueue.push((path + neighbors[2]));
    }
}
