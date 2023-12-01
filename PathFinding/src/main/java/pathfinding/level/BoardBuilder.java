package pathfinding.level;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class BoardBuilder {
    public static TileBoard fromFile(String filename) {
        TileBoard board = new TileBoard();
        try {
            Files.lines(Path.of(filename))
                    .map(String::chars)
                    .map(CharTileFactory::map)
                    .forEach((row) -> board.addRow(row));
        } catch (IOException e) {
            e.printStackTrace();
        }
        return board;
    }
}
