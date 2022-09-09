package pathfinding.level;

public interface Tile {
    default boolean isWalkable() {
        return false;
    }
}
