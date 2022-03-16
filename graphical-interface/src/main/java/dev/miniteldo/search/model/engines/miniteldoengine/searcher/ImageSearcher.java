package dev.miniteldo.search.model.engines.miniteldoengine.searcher;

import dev.miniteldo.search.model.engines.SearchResult;
import dev.miniteldo.search.model.engines.miniteldoengine.command.Command;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;

public class ImageSearcher extends Searcher {

    public ImageSearcher(SearcherType searcherType) {
        super();
        this.searcherType = searcherType;
        this.path = (searcherType == SearcherType.IMAGE_RGB_PATH) ? "search-engine/data/image/RGB/" : "search-engine/data/image/NB/";
    }

    @Override
    protected ArrayList<SearchResult> searchInner(String request) throws IOException {
        ArrayList<SearchResult> searchResults = new ArrayList<>();
        Command command = new Command(searcherType, request);
        BufferedReader reader = command.getResult();
        String absolutePath = System.getProperty("user.dir").toString();
        String line;

        while((line = reader.readLine()) != null) {
            String[] splitResults = line.split(" ");

            SearchResult searchResult = new SearchResult(absolutePath.substring(0, absolutePath.lastIndexOf("/")+1) + path + splitResults[0], Float.parseFloat(splitResults[1]));
            searchResults.add(searchResult);
        }
        return searchResults;
    }
}
