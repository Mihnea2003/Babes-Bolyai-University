import java.util.HashMap;
import java.util.Map;

public class ColorManager {
    private static String[] colorNames;

    public static void initializeColorCount(int count) {
        colorNames = new String[count];
    }

    public static void assignColorName(int colorIndex, String name) {
        colorNames[colorIndex - 1] = name;
    }

    public static Map<Integer, String> mapNodesToColors(int[] nodeCodes) {
        Map<Integer, String> nodeColorMapping = new HashMap<>();

        for (int i = 0; i < nodeCodes.length; i++) {
            String color = colorNames[nodeCodes[i] - 1];
            nodeColorMapping.put(i, color);
        }

        return nodeColorMapping;
    }

    public static int getColorCount() {
        return colorNames.length;
    }
}