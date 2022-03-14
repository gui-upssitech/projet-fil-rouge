package dev.miniteldo.search.model.engines.miniteldoengine;

import dev.miniteldo.search.model.engines.miniteldoengine.command.Command;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.Searcher;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherFactory;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.nio.file.FileSystems;

public class Test{

    public static void main(String[] args) throws IOException {
        Searcher searcher = SearcherFactory.getSearcher(SearcherType.IMAGE_RGB_PATH);
        System.out.println(searcher.search("data/image/RGB/01.jpg"));
    }
}