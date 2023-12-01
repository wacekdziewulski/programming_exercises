package pathfinding.level.tile;

import java.awt.*;

public class WallTile extends Tile {
    @Override
    public String toString() {
        return "Wall";
    }

    @Override
    public boolean isWalkable() {
        return false;
    }

    @Override
    public void paint(Graphics g) {
        int xOffset = node.coord.y() * TILE_SIZE;
        int yOffset = node.coord.x() * TILE_SIZE;
        g.setColor(Color.DARK_GRAY);
        g.fillRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE);
    }
}
