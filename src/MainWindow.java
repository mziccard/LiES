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

    private final CSPViewPanel showCSP;
    private final GenerateCSPPanel generateCSP;
    private final SolvingMethodChooserPanel methodPanel;
    private final CSPSolutionPanel showSolution;

    private JMenuBar menuBar;
    private JMenu firstMenu;
    private JMenuItem createCSPMenuItem;

    public enum SolverType {
        BACKTRACK(0),
        MC_BACKTRACK(1),
        AC_BACKTRACK(2),
        BRANCH_BOUND(3),
        AC_BRANCH_BOUND(4);

        int type;

        SolverType (int type) {
            this.type = type;
        }

        public int getValue() {
            return type;
        }
    }

    public MainWindow() {
        setLayout(new BorderLayout());

        generateCSP = new GenerateCSPPanel(this);
        showCSP = new CSPViewPanel(this);
        methodPanel = new SolvingMethodChooserPanel(this);
        showSolution = new CSPSolutionPanel(this);

        add(generateCSP, BorderLayout.NORTH);
        add(methodPanel, BorderLayout.CENTER);

        JPanel container = new JPanel();
        container.setLayout(new BorderLayout());
        container.add(showCSP, BorderLayout.WEST);
        container.add(showSolution, BorderLayout.EAST);

        add(container, BorderLayout.SOUTH);

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

    public void showSolution(String solution) {
        showSolution.displaySolution(solution);
        pack();
    }

    public void solve(String csp) {
        String solution = SolverWrapper.execute(csp);
        showSolution(solution);
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
