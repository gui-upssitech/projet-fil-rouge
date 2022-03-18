package dev.miniteldo.search.model.engines.miniteldoengine.command;

import dev.miniteldo.search.model.engines.miniteldoengine.admin.LogOptions;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

public class Command {
    private ProcessBuilder processBuilder;

    public Command(SearcherType searcherType, String data) {
        processBuilder = new ProcessBuilder("./bridge/" + searcherType.getSearcherType(), searcherType.getDataType(), data);
        processBuilder = processBuilder.directory(new File("../search-engine"));
    }

    public Command(LogOptions logOptions, String data) {
        processBuilder = new ProcessBuilder("./bridge/" + logOptions.getLogType(), logOptions.getLogAction(), data);
        processBuilder = processBuilder.directory(new File("../search-engine"));
    }

    public BufferedReader getResult() throws IOException {
        Process process = processBuilder.start();
        return new BufferedReader(new InputStreamReader(process.getInputStream()));
    }
}