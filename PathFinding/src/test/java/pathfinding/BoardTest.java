package pathfinding;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import pathfinding.level.Board;
import pathfinding.level.Coord;

import java.util.List;

import static org.assertj.core.api.Assertions.assertThat;

class BoardTest {
    Board<Integer> testBoard;

    @BeforeEach
    void setUp() {
        testBoard = new Board<>();
    }

    @Test
    public void testIncorrectIndex() {
        assertThat(testBoard.getTile(new Coord(-1,0))).isEmpty();
        assertThat(testBoard.getTile(new Coord(0,-1))).isEmpty();
    }

    @Test
    public void testEmptyBoard() {
        assertThat(testBoard.getTile(new Coord(0,0))).isEmpty();
    }

    @Test
    void testOneElementBoard() {
        testBoard.addRow(List.of(1));
        assertThat(testBoard.getTile(new Coord(0, 0))).contains(1);
        assertThat(testBoard.getNeighbours(new Coord(0, 0))).isEmpty();
    }

    @Test
    void testTwoByTwoBoard() {
        testBoard.addRow(List.of(1,2));
        testBoard.addRow(List.of(3,4));
        assertThat(testBoard.getTile(new Coord(0, 1))).contains(2);
        assertThat(testBoard.getTile(new Coord(1, 0))).contains(3);
        assertThat(testBoard.getNeighbours(new Coord(1, 1))).containsExactly(1, 2, 3);
    }

    @Test
    void testThreeByThreeBoard() {
        testBoard.addRow(List.of(1,2,3));
        testBoard.addRow(List.of(4,5,6));
        testBoard.addRow(List.of(7,8,9));

        assertThat(testBoard.getTile(new Coord(1, 0))).contains(4);
        assertThat(testBoard.getTile(new Coord(2, 0))).contains(7);
        assertThat(testBoard.getTile(new Coord(1, 2))).contains(6);
        assertThat(testBoard.getNeighbours(new Coord(1, 1))).containsExactly(1, 2, 3, 4, 6, 7, 8, 9);
        assertThat(testBoard.getNeighbours(new Coord(0, 2))).containsExactly(2, 5, 6);
    }
}