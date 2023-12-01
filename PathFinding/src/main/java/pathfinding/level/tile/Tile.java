package pathfinding.level.tile;

import pathfinding.algorithm.Node;

import java.awt.*;

public abstract class Tile {
    protected static final int TILE_SIZE = 50;
    protected static final int DOT_SIZE = 10;
    protected static final int FONT_SPACING = 13;
    public Node node = new Node();

    public abstract boolean isWalkable();

    public void paint(Graphics g) {
        int xOffset = node.coord.y() * TILE_SIZE;
        int yOffset = node.coord.x() * TILE_SIZE;

        g.setColor(node.color);
        g.fillRect(xOffset + TILE_SIZE - DOT_SIZE,
                yOffset + TILE_SIZE - DOT_SIZE,
                DOT_SIZE,
                DOT_SIZE);

        g.setColor(Color.BLACK);
        g.drawRect(xOffset,
                yOffset,
                TILE_SIZE,
                TILE_SIZE);
        g.drawRect(xOffset + TILE_SIZE - DOT_SIZE,
                yOffset + TILE_SIZE - DOT_SIZE,
                DOT_SIZE,
                DOT_SIZE);
        g.drawString("f=" + node.fCost, xOffset + 2, yOffset + FONT_SPACING);
        g.drawString("g=" + node.gCost, xOffset + 2, yOffset + 2 * FONT_SPACING);
        g.drawString("h=" + node.hCost, xOffset + 2, yOffset + 3 * FONT_SPACING);
    }
}