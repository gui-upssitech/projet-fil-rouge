package dev.miniteldo.search.model.engines.miniteldoengine.searcher;

import dev.miniteldo.search.model.engines.SearchResult;

import java.io.IOException;
import java.util.ArrayList;

public abstract class Searcher {
    protected SearcherType searcherType;
    protected String path;

    protected abstract ArrayList<SearchResult> searchInner(String request) throws IOException;

    public ArrayList<SearchResult> search(String request) {
        try {
            return searchInner(request);
        } catch(IOException e) {
            return new ArrayList<>();
        }
    }
}
