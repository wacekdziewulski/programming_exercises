package pathfinding.algorithm;

import pathfinding.level.Coord;

public class Distance {
    public static final int DIAGONAL_DISTANCE_CONSTANT = 14;
    public static final int LINEAR_DISTANCE_CONSTANT = 10;

    public static int calculate(Coord from, Coord to) {
        int dist_x = Math.abs(from.x() - to.x());
        int dist_y = Math.abs(from.y() - to.y());
        int diagonal = Math.min(dist_x, dist_y);
        int linear = Math.abs(Math.max(dist_x, dist_y) - diagonal);
        return linear * LINEAR_DISTANCE_CONSTANT + diagonal * DIAGONAL_DISTANCE_CONSTANT;
    }
}