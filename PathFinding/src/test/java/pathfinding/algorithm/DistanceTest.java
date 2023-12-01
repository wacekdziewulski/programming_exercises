package pathfinding.algorithm;

import org.junit.jupiter.api.Test;
import pathfinding.level.Coord;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static pathfinding.algorithm.Distance.DIAGONAL_DISTANCE_CONSTANT;
import static pathfinding.algorithm.Distance.LINEAR_DISTANCE_CONSTANT;

class DistanceTest {
    @Test
    void testSameCoordinates() {
        assertEquals(0, Distance.calculate(new Coord(5, 2), new Coord(5, 2)));
        assertEquals(0, Distance.calculate(new Coord(0, 0), new Coord(0, 0)));
        assertEquals(0, Distance.calculate(new Coord(-2, -3), new Coord(-2, -3)));
    }

    @Test
    void testOnlyLinear() {
        assertEquals(3 * LINEAR_DISTANCE_CONSTANT, Distance.calculate(new Coord(0, 3), new Coord(3, 3)));
        assertEquals(5 * LINEAR_DISTANCE_CONSTANT, Distance.calculate(new Coord(0, 0), new Coord(0, 5)));
        assertEquals(2 * LINEAR_DISTANCE_CONSTANT, Distance.calculate(new Coord(2, 0), new Coord(0, 0)));
        assertEquals(3 * LINEAR_DISTANCE_CONSTANT, Distance.calculate(new Coord(-5, 0), new Coord(-2, 0)));
        assertEquals(4 * LINEAR_DISTANCE_CONSTANT, Distance.calculate(new Coord(2, -4), new Coord(2, 0)));
    }

    @Test
    void testOnlyDiagonal() {
        assertEquals(3 * DIAGONAL_DISTANCE_CONSTANT, Distance.calculate(new Coord(0, 0), new Coord(3, 3)));
        assertEquals(5 * DIAGONAL_DISTANCE_CONSTANT, Distance.calculate(new Coord(5, 2), new Coord(10, 7)));
        assertEquals(7 * DIAGONAL_DISTANCE_CONSTANT, Distance.calculate(new Coord(-10, -5), new Coord(-3, 2)));
        assertEquals(5 * DIAGONAL_DISTANCE_CONSTANT, Distance.calculate(new Coord(2, 3), new Coord(7, -2)));
        assertEquals(6 * DIAGONAL_DISTANCE_CONSTANT, Distance.calculate(new Coord(-4, 2), new Coord(2, -4)));
    }

    @Test
    void testDiagonalPlusLinear() {
        assertEquals(2 * LINEAR_DISTANCE_CONSTANT + 3 * DIAGONAL_DISTANCE_CONSTANT, Distance.calculate(new Coord(0, 0), new Coord(3, 5)));
        assertEquals(5 * LINEAR_DISTANCE_CONSTANT + 10 * DIAGONAL_DISTANCE_CONSTANT, Distance.calculate(new Coord(4, 2), new Coord(-6, -13)));
        assertEquals(3 * LINEAR_DISTANCE_CONSTANT + 1 * DIAGONAL_DISTANCE_CONSTANT, Distance.calculate(new Coord(-1, 1), new Coord(3, 2)));
        assertEquals(4 * LINEAR_DISTANCE_CONSTANT + 4 * DIAGONAL_DISTANCE_CONSTANT, Distance.calculate(new Coord(-6, -2), new Coord(2, 2)));
    }
}