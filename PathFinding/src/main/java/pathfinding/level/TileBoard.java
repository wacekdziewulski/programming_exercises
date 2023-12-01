package pathfinding.level;

import pathfinding.algorithm.Path;
import pathfinding.level.tile.Tile;

import java.awt.*;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class TileBoard extends Board<Tile> {
    private Coord start;
    private Coord finish;
    private Path path = new Path();

    public void initialize(Coord start, Coord finish) {
        this.start = start;
        this.finish = finish;
        this.path.current = this.start;
        this.getTile(start).get().node.color = Color.CYAN;
        this.getTile(finish).get().node.color = Color.BLUE;
        decorateWithCoordinates();
    }

    public boolean isDone() {
        return this.path.current.equals(this.finish);
    }

    public void findPath() {
        for (Tile t : getNeighbours(this.path.current)) {
            if (t.node.wasVisited() || !t.isWalkable()) {
                continue;
            }
            t.node.updateCost(start, finish);
            if (!this.path.queue.contains(t.node)) {
                this.path.queue.add(t.node);
            }
        }
        getTile(this.path.current).get().node.setVisited();
        this.path.current = this.path.queue.poll().coord;
    }

    public void reconstructShortestPath() {
        Coord current = finish;
        List<Coord> shortestPath = new ArrayList<>();
        while (!current.equals(start)) {
            shortestPath.add(current);
            getTile(current).get().node.color = Color.MAGENTA;
            current = getNeighbours(current)
                    .stream()
                    .filter((tile -> tile.node.wasVisited()))
                    .filter((o) -> !shortestPath.contains(o.node.coord))
                    .min(Comparator.comparing((tile)->tile.node.getfCost()))
                    .get().node.coord;
            System.out.println(current);
        }
    }

    private void decorateWithCoordinates() {
        for (int i = 0; i < elements.size(); ++i) {
            for (int j = 0; j < elements.get(0).size(); j++) {
                Coord current = new Coord(i, j);
                getTile(current).ifPresent(tile -> { tile.node.coord = current; });
            }
        }
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (List<Tile> line : elements) {
            sb.append(line);
            sb.append("\n");
        }
        return sb.toString();
    }

    public void paint(Graphics g) {
        for(List<Tile> line : elements) {
            for(Tile element : line) {
                element.paint(g);
            }
        }
    }
}
