package dev.miniteldo.search.model.tools;

import dev.miniteldo.search.model.engines.SearchResult;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;

public class FileTools {
    public static boolean saveRequest(String request, ArrayList<SearchResult> searchResults) {
        String PATH = "../data/save.txt";
        FileOutputStream outputStream;
        String line = "";

        try {
            outputStream = new FileOutputStream(PATH);
            outputStream.write((request + "\n").getBytes());
            for (SearchResult searchResult : searchResults) {
                line = searchResult.getFilePath() + "-" + searchResult.getConfidence() + "\n";
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
}
