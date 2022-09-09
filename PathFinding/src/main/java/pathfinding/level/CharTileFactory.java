package pathfinding.level;

import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class CharTileFactory {
    public static final Map<String, Tile> tileMap = Map.of(
        "#", new WallTile(),
        ".", new FloorTile()
    );

    public static Tile mapSingle(String c) {
        return tileMap.get(c);
    }

    public static List<Tile> map(IntStream chars) {
        return chars
                .mapToObj(Character::toString)
                .map(CharTileFactory::mapSingle)
                .collect(Collectors.toList());
    }
}
