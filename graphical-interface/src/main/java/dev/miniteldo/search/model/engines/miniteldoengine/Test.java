package dev.miniteldo.search.model.engines.miniteldoengine;

import dev.miniteldo.search.model.engines.miniteldoengine.searcher.Searcher;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherFactory;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;

import java.io.IOException;

public class Test{

    public static void main(String[] args) throws IOException {
        Searcher searcher = SearcherFactory.getSearcher(SearcherType.AUDIO_PATH);
        System.out.println(searcher.search("data/audio/corpus_fi.wav"));
    }
}