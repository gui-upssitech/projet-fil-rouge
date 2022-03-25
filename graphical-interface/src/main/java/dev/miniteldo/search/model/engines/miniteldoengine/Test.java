package dev.miniteldo.search.model.engines.miniteldoengine;

import dev.miniteldo.search.model.engines.SearchResult;
import dev.miniteldo.search.model.tools.FileTools;

import java.io.IOException;
import java.util.ArrayList;

public class Test {

    public static void main(String[] args) throws IOException, InterruptedException {
//        System.out.println(Configurator.loadConfigs("search-engine"));
//        Configurator.configure("search-engine", Configurations.INDEXING_MODE, "0");
//        System.out.println(Configurator.loadConfigs("search-engine"));

        ArrayList<SearchResult> searchResults = new ArrayList<>();
        searchResults.add(new SearchResult("58", 12));
        searchResults.add(new SearchResult("59", 12));
        searchResults.add(new SearchResult("60", 12));
        searchResults.add(new SearchResult("61", 12));
        searchResults.add(new SearchResult("62", 12));
        searchResults.add(new SearchResult("63", 12));
        FileTools.saveRequest("/home/juju/Bureau/projet-fil-rouge/data/image/NB/51.bmp", searchResults);
    }
}