import de.javasoft.plaf.synthetica.SyntheticaBlueIceLookAndFeel;

import javax.swing.*;
import java.awt.*;
import java.text.ParseException;

/**
 * Created with IntelliJ IDEA.
 * User: dextor
 * Date: 7/30/13
 * Time: 9:05 PM
 * To change this template use File | Settings | File Templates.
 */
public class MainWindow extends JFrame {

    private final ShowCSPPanel showCSP;
    private GenerateCSPPanel generateCSP;

    private JMenuBar menuBar;
    private JMenu firstMenu;
    private JMenuItem createCSPMenuItem;

    public MainWindow() {
        setLayout(new BorderLayout());

        generateCSP = new GenerateCSPPanel(this);
        showCSP = new ShowCSPPanel(this);

        add(generateCSP, BorderLayout.CENTER);
        add(showCSP, BorderLayout.SOUTH);

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

    public void showCSP(String csp) {
        showCSP.setCSP(csp);
        pack();
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
