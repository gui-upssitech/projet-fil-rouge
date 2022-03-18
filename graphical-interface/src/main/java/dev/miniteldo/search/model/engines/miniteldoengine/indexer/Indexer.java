package dev.miniteldo.search.model.engines.miniteldoengine.indexer;

import dev.miniteldo.search.model.engines.miniteldoengine.command.Command;

import java.io.BufferedReader;
import java.io.IOException;

public class Indexer {
    public static boolean indexText() throws IOException {
        boolean result = false;
        String line;
        Command command = new Command(IndexerOptions.TEXT);
        BufferedReader reader = command.getResult();

        while ((line = reader.readLine()) != null) {
            if (line.equals("1")) {
                result = true;
            }
        }
        return result;
    }

    public static boolean indexImage() throws IOException {
        boolean result = false;
        String line;
        Command command = new Command(IndexerOptions.IMAGE);
        BufferedReader reader = command.getResult();

        while ((line = reader.readLine()) != null) {
            if (line.equals("1")) {
                result = true;
            }
        }
        return result;
    }

    public static boolean indexAudio() throws IOException {
        boolean result = false;
        String line;
        Command command = new Command(IndexerOptions.AUDIO);
        BufferedReader reader = command.getResult();

        while ((line = reader.readLine()) != null) {
            if (line.equals("1")) {
                result = true;
            }
        }
        return result;
    }

    public static boolean indexAll() throws IOException {
        boolean result = false;
        String line;
        Command command = new Command(IndexerOptions.ALL);
        BufferedReader reader = command.getResult();

        while ((line = reader.readLine()) != null) {
            if (line.equals("1")) {
                result = true;
            }
        }
        return result;
    }
}
