package dev.miniteldo.search.model.engines.miniteldoengine.indexer;

import dev.miniteldo.search.model.engines.miniteldoengine.command.Command;

import java.io.BufferedReader;
import java.io.IOException;

public class Indexer {
    public static boolean indexText(String miniteldoEnginePath, IndexerMode mode) throws IOException {
        boolean result = false;
        String line;
        Command command = new Command(miniteldoEnginePath, IndexerOptions.TEXT, mode);
        BufferedReader reader = command.getResult();

        while ((line = reader.readLine()) != null) {
            if (line.equals("1")) {
                result = true;
            }
        }
        return result;
    }

    public static boolean indexImage(String miniteldoEnginePath, IndexerMode mode) throws IOException {
        boolean result = false;
        String line;
        Command command = new Command(miniteldoEnginePath, IndexerOptions.IMAGE, mode);
        BufferedReader reader = command.getResult();

        while ((line = reader.readLine()) != null) {
            if (line.equals("1")) {
                result = true;
            }
        }
        return result;
    }

    public static boolean indexAudio(String miniteldoEnginePath, IndexerMode mode) throws IOException {
        boolean result = false;
        String line;
        Command command = new Command(miniteldoEnginePath, IndexerOptions.AUDIO, mode);
        BufferedReader reader = command.getResult();

        while ((line = reader.readLine()) != null) {
            if (line.equals("1")) {
                result = true;
            }
        }
        return result;
    }

    public static boolean indexAll(String miniteldoEnginePath, IndexerMode mode) throws IOException {
        boolean result = false;
        String line;
        Command command = new Command(miniteldoEnginePath, IndexerOptions.ALL, mode);
        BufferedReader reader = command.getResult();

        while ((line = reader.readLine()) != null) {
            if (line.equals("1")) {
                result = true;
            }
        }
        return result;
    }
}
