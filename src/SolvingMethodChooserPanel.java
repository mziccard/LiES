import javax.swing.*;
import java.awt.*;

/**
 * Created with IntelliJ IDEA.
 * User: dextor
 * Date: 8/16/13
 * Time: 2:32 PM
 * To change this template use File | Settings | File Templates.
 */
public class SolvingMethodChooserPanel extends JPanel {

    private final MainWindow parent;
    private final JRadioButton backtrackButton;
    private final JRadioButton backtrackMCButton;
    private final JRadioButton backtrackACButton;
    private final JRadioButton branchAndBoundButton;
    private final JRadioButton branchAndBoundACButton;

    public SolvingMethodChooserPanel(MainWindow parent) {
        this.parent = parent;

        setLayout(new FlowLayout());

        backtrackButton = new JRadioButton();
        backtrackButton.setText("Backtrack");

        backtrackMCButton = new JRadioButton();
        backtrackMCButton.setText("Backtrack (most constrained)");

        backtrackACButton = new JRadioButton();
        backtrackACButton.setText("Backtrack (arc consistency)");

        branchAndBoundButton = new JRadioButton();
        branchAndBoundButton.setText("Branch and bound");

        branchAndBoundACButton = new JRadioButton();
        branchAndBoundACButton.setText("Branch and bound (arc consistency)");

        ButtonGroup group = new ButtonGroup();
        group.add(backtrackButton);
        group.add(backtrackMCButton);
        group.add(backtrackACButton);
        group.add(branchAndBoundButton);
        group.add(branchAndBoundACButton);

        backtrackButton.setSelected(true);

        add(backtrackButton);
        add(backtrackMCButton);
        add(backtrackACButton);
        add(branchAndBoundButton);
        add(branchAndBoundACButton);
    }



}
