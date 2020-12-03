#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <iterator>

using namespace std;

namespace bender {

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

enum TileType {
    NORTH,
    EAST,
    WEST,
    SOUTH,
    WALL,
    OBSTACLE,
    PLAYER,
    INVERTER,
    BEER,
    TELEPORT,
    EMPTY,
    EXIT
};

class DirectionMap {
public:

    static std::string directionToString(Direction direction) {
        static DirectionMap converter;
        return converter.directionMap[direction];
    }

private:
    DirectionMap() {
        directionMap = {
            { LEFT, "WEST" },
            { RIGHT, "EAST" },
            { UP, "NORTH" },
            { DOWN, "SOUTH" },
        };
    }

    std::map<Direction, std::string> directionMap;
};

class Position {
public:
    Position() : x(-1), y(-1) {}
    Position(int x, int y) : x(x), y(y) {}

    Position get() {
        return *this;
    }

    Position neighbour(Direction direction) const {
        switch (direction) {
            case LEFT:
                return Position(x-1, y);
            case RIGHT:
                return Position(x+1, y);
            case UP:
                return Position(x, y-1);
            case DOWN:
                return Position(x, y+1);
            default:
                return *this;
        }
    }

    const int X() const {
        return x;
    }

    const int Y() const {
        return y;
    }

    bool isValid() const {
        return (x > -1 && y > -1);
    }

	bool operator!= (const Position& rhs) const {
		return ((this->y != rhs.x) || (this->y != rhs.y));
	}

	bool operator== (const Position& rhs) const {
		return ((this->x == rhs.x) && (this->y == rhs.y));
	}

private:
    int x;
    int y;
};

class Player {
public:
    Player(const Position& initialPosition) : position(initialPosition), direction(DOWN) {
        directionPriorities = { DOWN, RIGHT, UP, LEFT };
    }

    void move() {
        position = position.neighbour(direction);
		performedMoves.push_back(direction);
    }

	void teleport(const Position& teleportedPosition) {
		position = teleportedPosition;
	}

    void changeDirection(Direction newDirection) {
        direction = newDirection;
    }

    const Position& getPosition() const {
        return position;
    }

    const Direction& getDirection() const {
        return direction;
    }

    const std::vector<Direction>& getDirectionPriorities() const {
        return directionPriorities;
    }

    void invertDirectionPriorities() {
        std::reverse(directionPriorities.begin(), directionPriorities.end());
    }

    void switchBreakerMode() {
        breakerMode = !breakerMode;
    }

    bool isBreakerMode() const {
        return breakerMode;
    }

	const std::vector<Direction> getListOfPerformedMoves() {
		return performedMoves;
	}

    friend std::ostream& operator<< (std::ostream& os, const Player& player) {
        os << "Player: x=" << player.position.X() << " | y=" << player.position.Y() << " | direction=" << DirectionMap::directionToString(player.direction) << "\n";
        return os;
    }

private:
    bool breakerMode;
    Position position;
    Direction direction;
    std::vector<Direction> directionPriorities;
	std::vector<Direction> performedMoves;
};

class Level {
public:

    Level(std::istream& input) {
        readLevelFromStream(input);
        tileConversionTable = {
            {'N', NORTH },
            {'S', SOUTH },
            {'E', EAST },
            {'W', WEST },
            {'X', OBSTACLE },
            {'#', WALL },
            {'@', PLAYER },
            {'I', INVERTER },
            {'B', BEER },
            {'T', TELEPORT },
            {' ', EMPTY },
            {'$', EXIT },
        };
		analyzeLevel();
    }

    TileType getTile(const Position& position) {
        checkPositionValidity(position);
        std::string& line = levelMap[position.Y()];
        const char tile = line[position.X()];
        return tileConversionTable[tile];
    }

	const Position& getPlayerPosition() {
		return initialPlayerPosition;
	}

	void analyzeLevel() {
        int x = 0, y = 0;
        for (const std::string& line : levelMap) {
            for (const char tile : line) {
                if (tileConversionTable[tile] == PLAYER) {
                    initialPlayerPosition = Position(x, y);
                }
				else if (tileConversionTable[tile] == TELEPORT) {
					teleports.push_back(Position(x, y));
				}
                ++x;
            }
            x = 0;
            ++y;
        }
    }

	const Position& findTeleportExitPosition(const Position& teleportEntrance) {
		auto exitTeleporterPosition = std::find_if_not(teleports.begin(), teleports.end(), 
			[&](const Position& teleportPosition) -> bool { return teleportPosition == teleportEntrance; });
		return *exitTeleporterPosition;
	}

