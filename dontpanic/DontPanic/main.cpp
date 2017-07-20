#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

typedef std::map<int, std::vector<int> > LevelMap;
typedef std::pair<int, int> ElevatorPosition; // <floor, position>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    LevelMap levelMap;
    int nbFloors; // number of floors
    int width; // width of the area
    int nbRounds; // maximum number of rounds
    int exitFloor; // floor on which the exit is found
    int exitPos; // position of the exit on its floor
    int nbTotalClones; // number of generated clones
    int nbAdditionalElevators; // number of additional elevators that you can build
    int nbElevators; // number of elevators
    cin >> nbFloors >> width >> nbRounds >> exitFloor >> exitPos >> nbTotalClones >> nbAdditionalElevators >> nbElevators; cin.ignore();
    for (int i = 0; i < nbElevators; i++) {
        int elevatorFloor; // floor on which this elevator is found
        int elevatorPos; // position of the elevator on its floor
        cin >> elevatorFloor >> elevatorPos; cin.ignore();
        levelMap[elevatorFloor].push_back(elevatorPos);
    }

    const std::vector<ElevatorPosition>& elevatorPositionsToCreate = getMissingFloorPositions(levelMap, nbFloors);
    for (auto& elevatorPos : elevatorPositionsToCreate) {
    	cerr << "Missing Elevator: " << elevatorPos.first;
    	cerr << "position" << elevator.second;
    	cerr << std::endl;
    }

    // game loop
    while (1) {
        int cloneFloor; // floor of the leading clone
        int clonePos; // position of the leading clone on its floor
        string direction; // direction of the leading clone: LEFT or RIGHT
        cin >> cloneFloor >> clonePos >> direction; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << "WAIT" << endl; // action: WAIT or BLOCK
    }
}

const std::vector<ElevatorPosition> getMissingFloorPositions(const LevelMap& levelMap, int floors, int initialPosition) {
    std::vector<ElevatorPosition> missingElevatorPositions;
    std::vector<int>& missingElevatorLevels = findFloorsWithouthElevators(levelMap, floors);
    for (auto& position : missingElevatorPositions) {
    	if (position == 0) {
    		missingElevatorPositions.push_back(std::make_pair(0, -1));
    	}
    	else {
    		missingElevatorPositions.push_back(levelMap[position-1].second[0]);
    	}
    }
}

std::vector<int> findFloorsWithoutElevators(const LevelMap& levelMap, int floors) {
    std::vector<int> floorsWithoutElevators
    for (int i = 0; i < floors; ++i) {
    	if (levelMap.find(i) == levelMap.end()) {
    		floorsWithoutElevators.push_back(i);
    	}
    }
   	return floorsWithoutElevators;
}