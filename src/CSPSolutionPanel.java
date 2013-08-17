import javax.swing.*;
import java.awt.*;

/**
 * Created with IntelliJ IDEA.
 * User: dextor
 * Date: 8/16/13
 * Time: 2:58 PM
 * To change this template use File | Settings | File Templates.
 */
public class CSPSolutionPanel extends JPanel {

    private final MainWindow parent;

    private JTextArea cspSolutionArea;
    private final JScrollPane scroll;

    public CSPSolutionPanel(MainWindow parent) {
        this.parent = parent;

        setLayout(new GridBagLayout());

        GridBagConstraints c = new GridBagConstraints();
        c.gridwidth = GridBagConstraints.REMAINDER;
        c.fill = GridBagConstraints.BOTH;
        c.weightx = 1.0;
        c.weighty = 1.0;

        cspSolutionArea = new JTextArea("Solution of the generated CSP", 10, 40);
        cspSolutionArea.setEditable(false);
        cspSolutionArea.setLineWrap(true);
        cspSolutionArea.setWrapStyleWord(true);

        scroll = new JScrollPane(cspSolutionArea);
        scroll.setWheelScrollingEnabled(true);
        scroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);

        add(scroll, c);

    }

    public void displaySolution(String solution) {
        cspSolutionArea.setText("");
        cspSolutionArea.setText(solution);
    }

}