    void removeTile(const Position& position) {
        checkPositionValidity(position);
        std::string& line = levelMap[position.Y()];
        line[position.X()] = ' ';
    }

    friend std::ostream& operator<< (std::ostream& os, const Level& level) {
        os << "Level: " << "\n";
        for (const auto& line : level.levelMap) {
            os << "       " << line << "\n";
        }
        return os;
    }

private:

    void checkPositionValidity(const Position& position) {
        if (outOfBounds(position)) {
            throw std::logic_error("Position out of level bounds!");
        }
    }

    void readLevelFromStream(std::istream& input) {
        input >> height >> width;
        input.ignore();
        for (int i = 0; i < height; ++i) {
            string row;
            getline(input, row);
            levelMap.push_back(row);
        }
    }

    bool outOfBounds(const Position& position) {
        return (position.X() < 0 || position.Y() < 0 || position.X() > width || position.Y() > height);
    }

    int width;
    int height;
    std::vector<std::string> levelMap;
    std::map<const char, TileType> tileConversionTable;
	Position initialPlayerPosition;
	std::vector<Position> teleports;
};

class Game {
public:
    typedef std::unique_ptr<Player> PlayerPtr;
    typedef std::unique_ptr<Level> LevelPtr;

    Game(std::istream& input) : input(input), step(0), success(false) {
        level = LevelPtr(new Level(input));
        player = PlayerPtr(new Player(level->getPlayerPosition()));
        level->removeTile(player->getPosition());
    }

    friend std::ostream& operator<< (std::ostream& os, const Game& game) {
        os << "============= Step " << game.step << " =============\n";
        os << *game.level
           << *game.player;
        return os;
    }

    void play() {
        while (step < 1000 && !success) {
            cerr << *this << endl;
            advanceOneStep();
        }

		if (success) {
			outputAllPlayerMoves(std::cout);
		}
		else {
			std::cout << "LOOP\n";
		}
    }

	void outputAllPlayerMoves(std::ostream& stream) {
		const auto& moves = player->getListOfPerformedMoves();
		std::transform(moves.begin(), moves.end(), std::ostream_iterator<std::string>(stream, "\n"), DirectionMap::directionToString);
	}

    void advanceOneStep() {
        ++step;
        
        if (!tryRegularMove()) {
            tryAlternativeMoves();
        }
    }

    bool tryRegularMove() {
        handleCurrentTile();
        if (success) {
            return true;
        }
        return tryMoving(player->getDirection());
    }

    bool tryAlternativeMoves() {
        for (Direction direction : player->getDirectionPriorities()) {
            if (tryMoving(direction)) {
                return true;
            }
        }
        return false;
    }

    bool tryMoving(Direction direction) {
        TileType nextTile = level->getTile(player->getPosition().neighbour(direction));

        if (canMoveToNextTile(nextTile)) {
            player->changeDirection(direction);
            player->move();
            return true;
        }
        return false;
    }

    void handleCurrentTile() {
        Position currentPosition = player->getPosition();
        TileType currentTile = level->getTile(currentPosition);
        handleTile(currentTile, currentPosition);
    }

    bool canMoveToNextTile(const TileType tile) {
        return isTileWalkable(tile);
    }

    void handleTile(TileType tile, const Position& position) {
        switch (tile) {
            case NORTH:
                player->changeDirection(UP);
                break;
            case WEST:
                player->changeDirection(LEFT);
                break;
            case EAST:
                player->changeDirection(RIGHT);
                break;
            case SOUTH:
                player->changeDirection(DOWN);
                break;
            case BEER:
                player->switchBreakerMode();
                break;
            case OBSTACLE:
                if (player->isBreakerMode())
                    level->removeTile(position);
                break;
            case INVERTER:
                player->invertDirectionPriorities();
                break;
			case TELEPORT: {
				const Position& teleportExitPosition = level->findTeleportExitPosition(player->getPosition());
				player->teleport(teleportExitPosition);
				break;
			}
            case EXIT:
                success = true;
                break;
        }
    }

private:
    bool isTileWalkable(const TileType tile) {
        if (tile != WALL &&
            (tile != OBSTACLE || player->isBreakerMode())) {
            return true;
        }
        return false;
    }

    std::istream& input;
    PlayerPtr player;
    LevelPtr level;
    unsigned short step;
    bool success;
};

} // namespace bender

int main()
{
    bender::Game game(std::cin);

    game.play();

    return 0;
}
