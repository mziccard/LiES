import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * Created with IntelliJ IDEA.
 * User: dextor
 * Date: 8/16/13
 * Time: 3:40 PM
 * To change this template use File | Settings | File Templates.
 */
public class SolverWrapper {

    private static final String solverPath = "";

    public static String execute(String csp) {
        try {
            String[] cmdList = {solverPath + "/solver", "\"" + csp + "\""};
            Process p = Runtime.getRuntime().exec(cmdList);
            BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line = "";
            StringBuffer output = new StringBuffer();

            while ((line = reader.readLine()) != null) {
                output.append(line);
            }

            reader.close();

            return output.toString();

        } catch (IOException e) {
            e.printStackTrace();
        }

        return "Solver error";
    }

}
