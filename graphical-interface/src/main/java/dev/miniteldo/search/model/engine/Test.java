package dev.miniteldo.search.model.engine;

import dev.miniteldo.search.model.engine.command.Command;
import dev.miniteldo.search.model.engine.command.CommandFactory;
import dev.miniteldo.search.model.engine.searcher.SearcherType;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

public class Test{

    public static void main(String[] args) throws IOException {
        BufferedReader reader = CommandFactory.getCommand(SearcherType.IMAGE_RGB_PATH,"data/image/RGB/01.jpg").getResult();

        String line;
        while((line = reader.readLine()) != null) {
            System.out.println(line);
        }

    }
}