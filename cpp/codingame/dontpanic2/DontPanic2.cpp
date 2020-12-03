#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>
#include <memory>
#include <stdexcept>

using namespace std;

/**
* Auto-generated code below aims at helping you parse
* the standard input according to the problem statement.
**/

namespace DontPanic {
    enum Direction {
        LEFT,
        RIGHT,
        NONE
    };

    Direction parseDirection(const std::string& directionString) {
        if (directionString == "LEFT") {
            return LEFT;
        }
        else if (directionString == "RIGHT") {
            return RIGHT;
        }
        else {
            return NONE;
        }
    }

    struct Location {
        constexpr static const int INVALID = -1;
        constexpr static const int DEFAULT = 0;

        Location(int floor, int position) : floor(floor), position(position) {}

        bool isValid() const {
            return ((position != INVALID) &&
                    (floor    != INVALID));
        }

		bool isGroundFloor() const {
			return floor == 0;
		}

        bool isSameFloor(const Location& target) const {
            return floor == target.floor;
        }

        static const Location& Invalid() {
            static const Location Invalid(INVALID, INVALID);
            return Invalid;
        }

		bool operator< (const Location& rhs) const {
			return (floor < rhs.floor || (floor == rhs.floor && position < rhs.position));
		}

        int floor;
        int position;
    };

    struct Blockers {
        void addBlocker(const Location& location) {
            if (isNoBlockerOnFloor(location)) {
                blockers.push_back(location);
            }
        }

        const Location& getBlockerLocation(const Location& location) const {
            auto blockersOnFloorIterator = std::find_if(blockers.begin(), blockers.end(), [&] (const Location& current) -> bool {
                return current.isSameFloor(location);
            });
            if (blockersOnFloorIterator == blockers.end()) {
                return Location::Invalid();
            }
            else {
                return *blockersOnFloorIterator;
            }
        }

        bool isNoBlockerOnFloor(const Location& location) const {
            return !getBlockerLocation(location).isValid();
        }

    private:
        std::vector<Location> blockers;
    };

	struct Path {
		Path() : totalDistance(0) {}

		Path(const Path& path) {
			std::copy(path.steps.begin(), path.steps.end(), std::back_inserter(steps));
			totalDistance = path.totalDistance;
		}

		void addStep(const Location& nextLocation) {
			if (!steps.empty()) {
				const Location& lastLocation = steps.back();
				totalDistance += std::abs(lastLocation.position - nextLocation.position);
			}
			steps.push_back(nextLocation);
		}

		const unsigned int getTotalDistance() const {
			return totalDistance;
		}

		const size_t getNumberOfStepsInPath() {
			return steps.size();
		}
	private:
		std::vector<Location> steps;
		unsigned int totalDistance;
	};

	typedef std::shared_ptr<Path> PathPtr;

    struct Elevators {
        Elevators(int maxFloor) : maxFloor(maxFloor) {}

        void addElevator(const Location& elevatorLocation) {
            elevatorsByFloor[elevatorLocation.floor].push_back(elevatorLocation.position);
        }

        const Location& getClosestToLocation(const Location& location) const {
            const std::vector<Location>& elevatorsOnFloor = getElevatorsOnFloor(location.floor);
            if (elevatorsOnFloor.empty()) {
                return Location::Invalid();
            }

            auto closestElevatorIter = std::min_element(elevatorsOnFloor.begin(), elevatorsOnFloor.end(), [=] (const Location& lhs, const Location& rhs)
            {
                return std::abs(lhs.position - location.position) < std::abs(lhs.position - location.position);
            });

            return *closestElevatorIter;
        }

        const std::vector<Location>& getElevatorsOnFloor(int floor) const {
            static std::vector<Location> elevatorsOnFloor;
            elevatorsOnFloor.clear();

            auto elevatorsOnFloorIterator = elevatorsByFloor.find(floor);
            if (elevatorsOnFloorIterator != elevatorsByFloor.end()) {
                for (const auto elevatorPosition : elevatorsOnFloorIterator->second) {
                    elevatorsOnFloor.push_back(Location(floor, elevatorPosition));
                }
            }
            return elevatorsOnFloor;
        }

        bool isNoElevatorOnFloor(int floor) const {
            return getElevatorsOnFloor(floor).empty();
        }

        std::vector<int> getFloorsWithMissingElevators() const {
            std::vector<int> floorsWithMissingElevators;
            for (int currentFloor = 0; currentFloor < maxFloor; ++currentFloor) {
                if (isNoElevatorOnFloor(currentFloor)) {
                    floorsWithMissingElevators.push_back(currentFloor);
                }
            }
            return floorsWithMissingElevators;
        }

    private:
        std::map<int, std::vector<int>> elevatorsByFloor;
        int maxFloor;
    };

	struct Pathfinding {
		typedef std::pair<Location, std::vector<Location>> LocationNode;
		typedef std::map<Location, std::vector<Location>> LocationTree;

