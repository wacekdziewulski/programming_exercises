package pathfinding.level;

public class FloorTile implements Tile {
    @Override
    public boolean isWalkable() {
        return true;
    }

    @Override
    public String toString() {
        return "Floor";
    }
}
