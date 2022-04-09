package dev.miniteldo.search.model.tools;

import dev.miniteldo.search.model.History;
import dev.miniteldo.search.model.engines.AudioSearchResult;
import dev.miniteldo.search.model.engines.SearchResult;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.*;
import java.nio.file.Paths;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.TreeMap;

public class FileTools {
    private static final String PATERN_RESULT = "|";
    private static final String PATERN_REQUEST = "@";

    public static boolean saveRequest(String request, ArrayList<SearchResult> searchResults) {
        // variables
        String PATH = "../data/save.txt";
        FileOutputStream outputStream;
        String line = "";
        String strRequest = "";
        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");
        LocalDateTime now = LocalDateTime.now();

        try {
            outputStream = new FileOutputStream(PATH, true);
            strRequest = request + PATERN_REQUEST + dtf.format(now) + "\n";
            outputStream.write(strRequest.getBytes());
            for (SearchResult searchResult : searchResults) {
                if (searchResult instanceof AudioSearchResult audioSearchResult) {
                    line = audioSearchResult.getFilePath() + PATERN_RESULT + audioSearchResult.getConfidence() + PATERN_RESULT + audioSearchResult.getTimeCode() + "\n";
                } else {
                    line = searchResult.getFilePath() + PATERN_RESULT + searchResult.getConfidence() + "\n";
                }
                outputStream.write(line.getBytes());
            }
            outputStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return true;
    }

    public static boolean clearFile() {
        String PATH = "../data/save.txt";
        FileOutputStream outputStream;
        String line = "";

        try {
            outputStream = new FileOutputStream(PATH);
            outputStream.write(line.getBytes());
            outputStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return true;
    }

    public static TreeMap<History, ArrayList<SearchResult>> readFile() {
        TreeMap<History, ArrayList<SearchResult>> hashMap = new TreeMap<>();
        String PATH = "../data/save.txt";
        String[] splits;
        History currentHistory = null;

        BufferedReader reader;
        try {
            // Assure that the file exists
            File saveFile = new File(PATH);
            saveFile.createNewFile();
            reader = new BufferedReader(new FileReader(PATH));
            String line = reader.readLine();
            while (line != null) {
                if (line.contains(PATERN_RESULT)) {
                    splits = line.split("\\|");

                    // With time code
                    if (splits.length == 3) {
                        hashMap.get(currentHistory).add(new AudioSearchResult(splits[0], Float.parseFloat(splits[1]), Integer.parseInt(splits[2])));
                    } else {
                        hashMap.get(currentHistory).add(new SearchResult(splits[0], Float.parseFloat(splits[1])));
                    }
                } else {
                    splits = line.split("@");
                    currentHistory = new History(splits[0], new SimpleDateFormat("yyyy/MM/dd HH:mm:ss").parse(splits[1]));

                    hashMap.put(currentHistory, new ArrayList<>());
                }

                line = reader.readLine();
            }
            reader.close();
        } catch (IOException | ParseException e) {
            e.printStackTrace();
        }

        return hashMap;
    }

    public static File getInputFile(Stage stage) {
        FileChooser fileChooser = new FileChooser();
        fileChooser.getExtensionFilters().addAll(
                new FileChooser.ExtensionFilter("Descriptors", List.of("*.xml", "*.jpg", "*.bmp", "*.wav"))
        );

        // Set title for FileChooser
        fileChooser.setTitle("Select Some Files");

        // Set Initial Directory
        String currentPath = Paths.get("../data/").toAbsolutePath().toString();
        fileChooser.setInitialDirectory(new File(currentPath));
        return fileChooser.showOpenDialog(stage);
    }
}
