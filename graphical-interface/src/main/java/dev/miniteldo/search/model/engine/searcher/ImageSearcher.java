package searchengine.searcher;

import java.util.ArrayList;

public class ImageSearcher extends Searcher {

    public ImageSearcher(SearcherType searcherType) {
        super();
        this.searcherType = searcherType;
    }

    @Override
    public ArrayList<SearchResult> search(String request) {
        return null;
    }
}
