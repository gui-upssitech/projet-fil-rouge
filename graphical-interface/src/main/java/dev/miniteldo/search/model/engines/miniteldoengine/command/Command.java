package dev.miniteldo.search.model.engines.miniteldoengine.command;

import dev.miniteldo.search.model.engines.miniteldoengine.admin.Configurations;
import dev.miniteldo.search.model.engines.miniteldoengine.admin.LoggerOptions;
import dev.miniteldo.search.model.engines.miniteldoengine.indexer.IndexerMode;
import dev.miniteldo.search.model.engines.miniteldoengine.indexer.IndexerOptions;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

public class Command {
    private ProcessBuilder processBuilder;

    public Command(String miniteldoEnginePath, SearcherType searcherType, String data) {
        processBuilder = new ProcessBuilder("./bridge/" + searcherType.getSearcherType(), searcherType.getDataType(), data);
        processBuilder = processBuilder.directory(new File("../" + miniteldoEnginePath));
    }

    public Command(String miniteldoEnginePath, LoggerOptions logOptions, String data) {
        processBuilder = new ProcessBuilder("./bridge/" + logOptions.getLogType(), logOptions.getLogAction(), data);
        processBuilder = processBuilder.directory(new File("../" + miniteldoEnginePath));
    }

    public Command(String miniteldoEnginePath, IndexerOptions indexerOptions, IndexerMode mode) {
        processBuilder = new ProcessBuilder("./bridge/" + indexerOptions.getIndexingType(), indexerOptions.getDataType(), mode.getMode());
        processBuilder = processBuilder.directory(new File("../" + miniteldoEnginePath));
    }

    public Command(String miniteldoEnginePath, Configurations configurations, String data) {
        processBuilder = new ProcessBuilder("./bridge/" + configurations.getParametersType(), configurations.getParameters(), data);
        processBuilder = processBuilder.directory(new File("../" + miniteldoEnginePath));
    }

    public BufferedReader getResult() throws IOException {
        Process process = processBuilder.start();
        return new BufferedReader(new InputStreamReader(process.getInputStream()));
    }
}