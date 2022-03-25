package dev.miniteldo.search.model.tools;

import dev.miniteldo.search.model.engines.SearchResult;

import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;

public class FileTools {
    public static boolean saveRequest(String request, ArrayList<SearchResult> searchResults) {
        String PATH = "../data/save.txt";
        FileOutputStream outputStream;
        String line = "";

        try {
            outputStream = new FileOutputStream(PATH, true);
            outputStream.write((request + "\n").getBytes());
            for (SearchResult searchResult : searchResults) {
                line = searchResult.getFilePath() + "#" + searchResult.getConfidence() + "\n";
                outputStream.write(line.getBytes());
            }
            outputStream.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return true;
        // FIXME: 25/03/2022 FIX OVERWRITING
    }

    public static void clearFile() {
        String PATH = "../data/save.txt";
        FileOutputStream outputStream;
        String line = "";

        try {
            outputStream = new FileOutputStream(PATH);
            outputStream.write(line.getBytes());
            outputStream.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static HashMap<String, ArrayList<SearchResult>> readFile() {
        HashMap<String, ArrayList<SearchResult>> hashMap = new HashMap<>();
        String PATH = "../data/save.txt";
        String currentRequest = "";

        BufferedReader reader;
        try {
            // Assure that the file exists
            File saveFile = new File(PATH);
            saveFile.createNewFile();
            reader = new BufferedReader(new FileReader(PATH));
            String line = reader.readLine();
            while (line != null) {
                if (line.contains("#")) {
                    String[] splits = line.split("#");
                    hashMap.get(currentRequest).add(new SearchResult(splits[0], Float.parseFloat(splits[1])));
                } else {
                    currentRequest = line;
                    hashMap.put(currentRequest, new ArrayList<>());
                }

                line = reader.readLine();
            }
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return hashMap;

    }
}
