package dev.miniteldo.search.model.engine.searcher;

import java.util.ArrayList;

public abstract class Searcher {
    protected SearcherType searcherType;

    public abstract ArrayList<SearchResult> search(String request);
}