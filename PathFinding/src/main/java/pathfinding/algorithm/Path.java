package pathfinding.algorithm;

import pathfinding.level.Coord;

import java.util.Comparator;
import java.util.PriorityQueue;

public class Path {
    public PriorityQueue<Node> queue = new PriorityQueue<>(100, Comparator.comparingInt(Node::getfCost));
    public Coord current;
}
