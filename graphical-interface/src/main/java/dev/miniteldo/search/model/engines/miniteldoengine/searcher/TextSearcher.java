package dev.miniteldo.search.model.engines.miniteldoengine.searcher;

import dev.miniteldo.search.model.engines.SearchResult;

import java.util.ArrayList;

public class TextSearcher extends Searcher {

    public TextSearcher(SearcherType searcherType) {
        super();
        this.searcherType = searcherType;
    }

    @Override
    protected ArrayList<SearchResult> searchInner(String request) {
        return null;
    }
}
