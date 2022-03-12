package dev.miniteldo.search.model.engine.command;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

public class Command {
    private ProcessBuilder processBuilder;

    public Command(String searchType, String inputType, String data) {
        processBuilder = new ProcessBuilder("./bridge/" + searchType, inputType, data);
        processBuilder = processBuilder.directory(new File("../search-engine"));
    }

    public BufferedReader getResult() throws IOException {
        Process process = processBuilder.start();
        return new BufferedReader(new InputStreamReader(process.getInputStream()));
    }
}
