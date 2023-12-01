package pathfinding.level;

import pathfinding.level.tile.FloorTile;
import pathfinding.level.tile.Tile;
import pathfinding.level.tile.WallTile;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class CharTileFactory {
    public static Tile mapSingle(String c) {
        switch (c) {
            case "#": return new WallTile();
            case ".": return new FloorTile();
            default: throw new UnsupportedOperationException();
        }
    }

    public static List<Tile> map(IntStream chars) {
        return chars
                .mapToObj(Character::toString)
                .map(CharTileFactory::mapSingle)
                .collect(Collectors.toList());
    }
}
