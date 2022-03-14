package dev.miniteldo.search.model.engines.miniteldoengine.searcher;

import java.io.IOException;
import java.util.ArrayList;

public abstract class Searcher {
    protected SearcherType searcherType;
    protected String path;

    public abstract ArrayList<SearchResult> search(String request) throws IOException;
}
