package pathfinding.level;

public class WallTile implements Tile {
    @Override
    public String toString() {
        return "Wall";
    }

    @Override
    public boolean isWalkable() {
        return false;
    }
}