		void buildElevatorTreeByFloor(const std::vector<Location>& elevatorsOnCurrentFloor,
									  const std::vector<Location>& elevatorsOnNextFloor)
		{
			if (!elevatorsOnCurrentFloor.empty() && elevatorsOnCurrentFloor.front().isGroundFloor()) {
				groundElevators = elevatorsOnCurrentFloor;
			}
			for (auto& elevatorOnCurrentFloor : elevatorsOnCurrentFloor) {
				for (auto& elevatorOnNextFloor : elevatorsOnNextFloor) {
					treeOfElevatorsByFloor[elevatorOnCurrentFloor].push_back(elevatorOnNextFloor);
				}
			}
		}
		
		const PathPtr findShortestPath() {
			if (paths.empty()) {
				createPaths();
			}
			auto pathIterator = std::min_element(paths.begin(), paths.end(), [](const PathPtr lhs, const PathPtr rhs) -> bool { return lhs->getTotalDistance() < rhs->getTotalDistance(); });
			return *pathIterator;
		}
		
	private:
		
		void breadthFirstSearch(const std::vector<Location>& nodeChildren, Path path) {
			for (auto& elevatorNode : nodeChildren) {
				path.addStep(elevatorNode);
				breadthFirstSearch(treeOfElevatorsByFloor[elevatorNode], path);
			}
		}

		void createPaths() {
			for (auto& groundElevator : groundElevators) {
				Path newPath;
				newPath.addStep(groundElevator);
				breadthFirstSearch(treeOfElevatorsByFloor[groundElevator], newPath);
			}
		}

		LocationTree treeOfElevatorsByFloor;
		std::vector<Location> groundElevators;
		std::vector<Path> paths;
	};

    struct Clone {

        Clone(std::istream& is) : input(is), location(Location::Invalid()), direction(RIGHT) {}

        void updateLocationAndDirection() {
            // TODO: no input validation here - trusting the application, but should add it
            std::string directionStr;
            input >> location.floor >> location.position >> directionStr; input.ignore();
            updateDirection(directionStr);
        }

        const Location& getLocation() const {
            return location;
        }

        const Direction& getDirection() const {
            return direction;
        }

        bool isGoingInTheWrongDirection(const Location& targetLocation) {
            if (!targetLocation.isValid()) {
                return false;
            }
            if (direction == LEFT && location.position < targetLocation.position) {
                return true;
            }
            // cloneDirection == RIGHT
            else if (direction == RIGHT && location.position > targetLocation.position) {
                return true;
            }

            return false;
        }

    private:
        Location location;
        Direction direction;

        void updateDirection(const std::string& directionStr) {
            try {
                direction = parseDirection(directionStr);
            }
            catch (const std::invalid_argument&) {
                throw;
            }
        }

        std::istream& input;
    };

} // namespace DontPanic

int main()
{
    using namespace DontPanic;

    int nbFloors; // number of floors
    int width; // width of the area
    int nbRounds; // maximum number of rounds
    int exitFloor; // floor on which the exit is found
    int exitPos; // position of the exit on its floor
    int nbTotalClones; // number of generated clones
    int nbAdditionalElevators; // number of additional elevators that you can build
    int nbElevators; // number of elevators
    cin >> nbFloors >> width >> nbRounds >> exitFloor >> exitPos >> nbTotalClones >> nbAdditionalElevators >> nbElevators; cin.ignore();
    DontPanic::Elevators elevators(nbFloors-1);
    DontPanic::Blockers blockers;
    DontPanic::Clone clone(cin);
    const DontPanic::Location exitLocation(exitFloor, exitPos);

    for (int i = 0; i < nbElevators; i++) {
        int elevatorFloor; // floor on which this elevator is found
        int elevatorPos; // position of the elevator on its floor
        cin >> elevatorFloor >> elevatorPos; cin.ignore();
        Location elevatorLocation(elevatorFloor, elevatorPos);
        elevators.addElevator(elevatorLocation);
    }

	DontPanic::Pathfinding pathFinding;
	for (int floor = 0; floor < nbFloors-1; ++floor) {
		pathFinding.buildElevatorTreeByFloor(elevators.getElevatorsOnFloor(floor), elevators.getElevatorsOnFloor(floor+1));
	}
	
	const PathPtr shortestPath = pathFinding.findShortestPath();

    // game loop
    while (--nbRounds > 0) {
        clone.updateLocationAndDirection();

        const Location& targetLocation = clone.getLocation().isSameFloor(exitLocation) ?
                                         exitLocation :
                                         elevators.getClosestToLocation(clone.getLocation());

        if (!clone.getLocation().isValid()) {
            cout << "WAIT" << endl; // action: WAIT or BLOCK
        }
        else if (clone.isGoingInTheWrongDirection(targetLocation) && blockers.isNoBlockerOnFloor(clone.getLocation())) {
            blockers.addBlocker(clone.getLocation());
            cout << "BLOCK" << endl;
        }
        else if (!clone.getLocation().isSameFloor(exitLocation) && elevators.isNoElevatorOnFloor(clone.getLocation().floor)) {
            elevators.addElevator(clone.getLocation());
            cout << "ELEVATOR" << endl;
        }
        else {
            cout << "WAIT" << endl; // action: WAIT or BLOCK
        }
    }
}
