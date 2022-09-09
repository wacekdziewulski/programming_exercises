package pathfinding;

import pathfinding.level.Board;
import pathfinding.level.BoardBuilder;
import pathfinding.level.Coord;
import pathfinding.level.Tile;

public class Main {

    public static void main(String[] args) {
        Board<Tile> board = BoardBuilder.fromFile("test.txt");
        System.out.println(board.getNeighbours(new Coord(0,0)));
    }
}
