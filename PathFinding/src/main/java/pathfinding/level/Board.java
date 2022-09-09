package pathfinding.level;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class Board<T> {
    private List<List<T>> elements = new ArrayList<>();

    public void addRow(List<T> row) {
        elements.add(row);
    }

    public Optional<T> getTile(Coord coord) {
        try {
            return Optional.of(elements.get(coord.x()).get(coord.y()));
        }
        catch (IndexOutOfBoundsException ex) {
            return Optional.empty();
        }
    }

    public ArrayList<T> getNeighbours(Coord coord) {
        ArrayList<T> output = new ArrayList<>();
        for (int i = coord.x() - 1; i <= coord.x() + 1; ++i) {
            for (int j = coord.y() - 1; j <= coord.y() + 1; ++j) {
                if (i == coord.x() && j == coord.y())
                    continue;
                getTile(new Coord(i, j)).ifPresent(output::add);
            }
        }
        return output;
    }
}
