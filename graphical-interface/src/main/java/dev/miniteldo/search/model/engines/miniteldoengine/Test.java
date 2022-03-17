package dev.miniteldo.search.model.engines.miniteldoengine;

import dev.miniteldo.search.model.engines.miniteldoengine.searcher.Searcher;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherFactory;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;

import java.io.IOException;

public class Test{

    public static void main(String[] args) throws IOException {
        Searcher searcher = SearcherFactory.getSearcher(SearcherType.TEXT_PATH);
        System.out.println(searcher.search("data/text/03-Mimer_un_signal_nerveux_pour_utf8.xml"));
    }
}