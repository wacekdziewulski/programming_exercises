package pathfinding.algorithm;

import pathfinding.level.Coord;

import java.awt.*;

public class Node {
    public Coord coord;
    public int fCost;
    public int gCost;
    public int hCost;
    public Color color = Color.WHITE;
    private boolean visited = false;

    public boolean wasVisited() {
        return visited;
    }

    public void setVisited() {
        visited = true;
        if (color == Color.WHITE) {
            color = Color.GREEN;
        }
    }

    public void updateCost(Coord start, Coord finish) {
        gCost = Distance.calculate(start, coord);
        hCost = Distance.calculate(coord, finish);
        fCost = gCost + hCost;
    }

    public int getgCost() {
        return gCost;
    }

    public int gethCost() {
        return hCost;
    }

    public int getfCost() {
        return fCost;
    }
}