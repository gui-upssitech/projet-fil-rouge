package dev.miniteldo.search.model.engine.searcher;

public class SearcherFactory {

    public static Searcher getSearcher(SearcherType searcherType) {
        Searcher searcher;

        switch(searcherType) {
            case TEXT_KEYWORD: case TEXT_PATH:
                searcher = new TextSearcher(searcherType);
                break;
            case IMAGE_RGB_PATH: case IMAGE_NB_PATH:
                searcher = new ImageSearcher(searcherType);
                break;
            default:
                searcher = new AudioSearcher();
                break;
        }

        return searcher;
    }
}