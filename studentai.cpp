
#include "micromouseserver.h"
#include <string>
#include <stack>
#include <set>
#include <tuple>

using namespace std;

int direction {0};
string path = "";
string lastPath = "";
string mode = "discover";
bool inReverse = false;
stack <string> pathStack;
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

    if(path.length()>=4 && path.substr(path.length()-4)=="FRRR"){
            foundFinish();
        }
    else if(mode=="discover"){
        if((isWallLeft() && isWallRight() && isWallForward()) || visitedCoordinates.count(Coordinate)==1){
            lastPath = pathStack.top();
            pathStack.pop();
            mode = "backtrack";
            backtrack();
        }
        else findNeighbors();
    }
    else backtrack();
}

void microMouseServer::move(char letter){
    if(letter=='F') {
        moveForward();
        path += "F";
        visitedCoordinates.insert(Coordinate);
        updateCoordinate();
    }
    else if(letter=='R') {
        turnRight();
        moveForward();
        path += "R";
        direction += 1;
        visitedCoordinates.insert(Coordinate);
        updateCoordinate();
    }
    else if(letter=='L'){
        turnLeft();
        moveForward();
        path += "L";
        direction -= 1;
        visitedCoordinates.insert(Coordinate);
        updateCoordinate();
    }
}

void microMouseServer::backtrack(){
    string differenceOfPaths = "";
    if(inReverse){
        for(int i=path.size()-1; i>=(int)lastPath.size()-1; i--){
            differenceOfPaths += path[i];
        }
        if(differenceOfPaths.empty()){
            if(lastPath[lastPath.size()-1]=='F'){
                turnLeft();
                turnLeft();
                if(direction==1 || direction==-1) direction*=-1;
                else if(direction==0) direction=2;
                else if(direction==2 || direction==-2) direction=0;
                else if(direction==3) direction=1;
                else if(direction==-3) direction=-1;
                moveForward();

            } else if(lastPath[lastPath.size()-1]=='L'){
                turnRight();
                moveForward();
                direction += 1;

            } else if(lastPath[lastPath.size()-1]=='R'){
                turnLeft();
                moveForward();
                direction -= 1;
            }
            updateCoordinate();
            path = lastPath;
            mode = "discover";
            inReverse = false;
        }
        else if(differenceOfPaths[0]=='F'){
            moveForward();
            updateCoordinate();
            path = path.substr(0, path.size()-1);
        }
        else if(differenceOfPaths[0]=='R'){
            moveForward();
            updateCoordinate();
            turnLeft();
            direction -= 1;
            path = path.substr(0, path.size()-1);
        }
        else {
            moveForward();
            updateCoordinate();
            turnRight();
            direction += 1;
            path = path.substr(0, path.size()-1);
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
    if(neighbors.size()==1){
        move(neighbors[0]);
    }
    else if(neighbors.size()==2 && !path.empty()){
        pathStack.push((path + neighbors[1]));
        move(neighbors[0]);
    }
    else if(neighbors.size()==3 && !path.empty()){
        pathStack.push((path + neighbors[2]));
        pathStack.push((path + neighbors[1]));
        move(neighbors[0]);
    }
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


