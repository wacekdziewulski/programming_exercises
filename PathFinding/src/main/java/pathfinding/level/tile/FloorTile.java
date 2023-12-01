package pathfinding.level.tile;

public class FloorTile extends Tile {
    @Override
    public boolean isWalkable() {
        return true;
    }

    @Override
    public String toString() {
        return "Floor(" + node.toString() + ")";
    }
}
