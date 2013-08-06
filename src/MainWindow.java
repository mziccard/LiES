import de.javasoft.plaf.synthetica.SyntheticaAluOxideLookAndFeel;
import de.javasoft.plaf.synthetica.SyntheticaBlackStarLookAndFeel;
import de.javasoft.plaf.synthetica.SyntheticaBlueIceLookAndFeel;

import javax.swing.*;
import java.awt.*;
import java.text.ParseException;
import java.util.Random;

/**
 * Created with IntelliJ IDEA.
 * User: dextor
 * Date: 7/30/13
 * Time: 9:05 PM
 * To change this template use File | Settings | File Templates.
 */
public class MainWindow extends JFrame {

    private GenerateCSPPanel panel;

    private JMenuBar menuBar;
    private JMenu firstMenu;
    private JMenuItem createCSPMenuItem;

    public MainWindow() {
        setLayout(new BorderLayout());

        panel = new GenerateCSPPanel();
        add(panel, BorderLayout.CENTER);

        // initializing menus

        createCSPMenuItem = new JMenuItem("Create CSP");

        firstMenu = new JMenu();
        firstMenu.add(createCSPMenuItem);

        menuBar = new JMenuBar();
        menuBar.add(firstMenu);

        setJMenuBar(menuBar);

        pack();
        setLocationByPlatform(true);
        setResizable(false);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setVisible(true);
    }

    public static void main(String[] args) {

        // setting new theme
        try {
            UIManager.setLookAndFeel(new SyntheticaBlueIceLookAndFeel());
        } catch (UnsupportedLookAndFeelException e) {
            e.printStackTrace();
        } catch (ParseException e) {
            e.printStackTrace();
        }

        // initializing program
        new MainWindow();
    }

}
