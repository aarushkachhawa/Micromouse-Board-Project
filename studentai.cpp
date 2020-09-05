
#include "micromouseserver.h"
#include <string>
#include <queue>
#include <tuple>
#include <set>

using namespace std;

string path = "";
string lastPath = "";
string mode = "discover";
string pathDifferenceOfPaths = "";
string lastPathDifferenceOfPaths = "";
string entirePath = "";
bool inReverse = false;
bool backtrackPartTwo = false;
int counter = {0};
int counter2 = {0};
int direction = {0};
queue <string> pathQueue;
tuple <int, int> Coordinate = make_tuple(0, 0);
set <tuple<int, int>> visitedCoordinates;

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

        if(counter==path.size()) foundFinish();
        else if(path[counter]=='F'){
            moveForward();
            counter++;

        } else if(path[counter]=='L'){
            turnLeft();
            moveForward();
            counter++;

        } else if(path[counter]=='R'){
            turnRight();
            moveForward();
            counter++;

        }

    }
    else if(entirePath.size()>=7 && entirePath.substr(entirePath.size()-7)=="FRRFLLL"){
        if(isWallLeft() && isWallRight()){
            mode = "shortest path";
            counter = 0;
        }
    }
    else if(mode=="discover"){
        findNeighbors();
        mode = "backtrack";
        path = lastPath;
        if(!pathQueue.empty()){
            lastPath = pathQueue.front();
            pathQueue.pop();
        }
        if(!path.empty()){
            int i;
            for(i=0;i<(int)path.size();i++) {
                if(path[i]!=lastPath[i]) break;
            }
            if(i==(int)path.size()) inReverse = true;
        } else inReverse = true;
        backtrack();
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
                updateCoordinate();
                entirePath += "F";
            } else if(lastPath[lastPath.size()-1]=='L'){
                turnLeft();
                direction -= 1;
                moveForward();
                updateCoordinate();
                entirePath += "L";
            } else if(lastPath[lastPath.size()-1]=='R'){
                turnRight();
                direction += 1;
                moveForward();
                updateCoordinate();
                entirePath += "R";
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
                        updateCoordinate();
                        entirePath += "F";
                    } else if(lastPathDifferenceOfPaths[0]=='L'){
                        turnLeft();
                        direction -= 1;
                        moveForward();
                        updateCoordinate();
                        entirePath += "L";
                    } else if(lastPathDifferenceOfPaths[0]=='R'){
                        turnRight();
                        direction += 1;
                        moveForward();
                        updateCoordinate();
                        entirePath += "R";
                    }
                    counter2++;
                } else{
                    if(lastPathDifferenceOfPaths[0]=='F'){
                        turnLeft();
                        turnLeft();
                        if(direction==1 || direction==-1) direction*=-1;
                        else if(direction==0) direction=2;
                        else if(direction==2 || direction==-2) direction=0;
                        else if(direction==3) direction=1;
                        else if(direction==-3) direction=-1;
                        moveForward();
                        updateCoordinate();
                        entirePath += "F";
                        counter2++;
                        backtrackPartTwo = true;
                    } else if(lastPathDifferenceOfPaths[0]=='L'){
                        turnRight();
                        direction += 1;
                        moveForward();
                        updateCoordinate();
                        entirePath += "R";
                        counter2++;
                        backtrackPartTwo = true;
                    } else if(lastPathDifferenceOfPaths[0]=='R'){
                        turnLeft();
                        direction -= 1;
                        moveForward();
                        entirePath += "L";
                        updateCoordinate();
                        counter2++;
                        backtrackPartTwo = true;
                    }
                }
            }
        else if(pathDifferenceOfPaths[0]=='F'){
            moveForward();
            updateCoordinate();
            entirePath += "F";
            counter++;
        }
        else if(pathDifferenceOfPaths[0]=='R'){
            moveForward();
            updateCoordinate();
            turnLeft();
            entirePath += "R";
            direction -= 1;
            counter++;
        }
        else {
            moveForward();
            updateCoordinate();
            turnRight();
            entirePath += "L";
            direction += 1;
            counter++;
            }
        }
    } else {
        turnRight();
        turnRight();
        if(direction==1 || direction==-1) direction*=-1;
        else if(direction==0) direction=2;
        else if(direction==2 || direction==-2) direction=0;
        else if(direction==3) direction=1;
        else if(direction==-3) direction=-1;
        inReverse = true;
    }
}


void microMouseServer::findNeighbors(){
    string neighbors;
    if(!isWallLeft()) neighbors += 'L';
    if(!isWallForward()) neighbors += 'F';
    if(!isWallRight()) neighbors += 'R';
    /* optimize this and make it one loop */
    if(neighbors.size()==1 && visitedCoordinates.count(Coordinate)==0){
        pathQueue.push((path + neighbors[0]));
    }
    else if(neighbors.size()==2 && visitedCoordinates.count(Coordinate)==0){
        pathQueue.push((path + neighbors[0]));
        pathQueue.push((path + neighbors[1]));
    }
    else if(neighbors.size()==3 && visitedCoordinates.count(Coordinate)==0){
        pathQueue.push((path + neighbors[0]));
        pathQueue.push((path + neighbors[1]));
        pathQueue.push((path + neighbors[2]));
    }
    visitedCoordinates.insert(Coordinate);
}

void microMouseServer::updateCoordinate(){
    if(direction == 3) direction = -1;
    else if(direction == -3) direction = 1;
    else if(direction == 4 || direction == -4) direction = 0;
    if(direction == 0) get<1>(Coordinate) += 1;
    else if(direction == 1) get<0>(Coordinate) += 1;
    else if(direction == 2) get<1>(Coordinate) -= 1;
    else if(direction == -1) get<0>(Coordinate) -= 1;
    else if(direction == -2) get<1>(Coordinate) -= 1;

}

