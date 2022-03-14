package dev.miniteldo.search.model.engines.miniteldoengine;

import dev.miniteldo.search.model.engines.miniteldoengine.command.CommandFactory;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;

import java.io.BufferedReader;
import java.io.IOException;

public class Test{

    public static void main(String[] args) throws IOException {
        BufferedReader reader = CommandFactory.getCommand(SearcherType.IMAGE_RGB_PATH,"data/image/RGB/01.jpg").getResult();

        String line;
        while((line = reader.readLine()) != null) {
            System.out.println(line);
        }

    }
}