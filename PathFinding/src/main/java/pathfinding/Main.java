package pathfinding;

import pathfinding.level.BoardBuilder;
import pathfinding.level.Coord;
import pathfinding.level.TileBoard;

import javax.swing.*;
import java.awt.*;

public class Main extends JFrame {
    int X_SIZE = 1024;
    int Y_SIZE = 768;
    TileBoard board;

    public Main() {
        super("A* Algorithm");

        setSize(X_SIZE, Y_SIZE);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        board = BoardBuilder.fromFile("test.txt");
        board.initialize(new Coord(1,12), new Coord(8, 10));
    }

    public void run() {
        this.setVisible(true);

        while (!board.isDone()) {
            board.findPath();
            this.repaint();
            try {
                Thread.sleep(500);
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        this.repaint();
        board.reconstructShortestPath();
        this.repaint();
    }

    public void paint(Graphics g) {
        g.setColor(Color.WHITE);
        g.fillRect(0, 0, X_SIZE, Y_SIZE);
        board.paint(g);
    }

    public static void main(String[] args) {
        Main main = new Main();
        main.setVisible(true);
        main.run();
    }
}
